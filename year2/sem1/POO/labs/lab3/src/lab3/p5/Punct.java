package lab3.p5;

public class Punct {
    private int x, y;

    public Punct() {
        x = 0;
        y = 0;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    public double distance(int x2, int y2) {
        return Math.sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    }

    public double distance(Punct p1) {
        return Math.sqrt((p1.x - x) * (p1.x - x) + (p1.y - y) * (p1.y - y));
    }
}
