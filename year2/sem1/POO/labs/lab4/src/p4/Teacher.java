package p4;

import java.util.Vector;

public class Teacher extends Person{
    Vector courses;

    public Teacher(String name, String address){
        super(name, address);
        courses = new Vector();
    }

    public String toString() {
        return super.toString();
    }

    public boolean addCourse(String course) {
        if (course.contains(course) == false) {
            courses.add(course);
            return true;
        }
        return false;
    }

    public boolean removeCourse(String course) {
        return courses.remove(course);
    }
}
