#include <bits/stdc++.h>

using namespace std;

#define INPUT_FILE "magazin.in"
#define OUTPUT_FILE "magazin.out"

int dfs(vector<int> adj[], int n,
            int source, vector<int> &dfs_order,
            vector<int> &children_count,
            vector<int> &node_index_in_order) {
    dfs_order.push_back(source);
    node_index_in_order[source] = dfs_order.size() - 1;

    for (auto child : adj[source])
        children_count[source] += 1 +
            dfs(adj, n, child, dfs_order, children_count,
                node_index_in_order);

    return children_count[source];
}

int main() {
    int i;
    FILE *input;
    FILE *output;

    input= fopen(INPUT_FILE, "r");
    output = fopen(OUTPUT_FILE, "w");

    int n, q;

    // input
    fscanf(input, "%d", &n);
    fscanf(input, "%d", &q);

    vector<int> adj[n + 1];

    for (i = 1; i <= n - 1; i++) {
        int x;

        fscanf(input, "%d", &x);
        adj[x].push_back(i + 1);
    }

    /* perform a dfs on the graph where we keep track of the order of the
     * traversal, the number of children of each node and the index of each
     * node in the traversal order
     */
    vector<int> dfs_order;
    vector<int> node_index_in_order(n + 1, 0);
    vector<int> children_count(n + 1, 0);

    dfs(adj, n, 1, dfs_order, children_count, node_index_in_order);

    for (i = 1; i <= q; i++) {
        int d, e;

        fscanf(input, "%d", &d);
        fscanf(input, "%d", &e);

        // answer the queries using the information supplied by the dfs
        int d_index = node_index_in_order[d];

        if (e > children_count[d])
            fprintf(output, "-1\n");
        else
            fprintf(output, "%d\n", dfs_order[d_index + e]);
    }

    fclose(input);
    fclose(output);

    return 0;
}
