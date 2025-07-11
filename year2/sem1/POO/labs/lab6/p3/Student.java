package p3;

import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;

    class MyComp implements Comparator {
        public int compare(Object o1, Object o2) {
            if (o1 == null || o2 == null)
                throw new NullPointerException ();

            if (!( o1 instanceof Student ) || !( o2 instanceof Student ))
                throw new ClassCastException ("Nu pot compara!");

            Student s1 = (Student) o1;
            Student s2 = (Student) o2;

            if (s1.getNume().equals(s2.getNume()))
                return (int)s1.calculMedieGenerala() - (int)s2.calculMedieGenerala();
            return s1.getNume().compareTo(s2.getNume());
        }
    }

public class Student implements Persoana{
    private String nume;
    private Vector medii;

    public Student(String nume) {
        this.nume = nume;
        medii = new Vector();
    }

    public double calculMedieGenerala() {
        double result = 0;
        for (int i = 0; i < medii.size(); i++)
            result += (double)medii.get(i);
        return result / medii.size();
    }

    public void addMedie(double medie) {
        medii.add(medie);
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String toString() {
        return nume;
    }

    public int compareTo(Object o) {
        if (o == null)
            throw new NullPointerException ();

        if (!( o instanceof Student ))
            throw new ClassCastException ("Nu pot compara!");

        Student s = (Student) o;

        if (nume.equals(s.nume))
            return (int)calculMedieGenerala() - (int)s.calculMedieGenerala();
        return nume.compareTo(s.nume);
    }

    public static void main(String[] args) {
        Vector v = new Vector();
        v.add(new Student("Gica"));
        v.add(new Student("Andrei"));
        v.add(new Student("Moartea"));
        v.add(new Student("Tunak"));
        Collections.sort(v, new MyComp());
        for (int i = 0; i < v.size(); i++)
            System.out.println(v.get(i));
    }
}
