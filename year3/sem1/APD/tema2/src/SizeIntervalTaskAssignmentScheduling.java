import java.util.List;

/**
 * Scheduling strategy that assigns tasks based on the task type (short,
 * medium, long) to a corresponding host that only accepts tasks of that type.
 */
public class SizeIntervalTaskAssignmentScheduling extends SchedulingStrategy {
    public SizeIntervalTaskAssignmentScheduling(List<Host> hosts) {
        super(hosts);
    }

    @Override
    public Host getScheduledHost(Task task) {
        switch (task.getType()) {
            case SHORT -> {
                return hosts.get(0);
            }
            case MEDIUM -> {
                return hosts.get(1);
            }
            case LONG -> {
                return hosts.get(2);
            }
            default -> {
                return null;
            }
        }
    }
}
