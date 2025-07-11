package p4;
import java.util.ArrayList;

public interface GenericInterface {
	//Sterge duplicatele dintr-o lista si returneaza lista rezultata
	public <E extends Comparable<E>> ArrayList<E> removeDuplicates(ArrayList<E> list);
	//Determina elementul maxim dintr-o lista
	public <E extends Comparable<E>> E max(ArrayList<E> list);
	//Cauta o valoare in lista sortata, folosind algoritmul de cautare binara si returneaza pozitia
	public <E extends Comparable<E>> int binarySearch(ArrayList<E> list, E key, int start, int end);
}
