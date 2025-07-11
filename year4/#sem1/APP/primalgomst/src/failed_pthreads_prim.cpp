#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Compare {
public:
    bool operator() (const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }

        return a.second > b.second;
    }
};

struct relax_edges_arg {
    int id;
    int node;
    vector<int> *dist;
    vector<int> *parent;
    vector<pair<int, int>> *adj;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> *pq;
    set<int> *visited;
    pthread_mutex_t *lock;
};

void *relax_edges(void *arg) {
    relax_edges_arg *args = (relax_edges_arg *) arg;
    auto [id, node, dist, parent, adj, pq, visited, lock] = *args;

    size_t P = sysconf(_SC_NPROCESSORS_ONLN);
    double N = adj->size();

    int start = id * (double) N / P;
    int end = min((id + 1) * (double) N / P, N);

    for (int i = start; i < end; i++) {
        auto [neighbour, weight] = (*adj)[i];
        if (visited->find(neighbour) == visited->end() &&
                (*dist)[neighbour] > weight) {
            (*dist)[neighbour] = weight;
            (*parent)[neighbour] = node;

            pthread_mutex_lock(lock);
            pq->push({neighbour, (*dist)[neighbour]});
            pthread_mutex_unlock(lock);
        }
    }

    return NULL;
}

vector<vector<pair<int, int>>> get_adj_list(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }

    int V;
    file >> V;

    vector<vector<pair<int, int>>> adj(V);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int weight;
            file >> weight;

            if (weight != 0) {
                adj[i].push_back({j, weight});
            }
        }
    }

    return adj;
}

pair<int, vector<pair<int, int>>> prim_minimum_spanning_tree(vector<vector<pair<int, int>>> &adj) {
    auto V = adj.size();
    vector<int> dist(V);
    vector<int> parent(V);

    for (size_t i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    uint64_t cost = 0;
    vector<pair<int, int>> mst_edges;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
    set<int> visited;

    dist[0] = 0;
    pq.push({0, dist[0]});

    int num_threads = sysconf(_SC_NPROCESSORS_ONLN);
    pthread_t threads[num_threads];
    pthread_mutex_t lock;

    pthread_mutex_init(&lock, NULL);

    while (!pq.empty()) {
        auto [node, d] = pq.top();
        pq.pop();

        if (visited.find(node) != visited.end()) {
            continue;
        }

        visited.insert(node);
        if (parent[node] != -1) {
            cost += dist[node];
            mst_edges.push_back({node, parent[node]});
        }

        vector<relax_edges_arg> args(num_threads);

        for (int i = 0; i < num_threads; i++) {
            args[i] = {i, node, &dist, &parent, &adj[node], &pq, &visited, &lock};
            pthread_create(&threads[i], NULL, relax_edges, &args[i]);
        }

        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    }

    pthread_mutex_destroy(&lock);

    return {cost, mst_edges};
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        exit(1);
    }

    string graph_file = argv[1];

    vector<vector<pair<int, int>>> adj = get_adj_list(graph_file);

    auto [cost, mst_edges] = prim_minimum_spanning_tree(adj);

    cout << "Cost: " << cost << endl;

    for (auto [u, v] : mst_edges) {
        cout << u << " " << v << endl;
    }

    return 0;
}
