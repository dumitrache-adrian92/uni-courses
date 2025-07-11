import java.util.ArrayList;
import java.util.Hashtable;

public class ScoreVisitor implements Visitor {
    private Hashtable<Teacher, ArrayList<Tuple<Student, String, Double>>> examScores;
    private Hashtable<Assistant, ArrayList<Tuple<Student, String, Double>>> partialScores;

    public ScoreVisitor() {
        examScores = new Hashtable<>();
        partialScores = new Hashtable<>();
    }

    void addGrade(Teacher t, Student s, String courseName, Double grade) {
        if (examScores.get(t) == null)
            examScores.put(t, new ArrayList<>());

        examScores.get(t).add(new Tuple<>(s, courseName, grade));
    }

    void addGrade(Assistant t, Student s, String courseName, Double grade) {
        if (partialScores.get(t) == null)
            partialScores.put(t, new ArrayList<>());

        partialScores.get(t).add(new Tuple<>(s, courseName, grade));
    }

    public void visit(Assistant assistant) {
        for (Tuple<Student, String, Double> t : partialScores.get(assistant))
            for (Course c : Catalog.getInstance().getCourses())
                if (c.getName().equals(t.getCourseName())) {
                    if (c.getGrade(t.getStudent()) == null) {
                        Grade newGrade = new Grade(t.getStudent(), t.getCourseName());
                        newGrade.setPartialScore(t.getGrade());
                        c.addGrade(newGrade);
                    } else
                        c.getGrade(t.getStudent()).setPartialScore(t.getGrade());

                    Catalog.getInstance().notifyObservers(c.getGrade(t.getStudent()));

                    break;
                }

        partialScores.get(assistant).clear();
    }

    public void visit(Teacher teacher) {
        for (Tuple<Student, String, Double> t : examScores.get(teacher))
            for (Course c : Catalog.getInstance().getCourses())
                if (c.getName().equals(t.getCourseName())) {
                    if (c.getGrade(t.getStudent()) == null) {
                        Grade newGrade = new Grade(t.getStudent(), t.getCourseName());
                        newGrade.setExamScore(t.getGrade());
                        c.addGrade(newGrade);
                    } else
                        c.getGrade(t.getStudent()).setExamScore(t.getGrade());

                    Catalog.getInstance().notifyObservers(c.getGrade(t.getStudent()));

                    break;
                }

        examScores.get(teacher).clear();
    }

    public Hashtable<Teacher, ArrayList<Tuple<Student, String, Double>>> getExamScores() {
        return examScores;
    }

    public void setExamScores(Hashtable<Teacher, ArrayList<Tuple<Student, String, Double>>> examScores) {
        this.examScores = examScores;
    }

    public Hashtable<Assistant, ArrayList<Tuple<Student, String, Double>>> getPartialScores() {
        return partialScores;
    }

    public void setPartialScores(Hashtable<Assistant, ArrayList<Tuple<Student, String, Double>>> partialScores) {
        this.partialScores = partialScores;
    }

    private static class Tuple<S, N, G> {
        private final S student;
        private final N courseName;
        private final G grade;

        public Tuple(S student, N courseName, G grade) {
            this.student = student;
            this.courseName = courseName;
            this.grade = grade;
        }

        public S getStudent() {
            return student;
        }

        public N getCourseName() {
            return courseName;
        }

        public G getGrade() {
            return grade;
        }

        public String toString() {
            return student + ": " + grade + " in " + courseName;
        }
    }
}
