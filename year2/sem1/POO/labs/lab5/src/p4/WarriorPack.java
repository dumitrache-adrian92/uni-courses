package p4;

/**
 * 
 */
import java.util.*;

public class WarriorPack {
    private Vector warriors ;

    public WarriorPack () {
        warriors = new Vector();
    }

    public void addWarrior(Warrior newWarrior) {
        warriors.add(newWarrior);
    }

    public Vector getWarriors() {
        return warriors ;
    }

    public int calculateDamage() {
        int damage = 0;
        for (int i = 0; i < warriors.size(); i++) {

        }
        return damage;
    }

    public String toString() {
        String result = "";
        Warrior cast;

        for (Object w:getWarriors()) {
            cast = (Warrior) w;
            result += cast.getClass() + "Warrior " +
                        "health=" + cast.getHealth() +
                        ", name='" + cast.getName() + '\'' + '\n';
            }
        return result;
    }
}
