public class Notification {
    private Grade grade;

    public Notification(Grade grade) {
        this.grade = grade;
    }

    public String toString() {
            return "New grade in the " + grade.getCourse() + " course! " + "Current grade: " + grade.getTotal();
    }

    public Grade getGrade() {
        return grade;
    }
}
