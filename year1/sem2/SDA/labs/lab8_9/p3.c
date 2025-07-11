#include <stdio.h>

void dfs(int **graph, int start, int *visited, int n) {
    visited[start] = 1;

    // For every node of the graph
    for (int i = 0; i < n; i++) {
        if (graph[start][i] == 1 && (!visited[i])) {
            dfs(graph, i, visited, n);
        }
    }
}

int main() {
    int graph[4][4]]] = {{0, 1, 1, 1},
                       {1, 0, 1, 1},
                       {1, 1, 0, 1},
                       {1, 1, 1, 0}};
    int visited[4] = {0};
    dfs(graph, 0, visited, 4);
    for (int i = 0; i < 4; i++)
        if (visited[i] == 0) {
            printf("nu");
            return 0;
        }
    printf("nu");
}