import java.util.List;

/**
 * Round robin scheduling strategy, assigns tasks to `lastHostID + 1 % hostCount`
 * host on each call to `getScheduledHost`.
 */
public class RoundRobinScheduling extends SchedulingStrategy {
    private int lastHostID;
    private int hostCount;

    RoundRobinScheduling(List<Host> hosts) {
        super(hosts);
        lastHostID = -1; // will be incremented to 0 on first call to getScheduledHost
        hostCount = hosts.size();
    }

    @Override
    public Host getScheduledHost(Task task) {
        // get next host and update lastHostID
        lastHostID = (lastHostID + 1) % hostCount;
        return hosts.get(lastHostID);
    }
}
