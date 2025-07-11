package p4;

/**
 * 
 */
public class Warrior {
    //Stores one of the three above types
    //0 = dead, 100 = full strength
    private int health;
    private String name;

    public Warrior() {
        this(100, "unknown");
    }
    public Warrior (int health, String name) {
        this.health = health;
        this.name = name;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String toString() {
        return getClass() + "Warrior{" +
                "health=" + health +
                ", name='" + name + '\'' +
                '}';
    }
}
