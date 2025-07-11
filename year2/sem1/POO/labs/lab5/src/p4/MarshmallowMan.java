package p4;

public class MarshmallowMan extends Warrior{


    public MarshmallowMan(int health, String name) {
        super(health, name);
    }
    public MarshmallowMan() {
        this(100, "unknown");
    }

    public int getDamage() {
        return 1;
    }
}
