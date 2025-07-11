package p4;

import java.util.Vector;

public class Student extends Person {
    Vector courses;
    Vector grades;

    public Student() {
        this("Unknown", "Unknown");
    }

    public Student(String name, String address) {
        super(name, address);
        courses = new Vector();
        grades = new Vector();
    }

    public String toString() {
        return "Person{" +
                "name='" + super.getName() + '\n' +
                ", address='" + super.getAddress() + '\n' +
                '}';
    }

    public void addCourseGrade(String course, Integer grade) {
        courses.add(course);
        grades.add(grade);
    }

    public void printGrades() {
        System.out.println(courses);
        System.out.println(grades);
    }

    public double getAverageGrade() {
        double sum = 0;
        for (Object x:grades) {
            sum += (double)x;
        }
        return sum;
    }
}
