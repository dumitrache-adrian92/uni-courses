package lab3.p7;

public class Route {
    String origin, destination;

    public Route(String o, String d) {
        origin = o;
        destination = d;
    }

    public boolean tur_retur(Route x) {
        return destination.equals(x.origin) && origin.equals(x.destination);
    }
}
