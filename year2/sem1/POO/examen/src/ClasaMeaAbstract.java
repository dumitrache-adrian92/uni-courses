abstract class ClasaMeaAbstract {
    abstract void metoda1();

    void metoda2() {
        System.out.println("That");
    }
}

class ClasaMea extends ClasaMeaAbstract {
    void metoda1() {
        System.out.println("This");
    }

    public static void main(String[] args) {
        ClasaMeaAbstract x = new ClasaMea();

        x.metoda1();
        x.metoda2();
    }
}