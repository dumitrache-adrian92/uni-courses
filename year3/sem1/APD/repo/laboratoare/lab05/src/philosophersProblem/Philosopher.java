package philosophersProblem;

import java.util.concurrent.Semaphore;

public class Philosopher implements Runnable {
    private final Semaphore leftFork;
    private final Semaphore rightFork;
    private final int id;
    private int N;

    public Philosopher(int id, Object leftFork, Object rightFork, int N) {
        this.leftFork = (Semaphore) leftFork;
        this.rightFork = (Semaphore) rightFork;
        this.id = id;
        this.N = N;
    }

    private void sleep() {
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            if (id != N - 1) {
                try {
                    leftFork.acquire();
                    try {
                        rightFork.acquire();
                        System.out.println("Philosopher " + id + " is eating");
                        leftFork.release();
                        rightFork.release();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } else {
                try {
                    rightFork.acquire();
                    try {
                        leftFork.acquire();
                        System.out.println("Philosopher " + id + " is eating");
                        leftFork.release();
                        rightFork.release();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
