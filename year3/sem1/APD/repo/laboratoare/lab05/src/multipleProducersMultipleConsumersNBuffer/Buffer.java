package multipleProducersMultipleConsumersNBuffer;

import java.util.Queue;
import java.util.concurrent.Semaphore;

public class Buffer {
    
    Queue<Integer> queue;

    Semaphore full;
    Semaphore empty;
    Semaphore mutex = new Semaphore(1);
    
    public Buffer(int size) {
        queue = new LimitedQueue<>(size);
        empty = new Semaphore(size);
        full = new Semaphore(0);
    }

	public void put(int value) {
        try {
            empty.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            mutex.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        queue.add(value);
        mutex.release();
        full.release();
	}

	public int get() {
        int a = -1;
        try {
            full.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            mutex.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        Integer result = queue.poll();
        if (result != null) {
            a = result;
        }
        mutex.release();
        empty.release();
        return a;
	}
}
