package p2;

class Animal {
    public void sound() {
        System.out.println("aaaa");
    }
}

class Cat extends Animal {
    public void sound() {
        System.out.println("meow");
    }
}

class Dog extends Animal {
    public void sound() {
        System.out.println("bark");
    }
}

public class Main {
    public static void playWithAnimal(Animal a) {
        a.sound();
        a.sound();
    }

    public static void main(String[] args) {
        Dog d = new Dog();
        playWithAnimal(d);
    }
}
