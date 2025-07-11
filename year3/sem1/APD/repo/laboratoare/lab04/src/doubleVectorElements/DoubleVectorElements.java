package doubleVectorElements;

public class DoubleVectorElements extends Thread {
    int N = 100000013;
    int[] v = new int[N];
    int id;
    int P;

    public DoubleVectorElements(int N, int[] v, int id, int P) {
        this.id = id;
        this.N = N;
        this.v = v;
        this.P = P;
    }

    public void run() {
        int start = (int) (id * (double)N / P);
        int end = (int) Math.min((id + 1) * (double)N / P, N);

        for (int i = start; i < end; i++) {
            v[i] *= 2;
        }
    }
}
