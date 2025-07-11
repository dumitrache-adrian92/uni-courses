package p3;

import java.util.Vector;

public class User {
    private Vector<String> watchlist = new Vector<String>();
    public void update(String notification) {
        watchlist.add(notification);
    }

    public Vector<String> getWatchlist() {
        return watchlist;
    }
}
