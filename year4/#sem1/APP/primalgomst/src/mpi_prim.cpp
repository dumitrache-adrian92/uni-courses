#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;

#define MASTER 0

int proc_count;
int id;

class Compare
{
public:
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }

        return a.second > b.second;
    }
};

vector<vector<pair<int, int>>> get_adj_list(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }

    int V;
    file >> V;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int weight;
            file >> weight;

            if (weight != 0)
            {
                adj[i].push_back({j, weight});
            }
        }
    }

    return adj;
}

pair<int, vector<pair<int, int>>> prim_minimum_spanning_tree_master(vector<vector<pair<int, int>>> &adj)
{
    auto V = adj.size();
    MPI_Bcast(&V, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    vector<int> dist(V);
    vector<int> parent(V);

    for (size_t i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    uint64_t cost = 0;
    vector<pair<int, int>> mst_edges;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    set<int> visited;

    dist[0] = 0;
    pq.push({0, dist[0]});

    while (!pq.empty())
    {
        auto [node, d] = pq.top();
        pq.pop();

        if (visited.find(node) != visited.end())
        {
            continue;
        }

        visited.insert(node);
        if (parent[node] != -1)
        {
            cost += dist[node];
            mst_edges.push_back({node, parent[node]});
        }

        // send node to all processes
        MPI_Bcast(&node, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

        // use MPI_Scatterv to send parts of adj[node] to all processes
        vector<int> sendcounts(proc_count);
        vector<int> displs(proc_count);

        for (int i = 0; i < proc_count; i++)
        {
            sendcounts[i] = adj[node].size() / proc_count;
            displs[i] = i * sendcounts[i];
        }

        sendcounts[proc_count - 1] += adj[node].size() % proc_count;

        for (int i = 1; i < proc_count; i++)
        {
            MPI_Send(&sendcounts[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        vector<pair<int, int>> local_adj(sendcounts[MASTER]);

        MPI_Scatterv(adj[node].data(), sendcounts.data(), displs.data(),
                     MPI_2INT, local_adj.data(), sendcounts[MASTER],
                     MPI_2INT, MASTER, MPI_COMM_WORLD);

        for (auto [neighbour, weight] : local_adj)
        {
            if (visited.find(neighbour) == visited.end() && dist[neighbour] > weight)
            {
                dist[neighbour] = weight;
                parent[neighbour] = node;

                pq.push({neighbour, dist[neighbour]});
            }
        }

        for (int i = 1; i < proc_count; i++)
        {
            int n;

            MPI_Recv(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < n; j++)
            {
                pair<int, int> p;

                MPI_Recv(&p, 1, MPI_2INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (visited.find(p.first) == visited.end() && dist[p.first] > p.second)
                {
                    dist[p.first] = p.second;
                    parent[p.first] = node;

                    pq.push({p.first, dist[p.first]});
                }
            }
        }
    }

    for (int i = 1; i < proc_count; i++)
    {
        int node = -1;
        MPI_Bcast(&node, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    }

    return {cost, mst_edges};
}

void prim_minimum_spanning_tree_worker()
{
    int V;
    MPI_Bcast(&V, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    vector<pair<int, int>> adj_for_node(V, {0, 0});
    set<int> visited;

    while (true)
    {
        int node;
        MPI_Bcast(&node, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

        if (node == -1)
        {
            break;
        }

        visited.insert(node);

        int recv_count;
        MPI_Recv(&recv_count, 1, MPI_INT, MASTER, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        vector<pair<int, int>> local_adj(recv_count);

        MPI_Scatterv(nullptr, nullptr, nullptr,
                     MPI_2INT, local_adj.data(), recv_count,
                     MPI_2INT, MASTER, MPI_COMM_WORLD);

        unordered_map<int, int> dist;

        for (auto [neighbour, weight] : local_adj)
        {
            if (visited.find(neighbour) == visited.end() &&
                (dist.find(neighbour) == dist.end() || dist[neighbour] > weight))
            {
                dist[neighbour] = weight;
            }
        }

        int n = dist.size();
        MPI_Send(&n, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);

        for (auto [neighbour, weight] : dist)
        {
            pair<int, int> p = {neighbour, weight};

            MPI_Send(&p, 1, MPI_2INT, MASTER, 0, MPI_COMM_WORLD);
        }
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    proc_count = size;
    id = rank;

    if (argc != 2)
    {
        if (rank == MASTER)
        {
            cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        }

        MPI_Finalize();
        exit(1);
    }

    if (rank == MASTER)
    {
        string graph_file = argv[1];

        vector<vector<pair<int, int>>> adj = get_adj_list(graph_file);

        auto [cost, mst_edges] = prim_minimum_spanning_tree_master(adj);

        cout << "Cost: " << cost << endl;

        for (auto [u, v] : mst_edges)
        {
            cout << u << " " << v << endl;
        }
    }
    else
    {
        prim_minimum_spanning_tree_worker();
    }

    MPI_Finalize();
    return 0;
}
