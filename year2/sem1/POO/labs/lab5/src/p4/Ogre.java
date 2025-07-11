package p4;

public class Ogre extends Warrior{
    public Ogre () {
        this(100, "unknown");
    }

    public Ogre (int health, String name) {
        super(health, name);
    }

    public int getDamage() {
        return 6;
    }
}
