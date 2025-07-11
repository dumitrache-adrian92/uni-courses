package p2;

public class Graph{
    MyList[] noduri;
    boolean[] vizitat;

    public Graph(int n) {
        noduri = new MyList[n];
        vizitat = new boolean[n];

        for (int i = 0; i < n; i++) {
            noduri[i] = new MyList();
            vizitat[i] = false;
        }
    }

    public void add(int x, int y) {
        noduri[x - 1].add(y - 1);
    }

    public String toString() {
        String result = "";

        for (int i = 0; i < noduri.length; i++) {
            result += i + ": " + noduri[i].toString() + "\n";
        }
        return result;
    }

    public void dfs(int start) {
        int i = 0;
        System.out.println(start);
        vizitat[start - 1] = true;
        while (noduri[start - 1].get(i) != null) {
            //System.out.println(noduri[start - 1].get(i));
            if (!vizitat[(int)noduri[start - 1].get(i)])
                dfs((int)noduri[start - 1].get(i) + 1);
            i++;
        }
    }
}
