package readersWriters.writerPriority;

import java.util.concurrent.BrokenBarrierException;

public class Reader extends Thread {
    private final int id;

    public Reader(int id) {
        super();
        this.id = id;
    }

    @Override
    public void run() {
        try {
            Main.barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        }

        do {
            // TODO
            try {
                Main.enter.acquire();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            if (Main.currentWriters > 0 || Main.waitingWriters > 0) {
                Main.waitingReaders++;
                Main.enter.release();
                try {
                    Main.sem_reader.acquire();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }

            Main.currentReaders++;
            // TODO

            if (Main.waitingReaders > 0) {
                Main.waitingReaders--;
                Main.sem_reader.release();
            } else if (Main.waitingReaders == 0) {
                Main.enter.release();
            }

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Reader " + id + " is reading");
            Main.hasRead[id] = true;

            // TODO
            try {
                Main.enter.acquire();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            Main.currentReaders--;

            // TODO
            if (Main.currentReaders == 0) {
                Main.waitingWriters--;
                Main.sem_writer.release();
            } else if (Main.currentReaders > 0 || Main.waitingWriters == 0) {
                Main.enter.release();
            }

        } while (!Main.hasRead[id]);
    }
}
