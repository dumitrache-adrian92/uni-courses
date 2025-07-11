import java.util.List;

/**
 * Least work left scheduling strategy, assigns tasks to the host that has the
 * queue with the least amount of work left in milliseconds.
 */
public class LeastWorkLeftScheduling extends SchedulingStrategy {
    public LeastWorkLeftScheduling(List<Host> hosts) {
        super(hosts);
    }

    @Override
    public Host getScheduledHost(Task task) {
        Host leastWorkLeftHost = hosts.get(0);

        for (Host host : hosts) {
            if (host.getWorkLeft() < leastWorkLeftHost.getWorkLeft()) {
                leastWorkLeftHost = host;
            }
        }

        return leastWorkLeftHost;
    }
}
