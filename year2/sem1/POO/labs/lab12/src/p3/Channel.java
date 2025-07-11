package p3;

import java.util.ArrayList;

public class Channel {
    private String name;
    private ArrayList<User> users;

    public Channel(String name) {
        this.name = name;
        users = new ArrayList<User>();
    }

    public void subscribe(User u) {
        users.add(u);
    }

    public void unsubscribe(User u) {
        users.remove(u);
    }

    public void notify(String notification) {
        for (User u: users) {
            u.update(notification);
        }
    }

    @Override
    public String toString() {
        return "Channel{" +
                "name='" + name + '\'' +
                ", users=" + users +
                '}';
    }

}
