package p1;

public class StormFire extends BadLuck{
    void execute(Hero h) {
        h.damaged();
    }

    void execute(Warrior w) {
        w.damaged();
    }

    void execute(Ninja n) {
        n.damaged();
    }

    void execute(Rogue r) {
        r.damaged();
    }
}
