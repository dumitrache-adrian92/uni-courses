import java.util.List;

/**
 * Scheduling strategy that assigns tasks to the host with the shortest queue
 * of tasks left to be executed.
 */
public class ShortestQueueScheduling extends SchedulingStrategy {
    public ShortestQueueScheduling(List<Host> hosts) {
        super(hosts);
    }

    @Override
    public Host getScheduledHost(Task task) {
        // get host with shortest queue
        Host shortestHost = hosts.get(0);
        for (Host host : hosts) {
            if (host.getQueueSize() < shortestHost.getQueueSize()) {
                shortestHost = host;
            }
        }

        return shortestHost;
    }
}
