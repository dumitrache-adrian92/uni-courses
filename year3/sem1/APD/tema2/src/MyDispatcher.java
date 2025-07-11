/* Implement this class. */

import java.util.List;

/**
 * Dispatcher featuring multiple scheduling algorithms: round-robin, shortest
 * queue, size interval task assignment, and least work left.
 * The scheduling algorithm can be specified in the constructor.
 */
public class MyDispatcher extends Dispatcher {
    private SchedulingStrategy schedulingStrategy;

    public MyDispatcher(SchedulingAlgorithm algorithm, List<Host> hosts) {
        super(algorithm, hosts);

        if (algorithm == SchedulingAlgorithm.ROUND_ROBIN) {
            schedulingStrategy = new RoundRobinScheduling(hosts);
        } else if (algorithm == SchedulingAlgorithm.SHORTEST_QUEUE) {
            schedulingStrategy = new ShortestQueueScheduling(hosts);
        } else if (algorithm == SchedulingAlgorithm.SIZE_INTERVAL_TASK_ASSIGNMENT) {
            schedulingStrategy = new SizeIntervalTaskAssignmentScheduling(hosts);
        } else if (algorithm == SchedulingAlgorithm.LEAST_WORK_LEFT) {
            schedulingStrategy = new LeastWorkLeftScheduling(hosts);
        }
    }

    @Override
    public synchronized void addTask(Task task) {
        Host nextHost = schedulingStrategy.getScheduledHost(task);
        nextHost.addTask(task);
    }
}
