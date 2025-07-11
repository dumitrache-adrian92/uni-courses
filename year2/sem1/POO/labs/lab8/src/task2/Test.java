package task2;

public class Test {
    public static void main(String[] args) {
        Catalog catalog = new Catalog();
        catalog.addStudent("Alexandru", 7, 324);
        catalog.addStudent("Ioana", 5, 321);
        catalog.addStudent("Maria", 10, 322);
        catalog.addStudent("Ionut", 6.2, 323);
        catalog.addStudent("Diana", 7, 322);

        System.out.println(catalog.getStudent("Diana").compareTo(catalog.getStudent("Maria")));

    }
}
