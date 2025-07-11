#include <stdio.h>

int nV = 4;

void printMatrix(int matrix[][nV]);

void floydWarshall(int graph[][nV]) {
    int matrix[nV][nV], i, j, k;

    for (i = 0; i < nV; i++)
        for (j = 0; j < nV; j++)
            matrix[i][j] = graph[i][j];

    for (k = 0; k < nV; k++) {
        for (i = 0; i < nV; i++) {
            for (j = 0; j < nV; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
    // printMatrix(matrix);
}

void printMatrix(int matrix[][nV]) {
    for (int i = 0; i < nV; i++) {
        for (int j = 0; j < nV; j++) {
            if (matrix[i][j] == 999)
                printf("%4s", "999");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int minMatrix(int graph[][nV]) {
    int mn = graph[0][1];
    for (int i = 0; i < nV; i++)
        for (int j = 0; j < nV; j++)
            if (mn > graph[i][j] && graph[i][j] != 0)
                mn = graph[i][j];
    return mn;
}

int main() {
    int graph[4][4] = {{0, 3, 999, 5},
                       {2, 0, 999, 4},
                       {999, 1, 0, 999},
                       {999, 999, 2, 0}};
    floydWarshall(graph);
    printf("%d\n", minMatrix(graph));
}