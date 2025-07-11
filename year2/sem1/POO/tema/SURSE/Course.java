import java.util.*;

public abstract class Course {
    private String name;
    private Teacher teacher;
    private HashSet<Assistant> assistants;
    private HashMap<String, Group<Student>> groups;
    private Vector<Grade> grades;
    private int credits;
    private BestStudentStrategy bestStudentCalculator;
    private Snapshot backup;

    public Course(CourseBuilder u) {
        this.name = u.name;
        this.teacher = u.teacher;
        this.assistants = u.assistants;
        this.groups = u.groups;
        this.grades = u.grades;
        this.credits = u.credits;
        bestStudentCalculator = u.strat;
        backup = new Snapshot();
    }

    public Student getBestStudent() {
        if (bestStudentCalculator != null)
            return bestStudentCalculator.getBestStudent(this);
        else return null;
    }

    public static abstract class CourseBuilder {
        private final String name;
        private final Teacher teacher;
        private HashSet<Assistant> assistants = new HashSet<>();
        private HashMap<String, Group<Student>> groups = new HashMap<>();
        private Vector<Grade> grades = new Vector<>();
        private BestStudentStrategy strat = null;
        private final int credits;

        protected CourseBuilder(String name, Teacher teacher, int credits) {
            this.name = name;
            this.teacher = teacher;
            this.credits = credits;
        }

        public CourseBuilder assistants(HashSet<Assistant> assistants) {
            this.assistants = assistants;
            return this;
        }

        public CourseBuilder groups(HashMap<String, Group<Student>> groups) {
            this.groups = groups;
            for (Group g : groups.values())
                assistants.add(g.getAssistant());
            return this;
        }

        public CourseBuilder grades(Vector<Grade> grades) {
            this.grades = grades;
            return this;
        }

        public CourseBuilder strat(BestStudentStrategy strat) {
            this.strat = strat;
            return this;
        }

        public abstract Course build();

        public String getName() {
            return name;
        }

        public Teacher getTeacher() {
            return teacher;
        }

        public HashSet<Assistant> getAssistants() {
            return assistants;
        }

        public HashMap<String, Group<Student>> getGroups() {
            return groups;
        }

        public Vector<Grade> getGrades() {
            return grades;
        }

        public int getCredits() {
            return credits;
        }
    }

    private class Snapshot {
        private Vector<Grade> backupGrades = new Vector<>();

        public Vector<Grade> getBackupGrades() {
            return backupGrades;
        }
    }

    public void makeBackup() {
        backup.getBackupGrades().clear();

        for (Grade g : grades)
            backup.getBackupGrades().add((Grade) g.clone());
    }

    public void undo() {
        grades.clear();
        for (Grade g : backup.backupGrades)
            grades.add((Grade) g.clone());
    }

    public void addAssistant(String ID, Assistant assistant) {
        groups.get(ID).setAssistant(assistant);

        if (assistants.contains(assistant) == false)
            assistants.add(assistant);
    }

    public void addStudent(String ID, Student student) {
        groups.get(ID).add(student);
    }

    public void addGroup(Group group) {
        groups.put(group.getID(), group);
        assistants.add(group.getAssistant());
    }

    public void addGroup(String ID, Assistant assistant) {
        groups.put(ID, new Group<>(assistant, ID));
    }

    public void addGroup(String ID, Assistant assist, Comparator<Student> comp) {
        groups.put(ID, new Group<>(assist, ID, comp));
    }

    public Grade getGrade(Student student) {
        for (Grade g : grades)
            if (student.equals(g.getStudent()))
                return g;

        return null;
    }

    public void addGrade(Grade grade) {
        grades.add(grade);
    }

    public ArrayList<Student> getAllStudents() {
        ArrayList<Student> result = new ArrayList<>();

        for (Group g : groups.values())
            result.addAll(g);

        return result;
    }

    public HashMap<Student, Grade> getAllStudentGrades() {
        HashMap<Student, Grade> result = new HashMap<>();

        for (Grade g : grades)
            result.put(g.getStudent(), g);

        return result;
    }

    public abstract ArrayList<Student> getGraduatedStudents();

    // getters/setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Teacher getTeacher() {
        return teacher;
    }

    public void setTeacher(Teacher teacher) {
        this.teacher = teacher;
    }

    public HashSet<Assistant> getAssistants() {
        return assistants;
    }

    public void setAssistants(HashSet<Assistant> assistants) {
        this.assistants = assistants;
    }

    public HashMap<String, Group<Student>> getGroups() {
        return groups;
    }

    public void setGroups(HashMap<String, Group<Student>> groups) {
        this.groups = groups;
    }

    public int getCredits() {
        return credits;
    }

    public void setCredits(int credits) {
        this.credits = credits;
    }

    public Vector<Grade> getGrades() {
        return grades;
    }

    public void setGrades(Vector<Grade> grades) {
        this.grades = grades;
    }

    public void setBestStudentCalculator(BestStudentStrategy bestStudentCalculator) {
        this.bestStudentCalculator = bestStudentCalculator;
    }

    public String toString() {
        return name;
    }
}
