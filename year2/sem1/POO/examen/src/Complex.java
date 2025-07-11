import java.util.Vector;

public class Complex implements Comparable<Complex>{
    private int re, im;

    public Complex(int re, int im) {
        this.re = re;
        this.im = im;
    }

    public Complex() {
        this(0, 0);
    }

    public String toString() {
        return re + " " + im;
    }

    public int getRe() {
        return re;
    }

    public void setRe(int re) {
        this.re = re;
    }

    public int getIm() {
        return im;
    }

    public void setIm(int im) {
        this.im = im;
    }

    public int compareTo(Complex other) {
        if (re - other.re != 0)
            return re - other.re;
        else
            return other.im - im;
    }

    public static void main(String[] args) {
        Vector<Complex> v = new Vector<>();
        v.add(new Complex());
        v.add(new Complex(1, 3));
        v.add(new Complex(7, 8));
        v.add(new Complex(1, 4));

        v.sort(null);

        System.out.println(v);
    }
}
