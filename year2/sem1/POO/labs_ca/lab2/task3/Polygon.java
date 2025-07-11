package lab2.task3;

public class Polygon {
    Point[] points;

    public Polygon(int n) {
        points = new Point[n];
    }

    public Polygon(float[] p) {
        this(p.length / 2);
        System.out.println(p.length);
        int j = 0;
        for (int i = 0; i < points.length; i += 2) {
            points[j++] = new Point(p[i], p[i + 1]);
        }
    }

    public static void main(String[] args) {
        float[] arr = new float[]{ 1,2,3,4,5,6,7,8,9,10 };

        Polygon test = new Polygon(arr);
        for(int i = 0; i < 5; i++) {
            System.out.println(test.points[i]);
        }

    }
}
