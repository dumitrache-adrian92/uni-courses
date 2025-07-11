package p3;
import java.util.ArrayList;

public abstract class AMatrix<T extends Number> extends ArrayList<ArrayList<T>> {
	public abstract AMatrix<T> addition(AMatrix<T> m1);
	
	// Aduna doua elemente de tip T si intoarce rezultatul
	public abstract T sum(T obj1, T obj2);
}
