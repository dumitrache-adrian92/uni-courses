import java.util.List;

/**
 * Abstract class for a scheduling strategy.
 */
public abstract class SchedulingStrategy {
    List<Host> hosts;

    /**
     * Instantiated a scheduling strategy object.
     *
     * @param hosts lists of hosts the scheduling strategy assigns tasks to
     */
    protected SchedulingStrategy(List<Host> hosts) {
        this.hosts = hosts;
    }

    /**
     * Returns the host that should execute the given task.
     *
     * @param task task to be scheduled
     * @return host that should execute the given task
     */
    public abstract Host getScheduledHost(Task task);
}
