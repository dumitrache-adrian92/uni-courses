package p3;

public class Main {
    public static void main(String[] args) {
        Channel gamingHardcore = new Channel("Gaming Hardcore");
        User u1 = new User();
        User u2 = new User();

        gamingHardcore.subscribe(u1);
        gamingHardcore.subscribe(u2);

        gamingHardcore.notify("New video: Minecraft Ep. 1");
        gamingHardcore.unsubscribe(u2);
        gamingHardcore.notify("New video: Minecraft Ep. 2");

        System.out.println(u1.getWatchlist());
        System.out.println(u2.getWatchlist());
    }
}
