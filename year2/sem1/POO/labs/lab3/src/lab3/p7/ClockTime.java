package lab3.p7;

public class ClockTime {
    int hour, minute;

    public ClockTime(int h, int m) {
        hour = h;
        minute = m;
    }

    public int compare(ClockTime x) {
        return 60 * x.hour + x.minute - 60 * hour - minute;
    }
}
