package task2;
import java.util.*;

public class Catalog extends TreeSet<Catalog.Student> {
    public class Student implements Comparable {
        String name;
        double mean;
        int clazz;

        public Student(String name, double mean, int clazz) {
            this.name = name;
            this.mean = mean;
            this.clazz = clazz;
        }

        public String toString() {
            return "Student{" +
                    "name='" + name + '\'' +
                    ", mean=" + mean +
                    ", clazz=" + clazz +
                    '}';
        }

        public int compareTo(Object o) {
            Student obj = (Student)o;
            if(o != null) {
                if (obj.mean == mean)
                    return name.compareTo(obj.name);
                else return (int) Double.compare(mean, obj.mean);
            }
            else return 0;
        }
    }

    public Catalog() {

    }

    public Catalog(Comparator c) {
        super(c);
    }

    public void addStudent(String name, double mean, int clazz) {
        add(new Student(name, mean, clazz));
    }

    public Student getStudent(String name) {
        Iterator i = iterator();
        Student current;
        while (i.hasNext()) {
            current = (Student)i.next();
            if (current.name.equals(name))
                return current;
        }
        return null;
    }

    public void removeStudent(String name) {
        Iterator i = iterator();
        Student current;
        while (i.hasNext()) {
            current = (Student)i.next();
            if (current.name.equals(name)) {
                remove(current);
                return;
            }
        }
    }

    public Catalog byClass (int clazz ) {
        List temp = new ArrayList();
        Catalog result = new Catalog(comparator());
        Iterator i = iterator();
        Student current;
        while (i.hasNext()) {
            current = (Student)i.next();
            if (current.clazz == clazz) {
                result.add(current);
            }
        }

        //Collections.sort(temp, comparator());

        //result.addAll(temp);

        return result;
    }

}