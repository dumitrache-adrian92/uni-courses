package lab2.task1;
public class Complex {
    private int real, imaginary;

    Complex(int real, int imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    Complex() {
        this(0, 0);
    }

    Complex(Complex src) {
        real = src.real;
        imaginary = src.imaginary;
    }

    public int getReal() {
        return real;
    }

    public int getImaginary() {
        return imaginary;
    }

    public void setReal(int real) {
        this.real = real;
    }

    public void setImaginary(int imaginary) {
        this.imaginary = imaginary;
    }

    public void addWithComplex(Complex toAdd) {
        real += toAdd.real;
        imaginary += toAdd.imaginary;
    }

    public void showNumber() {
        if (imaginary == 0)
            System.out.println(real);
        else if (imaginary > 0)
            System.out.println(real + " + i * " + imaginary);
        else
            System.out.println(real + " - i * " + imaginary);
    }
}
