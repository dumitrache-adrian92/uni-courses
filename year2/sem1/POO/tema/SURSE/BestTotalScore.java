public class BestTotalScore implements BestStudentStrategy {
    public Student getBestStudent(Course course) {
        Student result = null;
        double grade = -1;

        for (Grade g : course.getGrades()) {
            if (g.getTotal() > grade) {
                result = g.getStudent();
                grade = g.getTotal();
            }
        }

        return result;
    }
}
