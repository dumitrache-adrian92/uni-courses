/* Implement this class. */

import java.util.PriorityQueue;
import java.util.concurrent.PriorityBlockingQueue;
import java.util.concurrent.Semaphore;

/**
 * Class for a host that runs tasks based on their priority.
 * Given multiple tasks, it will always run the one with the highest priority.
 * In case of a tie, the task with the earliest start time will be run first.
 * It supports preemption, meaning that if a task with a higher priority arrives
 * while a lower priority task is running, the new task will start running
 * instead.
 */
public class MyHost extends Host {
    private PriorityBlockingQueue<Task> tasks;
    private Semaphore taskCount;
    private Task currentTask;
    private double currentTaskStartTime;
    private Boolean isShutdown;

    public MyHost() {
        // queue that prioritizes tasks in reverse order of priority, and in
        // case of a tie, in order of start time
        tasks = new PriorityBlockingQueue<>(100,(o1, o2) -> {
            int priorityDif = o2.getPriority() - o1.getPriority();
            int startDif = o1.getStart() - o2.getStart();

            return priorityDif != 0 ? priorityDif : startDif;
        });
        taskCount = new Semaphore(0);

        isShutdown = false;
    }

    @Override
    public void run() {
        try {
            while (!isShutdown) {
                // grab the next task or wait for one to be added
                taskCount.acquire();
                currentTask = tasks.poll();

                // run the task and time it
                currentTaskStartTime = Timer.getTimeDouble();
                synchronized (this) {
                    wait(currentTask.getLeft());
                }
                double timePassedSecs = Math.round(Timer.getTimeDouble() - currentTaskStartTime);
                long timePassedMillis = (long) timePassedSecs * 1000;

                // determine whether the task finished completely or was preempted
                if (timePassedMillis >= currentTask.getLeft()) {
                    currentTask.finish();
                } else {
                    // update the task's remaining time and add it back to the queue
                    currentTask.setLeft(currentTask.getLeft() - timePassedMillis);
                    addTask(currentTask);
                }

                currentTask = null;
            }
        } catch (InterruptedException e) {
            // the thread was shutdown while waiting for a task, so exit
            interrupt();
        }
    }

    @Override
    public void addTask(Task task) {
        tasks.add(task);
        taskCount.release();

        // stop the current task if it is preemptible and the new task has a higher priority
        if (currentTask != null && currentTask.isPreemptible()
                && currentTask.getPriority() < task.getPriority()) {
            synchronized (this) {
                notifyAll();
            }
        }
    }

    @Override
    public int getQueueSize() {
        return tasks.size() + (currentTask == null ? 0 : 1);
    }

    @Override
    public long getWorkLeft() {
        long workLeft = 0;

        // add the current task's remaining time to the total
        if (currentTask != null) {
            long currentTaskTimePassed = Math.round(Timer.getTimeDouble() - currentTaskStartTime) * 1000;
            workLeft += currentTask.getLeft() - currentTaskTimePassed;
        }

        // add the remaining time of each task in the queue to the total
        for (Task task : tasks) {
            workLeft += task.getLeft();
        }

        return workLeft;
    }

    @Override
    public void shutdown() {
        isShutdown = true;
        interrupt();
    }
}
