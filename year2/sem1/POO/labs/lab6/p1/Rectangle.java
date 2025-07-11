package p1;

public class Rectangle extends Shape {
    private double width;
    private double length;

    public Rectangle() {
        super();
        width = 0;
        length = 0;
    }

    public Rectangle(double width, double length) {
        this();
        this.width = width;
        this.length = length;
    }

    public Rectangle(double width, double length, String color, boolean filled)  {
        super(color, filled);
        this.width = width;
        this.length = length;
    }
    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getArea() {
        return width * length;
    }

    public double getPerimeter() {
        return 2 * length + 2 * width;
    }

    public String toString() {
        return "Width = " + width + "\nLength = " + length + "\nColor = " + getColor() + "\nFilled = " + isFilled();
    }
}
