package p2;
import java.util.Vector;

public class SortedArray extends Array {
    public SortedArray() {
        super();
    }

    public void addElement(Integer x) {
        int i = 0;

        while(x > super.get(i) && i < super.getSize()) {
            i++;
        }

        if (i != super.getSize())
            super.addElement(x, i);
        else
            super.addElement(x);
    }

    public void addElement(Integer x, int poz) {
        addElement(x);
    }


}
