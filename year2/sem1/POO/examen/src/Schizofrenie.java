class Ana {
    public void print(Ana p) {
        System.out.println("Ana 1\n");
    }
}
class Mihai extends Ana {
    public void print(Ana p) {
        System.out.println("Mihai 1\n");
    }
    public void print(Mihai l) {
        System.out.println("Mihai 2\n");
    }
}
class Dana extends Mihai {
    public void print(Ana p) {
        System.out.println("Dana 1\n");
    }
    public void print(Mihai l) {
        System.out.println("Dana 2\n");
    }
    public void print(Dana b) {
        System.out.println("Dana 3\n");
    }
}

public class Schizofrenie {
    public static void main (String [] args) {
        Mihai stud1 = new Dana();
        Ana stud2 = new Mihai();
        Ana stud3 = new Dana();
        Dana stud4 = new Dana();
        Mihai stud5 = new Mihai();
        stud1.print(new Ana()); // Dana 1
        ((Dana) stud1).print(new Mihai()); // Dana2
        ((Mihai) stud2).print(new Ana()); // Mihai 1
        stud2.print(new Dana()); // Mihai 1
        stud2.print(new Mihai()); // Mihai 1
        stud3.print(new Dana()); // Dana 1
        stud3.print(new Ana()); // Dana 1
        stud3.print(new Mihai()); // Dana 1
        ((Dana) stud3).print(new Mihai()); // Dana 2
        ((Dana) stud3).print(new Dana()); // Dana 3
        stud4.print(new Dana()); // Dana 3
        stud4.print(new Ana()); // Dana 1
        stud4.print(new Mihai()); // Dana 2
        stud5.print(new Dana()); // Mihai 2
        stud5.print(new Mihai()); // Mihai 2
        stud5.print(new Ana()); // Mihai 1
        ((Ana) stud5).print(new Mihai()); // Mihai 1
    }
}
