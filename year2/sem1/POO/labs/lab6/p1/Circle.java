package p1;

public class Circle extends Shape{
    private double radius;

    public Circle() {
        super();
        radius = 0;
    }

    public Circle(double radius) {
        this();
        this.radius = radius;
    }

    public Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }

    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    public String toString() {
        return "Radius = " + radius + "\nColor = " + getColor() + "\nFilled = " + isFilled();
    }
}
