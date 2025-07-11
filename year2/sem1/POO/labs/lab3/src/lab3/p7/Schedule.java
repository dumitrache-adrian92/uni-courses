package lab3.p7;

public class Schedule {
    ClockTime departure;
    ClockTime arrival;

    public Schedule(ClockTime d, ClockTime a) {
        departure = d;
        arrival = a;
    }

    public int duration() {
        return departure.compare(arrival);
    }
}
