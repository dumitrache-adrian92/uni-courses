package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;

public class Buffer {
	int value;

	ArrayBlockingQueue<Integer> queue = new ArrayBlockingQueue<Integer>(Main.N);

	void put(int value) {
		try {
			queue.put(value);
		} catch (InterruptedException e) {
			throw new RuntimeException(e);
		}
	}

	int get() {
		return queue.poll();
	}
}
