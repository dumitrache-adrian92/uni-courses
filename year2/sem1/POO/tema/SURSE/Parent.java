import java.util.Vector;

public class Parent extends User implements Observer {
    private Vector<Notification> notifications = new Vector<>();

    public Parent(String firstName, String lastName) {
        super(firstName, lastName);
    }

    public Vector<Notification> getNotifications() {
        return notifications;
    }

    public void update(Notification notification) {
        notifications.add(notification);
    }
}
