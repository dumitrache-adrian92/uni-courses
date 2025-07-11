package shortestPathsFloyd_Warshall;

public class FloydWarshall extends Thread {
    int id;
    int[][] graph;
    int N;
    int P;

    public FloydWarshall(int[][] graph, int N, int ID, int P) {
        this.graph = graph;
        this.N = N;
        this.id = ID;
        this.P = P;
    }

    public void run() {
        int start = (int) (id * (double)N / P);
        int end = (int) Math.min((id + 1) * (double)N / P, N);

        for (int k = start; k < end; k++) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                }
            }
        }
    }
}
