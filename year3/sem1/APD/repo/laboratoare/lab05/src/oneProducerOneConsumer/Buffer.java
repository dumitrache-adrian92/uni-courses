package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

public class Buffer {
    private int a;

    Semaphore full = new Semaphore(0);
    Semaphore empty = new Semaphore(1);

    void put(int value) {
        try {
            empty.acquire();
            a = value;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        full.release();
    }

    int get() {
        int result;
        try {
            full.acquire();
            result = a;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        empty.release();

        return result;
    }
}
