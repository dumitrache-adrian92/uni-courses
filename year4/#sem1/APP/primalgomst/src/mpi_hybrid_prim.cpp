#include <bits/stdc++.h>
#include <mpi.h>
#include <omp.h>
#include <unistd.h>

using namespace std;

#define MASTER 0

int proc_count;
int id;
int thread_count;

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

struct handle_lines_arg
{
    int id;
    int P;
    int N;
    vector<vector<pair<int, int>>> *adj;
    vector<string> *lines;
};

void *handle_lines(void *arg)
{
    handle_lines_arg *args = (handle_lines_arg *)arg;
    auto [id, P, N, adj, lines] = *args;

    int start = id * (double)N / P;
    int end = min((id + 1) * (double)N / P, (double)N);

    for (int i = start; i < end; i++)
    {
        istringstream iss((*lines)[i]);

        for (int j = 0; j < N; j++)
        {
            int weight;
            iss >> weight;

            if (weight != 0)
            {
                (*adj)[i].push_back({j, weight});
            }
        }
    }

    return NULL;
}

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

    vector<vector<pair<int, int>>> adj(V, vector<pair<int, int>>());
    vector<string> lines(V, string());
    string line;

    int P = thread_count;
    int current_id = 0;
    int end = min((current_id + 1) * (double)V / P, (double)V);

    vector<handle_lines_arg> args(P);

    int i = 0;

    getline(file, line);

    for (i = 0; i < V; i++)
    {
        getline(file, line);
        lines[i] = line;

        if (i == end - 1)
        {
            args[current_id] = {current_id, P, V, &adj, &lines};
            #pragma omp task shared(adj, lines)
            handle_lines(&(args[current_id]));

            current_id++;
            end = min((current_id + 1) * (double)V / P, (double)V);
        }
    }

    #pragma omp taskwait

    return adj;
}

pair<int, vector<pair<int, int>>> prim_minimum_spanning_tree_master(vector<vector<pair<int, int>>> &adj)
{
    int V = adj.size();
    MPI_Bcast(&V, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    vector<int> dist(V);
    vector<int> parent(V);

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    uint64_t cost = 0;
    vector<pair<int, int>> mst_edges;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    vector<int> visited(V + 1, -1);

    dist[0] = 0;
    pq.push({0, dist[0]});
    int i;
    while (!pq.empty())
    {
        auto [node, d] = pq.top();
        pq.pop();

        int ok = 0;
        #pragma omp parallel for shared(visited) private(i) reduction(||:ok)
        for (i = 0; i < V; i++)
        {
            if (visited[i] == node)
            {
                ok = 1;
            }
        }

        if (ok)
        {
            continue;
        }

        visited[node] = node;
        if (parent[node] != -1)
        {
            cost += dist[node];
            mst_edges.push_back({node, parent[node]});
        }

        MPI_Bcast(&node, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

        vector<int> sendcounts(proc_count);
        vector<int> displs(proc_count);

        for (i = 0; i < proc_count; i++)
        {
            sendcounts[i] = adj[node].size() / proc_count;
            displs[i] = i * sendcounts[i];
        }

        sendcounts[proc_count - 1] += adj[node].size() % proc_count;

        for (i = 1; i < proc_count; i++)
        {
            MPI_Send(&sendcounts[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        vector<pair<int, int>> local_adj(sendcounts[MASTER]);

        MPI_Scatterv(adj[node].data(), sendcounts.data(), displs.data(),
                     MPI_2INT, local_adj.data(), sendcounts[MASTER],
                     MPI_2INT, MASTER, MPI_COMM_WORLD);

        int n = local_adj.size();
        #pragma omp parallel
        {

            #pragma omp single
            {
                for (int i = 0; i < n; i++)
                {
                    #pragma omp task shared(visited, dist, parent) firstprivate(i)
                    {
                        auto [neighbour, weight] = local_adj[i];

                        int ok = 0;

                        #pragma omp parallel for shared(visited) reduction(||:ok)
                        for (int j = 0; j < V; j++)
                        {
                            if (visited[j] == neighbour)
                            {
                                ok = 1;
                            }
                        }

                        if (!ok && dist[neighbour] > weight)
                        {
                            dist[neighbour] = weight;
                            parent[neighbour] = node;

                            #pragma omp critical
                            {
                                pq.push({neighbour, dist[neighbour]});
                            }
                        }
                    }
                }
            }

            #pragma omp taskwait
        }

        for (int i = 1; i < proc_count; i++)
        {
            int n;

            MPI_Recv(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < n; j++)
            {
                pair<int, int> p;

                MPI_Recv(&p, 1, MPI_2INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int ok = 0;
                int k;
                #pragma omp parallel for shared(visited) private(k) reduction(||:ok)
                for (k = 0; k < V; k++)
                {
                    if (visited[k] == p.first)
                    {
                        ok = 1;
                    }
                }
                if (!ok && dist[p.first] > p.second)
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
    vector<int> visited(V + 1, -1);

    while (true)
    {
        int node;
        MPI_Bcast(&node, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

        if (node == -1)
        {
            break;
        }

        visited[node] = node;

        int recv_count;
        MPI_Recv(&recv_count, 1, MPI_INT, MASTER, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        vector<pair<int, int>> local_adj(recv_count);

        MPI_Scatterv(nullptr, nullptr, nullptr,
                     MPI_2INT, local_adj.data(), recv_count,
                     MPI_2INT, MASTER, MPI_COMM_WORLD);

        unordered_map<int, int> dist;
        int adj_size = local_adj.size();
        int i, j;
        for (i = 0; i < adj_size; i++)
        {
            auto [neighbour, weight] = local_adj[i];
            int ok = 0;
            #pragma omp parallel for shared(visited) private(j) reduction(||:ok)
            for (j = 0; j < V; j++)
            {
                if (visited[j] == neighbour)
                {
                    ok = 1;
                }
            }

            if(!ok && (dist.find(neighbour) == dist.end() || dist[neighbour] > weight))
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

    if (argc <= 1)
    {
        if (rank == MASTER)
        {
            cerr << "Usage: " << argv[0] << " <graph_file> [thread_count]" << endl;
        }

        MPI_Finalize();
        exit(1);
    }

    if (argc == 3)
    {
        thread_count = atoi(argv[2]);
    }
    else
    {
        thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    }

    omp_set_num_threads(thread_count / size);

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
