public class Outer {
    public void outerMethod() {
        new Inner(); //works
    }

    class Inner { }

    public void main(String[] args) {
        Outer o = new Outer();

        new Outer.Inner();
    }
}