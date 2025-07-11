import java.util.ArrayList;

public class FullCourse extends Course {
    protected FullCourse(CourseBuilder u) {
        super(u);
    }

    public static class FullCourseBuilder extends CourseBuilder {
        public FullCourseBuilder(String name, Teacher teacher, int credits) {
            super(name, teacher, credits);
        }

        public Course build() {
            return new FullCourse(this);
        }
    }

    public ArrayList<Student> getGraduatedStudents() {
        ArrayList<Student> result = new ArrayList<>();

        for (Grade g : getGrades())
            if (g.getPartialScore() >= 3.0 && g.getExamScore() >= 2.0)
                result.add(g.getStudent());

        return result;
    }
}
