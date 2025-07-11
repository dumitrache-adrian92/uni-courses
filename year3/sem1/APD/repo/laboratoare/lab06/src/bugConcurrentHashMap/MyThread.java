package bugConcurrentHashMap;

import java.util.concurrent.ConcurrentHashMap;

public class MyThread implements Runnable {
	public static ConcurrentHashMap<Integer, Integer> hashMap = new ConcurrentHashMap<>();
	private final int id;

	public MyThread(int id) {
		this.id = id;
	}

	private void addValue(int key, int value) {
		Integer prevVal = hashMap.putIfAbsent(key, value);

		if (prevVal != null) {
			hashMap.put(key, value + prevVal);
		}

//		hashMap.computeIfPresent(key, (k, v) -> v + value);
//		hashMap.computeIfAbsent(key, k -> value);
//		if (hashMap.containsKey(key)) {
//			hashMap.put(key, hashMap.get(key) + value);
//		} else {
//			hashMap.put(key, value);
//		}
	}
	
	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++) {
				addValue(i, 2 * i);
			}
		} else {
			for (int i = 0; i < Main.N; i++) {
				addValue(i, 3 * i);
			}
		}
	}
}
