#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int thread_count;

class Compare {
public:
    bool operator() (const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }

        return a.second > b.second;
    }
};

class ThreadPool {
public:
    ThreadPool(int num_threads) {
        threads.resize(num_threads);
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&job_available, NULL);
        pthread_cond_init(&pool_idle, NULL);

        stop = false;
        active_tasks = 0;

        for (int i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, thread_loop, this);
        }
    }

    ~ThreadPool() {
        end();

        for (size_t i = 0; i < threads.size(); i++) {
            pthread_join(threads[i], NULL);
        }

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&job_available);
        pthread_cond_destroy(&pool_idle);
    }

    static void *thread_loop(void *arg) {
        ThreadPool *pool = (ThreadPool *) arg;

        while (true) {
            pthread_mutex_lock(&pool->lock);

            while (pool->tasks.empty() && !pool->stop) {
                pthread_cond_wait(&pool->job_available, &pool->lock);
            }

            if (pool->stop) {
                pthread_mutex_unlock(&pool->lock);
                break;
            }

            auto task = pool->tasks.front().first;
            auto arg = pool->tasks.front().second;
            pool->tasks.pop();
            pool->active_tasks++;

            pthread_mutex_unlock(&pool->lock);

            (*task)(arg);

            pthread_mutex_lock(&pool->lock);
            pool->active_tasks--;

            if (pool->tasks.empty() && pool->active_tasks == 0) {
                pthread_cond_signal(&pool->pool_idle);
            }

            pthread_mutex_unlock(&pool->lock);
        }

        return NULL;
    }

    void submit(void *(*task)(void *), void *arg) {
        pthread_mutex_lock(&lock);
        tasks.push({task, arg});
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&job_available);
    }

    void wait_until_idle() {
        pthread_mutex_lock(&lock);

        while (!tasks.empty() || active_tasks > 0) {
            pthread_cond_wait(&pool_idle, &lock);
        }

        pthread_mutex_unlock(&lock);
    }

    void end() {
        pthread_mutex_lock(&lock);
        stop = true;
        pthread_mutex_unlock(&lock);

        pthread_cond_broadcast(&job_available);
    }

    vector<pthread_t> threads;
    queue<pair<void *(*)(void *), void *>> tasks;
    pthread_mutex_t lock;
    pthread_cond_t job_available;
    pthread_cond_t pool_idle;
    volatile bool stop;
    int active_tasks;
};

struct handle_lines_arg {
    int id;
    int P;
    int N;
    vector<vector<pair<int, int>>> *adj;
    vector<string> *lines;
};

void *handle_lines(void *arg) {
    handle_lines_arg *args = (handle_lines_arg *) arg;
    auto [id, P, N, adj, lines] = *args;

    int start = id * (double) N / P;
    int end = min((id + 1) * (double) N / P, (double) N);

    for (int i = start; i < end; i++) {
        istringstream iss((*lines)[i]);

        for (int j = 0; j < N; j++) {
            int weight;
            iss >> weight;

            if (weight != 0) {
                (*adj)[i].push_back({j, weight});
            }
        }
    }

    return NULL;
}

vector<vector<pair<int, int>>> get_adj_list(string filename, ThreadPool &pool) {
    ifstream file(filename);
    if (!file.is_open()) {
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
    int end = min((current_id + 1) * (double) V / P, (double) V);

    vector<handle_lines_arg> args(P);

    int i = 0;

    // Skip the first line
    getline(file, line);

    for (i = 0; i < V; i++) {
        getline(file, line);
        lines[i] = line;

        // We've read enough lines to start processing them in parallel
        if (i == end - 1) {
            args[current_id] = {current_id, P, V, &adj, &lines};
            pool.submit(handle_lines, &args[current_id]);

            current_id++;
            end = min((current_id + 1) * (double) V / P, (double) V);
        }
    }

    pool.wait_until_idle();

    return adj;
}

struct relax_edges_arg {
    int id;
    int node;
    int P;
    vector<int> *dist;
    vector<int> *parent;
    vector<pair<int, int>> *adj;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> *pq;
    set<int> *visited;
    pthread_mutex_t *lock;
};

void *relax_edges(void *arg) {
    relax_edges_arg *args = (relax_edges_arg *) arg;
    auto [id, node, P, dist, parent, adj, pq, visited, lock] = *args;

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

pair<int, vector<pair<int, int>>> prim_minimum_spanning_tree(vector<vector<pair<int, int>>> &adj,
                                                             ThreadPool &pool) {
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

    int num_threads = thread_count;
    int cache_line_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    int int_cache_line_size = cache_line_size / sizeof(int);
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

        int P = min(num_threads, (int) adj[node].size() / int_cache_line_size);

        if (P <= 1) {
            for (auto [neighbour, weight] : adj[node]) {
                if (visited.find(neighbour) == visited.end() && dist[neighbour] > weight) {
                    dist[neighbour] = weight;
                    parent[neighbour] = node;

                    pq.push({neighbour, dist[neighbour]});
                }
            }
        } else {
            for (int i = 0; i < P; i++) {
                args[i] = {i, node, P, &dist, &parent, &adj[node], &pq, &visited, &lock};
                pool.submit(relax_edges, &args[i]);
            }
        }

        pool.wait_until_idle();
    }

    pthread_mutex_destroy(&lock);

    return {cost, mst_edges};
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        exit(1);
    }

    if (argc == 3) {
        thread_count = atoi(argv[2]);
    } else {
        thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    }

    string graph_file = argv[1];
    ThreadPool pool(thread_count);

    vector<vector<pair<int, int>>> adj = get_adj_list(graph_file, pool);

    auto [cost, mst_edges] = prim_minimum_spanning_tree(adj, pool);

    cout << "Cost: " << cost << endl;

    for (auto [u, v] : mst_edges) {
        cout << u << " " << v << endl;
    }

    return 0;
}
