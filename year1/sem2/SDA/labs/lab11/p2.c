#include <stdio.h>

void floydWarshall(int graph[][10], int dist[][10], int n) {
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

void printDist(int dist[][10], int x, int y) {
    printf("%d\n", dist[x - 1][y - 1]);
}

int main() {
    int n, x, y;
    int i, j, k;
    int t = 10;
    scanf("%d%d%d", &n, &x, &y);
    int graph[10][10], dist[10][10];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = t;
    int m;
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &j, &k);
        graph[j - 1][k - 1] = 30;
    }

    floydWarshall(graph, dist, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }

    printDist(dist, x, y);
}