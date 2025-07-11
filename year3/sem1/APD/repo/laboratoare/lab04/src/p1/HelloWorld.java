package p1;

public class HelloWorld extends Thread {
    int id;

    public HelloWorld(int id) {
        this.id = id;
    }

    public void run() {
        System.out.println("Hello from thread " + id);
    }
}
