#include "queue.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int n, m, d;     // nr clienti/depozite, nr muchii, nr drumuri
    double **graph;  // matrice de adiacenta a clientilor/depozitelor
    int *warehouses; // daca wh[i] = 1, i e depozit
} firm;

void readFirm(firm *gica) {
    int i, j;
    int x, y;
    double cost;
    scanf("%d%d%d", &gica->n, &gica->m, &gica->d);

    // alocare de memorie
    gica->warehouses = malloc(gica->n * sizeof(int));
    for (i = 0; i < gica->n; i++)
        gica->warehouses[i] = 0;

    gica->graph = malloc(gica->n * sizeof(double *));
    for (i = 0; i < gica->n; i++) {
        gica->graph[i] = malloc(gica->n * sizeof(double));
        // initializare
        for (j = 0; j < gica->n; j++)
            gica->graph[i][j] = 0;
    }

    // citire muchii
    for (i = 0; i < gica->m; i++) {
        scanf("%d%d%lf", &x, &y, &cost);
        gica->graph[x][y] = cost;
    }

    // citire depozite
    for (i = 0; i < gica->d; i++) {
        scanf("%d", &j);
        gica->warehouses[j] = 1;
    }
}

// elibereaza memoria alocata intr-o structura firm
void freeFirm(firm *gica) {
    if (gica->warehouses)
        free(gica->warehouses);
    for (int i = 0; i < gica->n; i++)
        free(gica->graph[i]);
    free(gica->graph);
}

/* foloseste vectorul de predecesori pentru a determina drumul de la parent la
   i pe care il noteaza in vectorul path*/
void pathCreate(int *shortestPath, int i, int *path, int *n) {
    if (shortestPath[i] == -1) {
        path[*n] = i;
        *n += 1;
        return;
    }
    pathCreate(shortestPath, shortestPath[i], path, n);
    path[*n] = i;
    *n += 1;
}

/* gaseste nodul nevizitat cu distanta cea mai mica fata de nodul pentru care
   apelam dijkstra*/
int minDist(double *dist, int *visited, int n) {
    int index, i;
    double min = INT_MAX;
    for (i = 0; i < n; i++)
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    return index;
}

// algoritmul lui Dijkstra cu vector de predecesori
double dijkstra(firm gica, int *path, int x, int y, int *n) {
    double *dist = malloc(gica.n * sizeof(double));   // vector distante de la x
    int *visited = calloc(gica.n, sizeof(int));       // 1 daca e vizitat, 0 altfel
    int *shortestPath = malloc(gica.n * sizeof(int)); // vector de predecesori
    int i, j, min;
    for (i = 0; i < gica.n; i++) {
        shortestPath[i] = 0;
        dist[i] = INT_MAX; // plecam de la distante ridicole
    }
    shortestPath[x] = -1; // parintele
    dist[x] = 0;          // distanta de la un nod la el e 0 intr-o lume cu geometrie euclidiana

    // algoritmul propriu zis ca la curs
    for (i = 0; i < gica.n - 1; i++) {
        min = minDist(dist, visited, gica.n);
        visited[min] = 1;
        for (j = 0; j < gica.n; j++)
            if (dist[min] + gica.graph[min][j] < dist[j] &&
                gica.graph[min][j] && !visited[j]) {
                shortestPath[j] = min;
                dist[j] = dist[min] + gica.graph[min][j];
            }
    }

    /* folosim vectorul de predecesori pentru a genera pasii celui mai scurt
       de la x la y*/
    pathCreate(shortestPath, y, path, n);
    // ca sa eliberam si sa si returnam distanta luam o copie
    double copy = dist[y];
    // eliberare de memorie
    free(dist);
    free(visited);
    free(shortestPath);
    return copy;
}

// algoritmul lui Warshall/Roy/Floyd exact cum l-am scris in liceu
void warshall(int **mat, int n) {
    int i, j, k;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (mat[i][j] == 0 && i != j)
                    mat[i][j] = mat[i][k] * mat[k][j];
}

// algoritmul lui Dijkstra pentru drumul cel mai scurt care viziteaza toate nodurile
double dijkstraAllNodes(firm aux, int x) {
    // distantele minime pentru ajunge in nodul i cu starea j
    double **dist = malloc(aux.n * sizeof(double *));
    double cost; // variabila de return
    queue nodes, bitmasks; // 2 cozi care o sa fie folosite ca una practic, lene...
    int currentNode, currentBitmask, goodMask;
    initQueue(&nodes, pow(2, aux.n) * aux.n);
    initQueue(&bitmasks, pow(2, aux.n) * aux.n);
    int i, j;
    // initializam matricea de distante
    for (i = 0; i < aux.n; i++) {
        dist[i] = malloc(pow(2, aux.n) * sizeof(double));
        for (j = 0; j < pow(2, aux.n); j++)
            dist[i][j] = INT_MAX;
        dist[i][(int)pow(2, i)] = 0;
    }

    // punem nodul nostru de start in cozi
    pushQueue(&nodes, x);
    pushQueue(&bitmasks, pow(2, x));

    // algoritmul Dijkstra aplicat pe graf cu stari
    while (!queueIsEmpty(nodes)) {
        // scoatem din coada un nod si starea sa
        currentNode = popQueue(&nodes);
        currentBitmask = popQueue(&bitmasks);
        // parcurgem toti fii
        for (j = 0; j < aux.n; j++)
            if (aux.graph[currentNode][j]) {
                /* daca drumul gasit anterior este mai lung decat cel nou, schimbam valoarea
                   si continum explorarea, adaugand in queue*/
                if (dist[j][currentBitmask | (int)pow(2, j)] > dist[currentNode][currentBitmask] + aux.graph[currentNode][j]) {
                    pushQueue(&nodes, j);
                    pushQueue(&bitmasks, currentBitmask | (int)pow(2, j));
                    dist[j][currentBitmask | (int)pow(2, j)] = dist[currentNode][currentBitmask] + aux.graph[currentNode][j];
                }
            }
    }

    cost = INT_MAX;
    /* masca in care sunt marcate ca vizitate doar nodurile si depozitul din
       care am plecat ca sa selectam doar starile bune*/
    goodMask = ((int)pow(2, aux.n - aux.d) - 1) | (int)pow(2, x);

    // aflam drumul minim ce parcurge tot
    for (j = goodMask; j < (int)pow(2, aux.n); j++)
        if (cost > dist[x][j] && ((goodMask & j) == goodMask))
            cost = dist[x][j];

    for (i = 0; i < aux.n; i++) {
        free(dist[i]);
    }
    free(dist);
    freeQueue(&nodes);
    freeQueue(&bitmasks);
    return cost;
}

void e1(firm gica) {
    int x, y, nr, j;
    double totalCost = 0, cost1, cost2;
    // x la y
    int *path1 = malloc(gica.n * sizeof(int)), n1;
    // y la x
    int *path2 = malloc(gica.n * sizeof(int)), n2;
    scanf("%d%d", &x, &nr);
    for (int i = 0; i < nr; i++) {
        /* calcul efectiv al celui mai scurt drum dus si intors cu dijkstra
           si afisare simultan*/
        n1 = 0;
        n2 = 0;
        scanf("%d", &y);
        printf("%d\n", y);
        cost1 = dijkstra(gica, path1, x, y, &n1);
        cost2 = dijkstra(gica, path2, y, x, &n2);
        totalCost += cost1 + cost2;
        printf("%.1lf %.1lf\n", cost1, cost2);
        for (j = 0; j < n1; j++)
            printf("%d ", path1[j]);
        for (j = 1; j < n2 - 1; j++)
            printf("%d ", path2[j]);
        printf("%d", path2[n2 - 1]); // pt ca checkerul e space sensitive, ugh
        printf("\n");
    }
    printf("%.1lf", totalCost);
    free(path1);
    free(path2);
}

void e2(firm gica) {
    int **stores;
    int *visited = calloc(gica.n, sizeof(int));
    int *scc = calloc(gica.n, sizeof(int)), m;
    int i, j, nr = 0, newLine = 0;
    // facem o matrice de adiacenta care nu contine depozitele
    stores = malloc(gica.n * sizeof(int *));
    for (i = 0; i < gica.n; i++) {
        stores[i] = malloc(gica.n * sizeof(int));
        // initializare
        for (j = 0; j < gica.n; j++)
            stores[i][j] = 0;
    }
    for (i = 0; i < gica.n; i++)
        for (j = 0; j < gica.n; j++)
            if (gica.graph[i][j] && !gica.warehouses[i] && !gica.warehouses[j])
                stores[i][j] = 1; // nu conteaza costurile... ce viata

    // conversie in matrice de drumuri
    warshall(stores, gica.n);

    // marcam depozitele ca vizitate ca nu le bage in seama la parcurgere
    for (i = 0; i < gica.n; i++)
        if (gica.warehouses[i])
            visited[i] = 1;

    // parcurgem odata componentele conexe ca sa gasim numarul de elemente
    for (i = 0; i < gica.n; i++) {
        if (visited[i])
            continue;
        nr++;
        visited[i] = 1;
        for (j = 0; j < gica.n; j++) {
            if (visited[j] || i == j)
                continue;
            if (stores[i][j] && stores[j][i])
                visited[j] = 1;
        }
    }

    // resetam nodurile vizitate
    free(visited);
    visited = calloc(gica.n, sizeof(int));
    for (i = 0; i < gica.n; i++)
        if (gica.warehouses[i])
            visited[i] = 1;

    printf("%d\n", nr);

    // mai parcurgem odata pentru a afisa componentele tare conexe propriu zise
    m = 0;
    for (i = 0; i < gica.n; i++) {
        if (visited[i])
            continue;
        scc[m++] = i;
        visited[i] = 1;
        for (j = 0; j < gica.n; j++) {
            if (visited[j] || i == j)
                continue;
            if (stores[i][j] && stores[j][i]) {
                scc[m++] = j;
                visited[j] = 1;
            }
        }
        if (newLine)
            printf("\n");
        else
            newLine = 1; // ca sa nu afisam un new line in plus, serios?
        for (j = 0; j < m - 1; j++)
            printf("%d ", scc[j]);
        printf("%d", scc[j]);
        m = 0;
    }

    // eliberare memorie
    for (i = 0; i < gica.n; i++)
        free(stores[i]);
    free(stores);
    free(visited);
    free(scc);
}

void e3(firm gica) {
    int r, i, j;
    double costMin, cost;
    /* o sa facem o structura doar cu nodurile pe care trebuie sa le parcurgem
       si depozitele*/
    firm sccNodes;
    scanf("%d", &r); // cate grupuri de noduri avem de parcurs
    // printf("%d\n", r);
    int k, *scc; // vector cu nodurile ce trebuie parcurse
    sccNodes.d = gica.d;
    for (i = 0; i < r; i++) {
        scanf("%d", &sccNodes.n);
        scc = malloc((sccNodes.d + sccNodes.n) * sizeof(int));
        for (j = 0; j < sccNodes.n; j++)
            scanf("%d", &scc[j]);
        // adaugam depozitele in vectorul cu noduri ca sa facem matricea usor
        for (j = 0; j < gica.n; j++)
            if (gica.warehouses[j])
                scc[sccNodes.n++] = j;
        /* for (j = 0; j < sccNodes.n; j++)
            printf("%d ", scc[j]);
        printf("\n"); */

        // facem o alta matrice de adiacenta
        sccNodes.graph = malloc(sccNodes.n * sizeof(double *));
        for (j = 0; j < sccNodes.n; j++)
            sccNodes.graph[j] = malloc(sccNodes.n * sizeof(double));
        sccNodes.warehouses = NULL;
        for (j = 0; j < sccNodes.n; j++)
            for (k = 0; k < sccNodes.n; k++) {
                sccNodes.graph[j][k] = gica.graph[scc[j]][scc[k]];
            }
        // incepem dijkstra plecand din fiecare depozitele si luam minimul
        costMin = INT_MAX;
        for (j = sccNodes.n - sccNodes.d; j < sccNodes.n; j++) {
            cost = dijkstraAllNodes(sccNodes, j);
            if (costMin > cost)
                costMin = cost;
        }
        if (i != 0)
            printf("\n"); // mda
        printf("%.1f", costMin);

        freeFirm(&sccNodes);
        free(scc);
    }
}

int main() {
    firm gica;
    char task[3];
    int nr, i;
    readFirm(&gica);

    scanf("%d", &nr); // nr taskuri
    for (i = 0; i < nr; i++) {
        if (i != 0)
            printf("\n");
        scanf("%s", task);
        if (!strcmp(task, "e1"))
            e1(gica);
        else if (!strcmp(task, "e2"))
            e2(gica);
        else if (!strcmp(task, "e3"))
            e3(gica);
    }

    freeFirm(&gica);
}
