package lab2.task3;

public class Point {
    float x, y;

    Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public void changeCoords(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}
