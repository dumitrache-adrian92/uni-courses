package p4;

public class Snake extends Warrior{
    public Snake (int health, String name) {
        super(health, name);
    }
    public Snake () {
        this(100, "unknown");
    }

    public int getDamage() {
        return 10;
    }
}
