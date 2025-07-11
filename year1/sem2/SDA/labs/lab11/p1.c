#include <stdio.h>
int nV = 4;
void printdist(int dist[][nV]);
void floydWarshall(int graph[][nV], int dist[][nV]) {
    int i, j, k;
    for (i = 0; i < nV; i++)
        for (j = 0; j < nV; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < nV; k++) {
        for (i = 0; i < nV; i++) {
            for (j = 0; j < nV; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
void printDistances(int dist[][nV]) {
    for (int i = 0; i < nV; i++) {
        for (int j = 0; j < nV; j++) {
            if (dist[i][j] == 999)
                printf("%4s", "999");
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}
void printDist(int dist[][nV], int x, int y) {
    printf("%d\n", dist[x - 1][y - 1]);
}

int main() {
    int graph[4][4] = {{0, 3, 999, 5},
                       {2, 0, 999, 4},
                       {999, 1, 0, 999},
                       {999, 999, 2, 0}};
    int dist[4][4];
    int i, j, k, n = 4;
    floydWarshall(graph, dist);
    printDist(dist, 2, 3);
}