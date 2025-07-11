package lab3.p7;

import java.time.Clock;

public class Train {
    Route r;
    Schedule s;
    boolean local;

    public Train(String o, String d, boolean loc, ClockTime departure, ClockTime arrival) {
        r = new Route(o, d);
        local = loc;
        s = new Schedule(departure, arrival);
    }

    public int price() {
        if (local == false)
            return 2 * s.duration();
        else
            return s.duration();
    }
}
