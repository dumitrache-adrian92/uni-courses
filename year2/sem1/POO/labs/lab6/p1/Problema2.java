package p1;

public class Problema2 {
    public static void main(String[] args) {
        //Rectangle r = new Shape(); imposibil, Shape nu poate sa fie instantiat
        Rectangle r = new Square(); //posibil
        Square s = new Square();
        r = s; //upcasting 1 nivel merge
        Shape sh = r; // upcasting 2 niveluri merge
        //Circle c = r; imposibil, Rectangle nu e parinte al lui Circle

        //Conversie 1
        Circle c1 = new Circle();
        //Square sq = (Square) c1; imposibil, Rectangle nu e parinte al lui Circle
        //Conversie 2
        Rectangle rect = new Rectangle(5.0, 5.0);
        Square sq = (Square) rect; // downcasting
        //Conversie 3
        sq = new Square(7.0);
        rect = sq; // upcasting
    }
}
