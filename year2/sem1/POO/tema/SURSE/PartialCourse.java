import java.util.ArrayList;

public class PartialCourse extends Course {
    protected PartialCourse(CourseBuilder u) {
        super(u);
    }

    public static class PartialCourseBuilder extends CourseBuilder {
        public PartialCourseBuilder(String name, Teacher teacher, int credits) {
            super(name, teacher, credits);
        }

        public Course build() {
            return new PartialCourse(this);
        }
    }


    public ArrayList<Student> getGraduatedStudents() {
        ArrayList<Student> result = new ArrayList<>();

        for (Grade g : getGrades())
            if (g.getTotal() >= 5.0)
                result.add(g.getStudent());

        return result;
    }
}
