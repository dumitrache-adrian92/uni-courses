public class Grade implements Comparable, Cloneable{
    private Double partialScore, examScore;
    private Student student;
    private String course;

    public int compareTo(Object o) {
        Grade g = (Grade) o;

        return (int) (getTotal() - g.getTotal());
    }

    public Grade(Student student, String course) {
        this.student = student;
        this.course = course;
        partialScore = 0.0;
        examScore = 0.0;
    }

    public Double getTotal() {
        return partialScore + examScore;
    }

    public Double getPartialScore() {
        return partialScore;
    }

    public Object clone() {
        Grade result = new Grade(student, course);

        if (partialScore != null)
            result.partialScore = partialScore.doubleValue();
        else
            result.partialScore = null;

        if (examScore != null)
            result.examScore = examScore.doubleValue();
        else
            result.examScore = null;

        return result;
    }

    public String toString() {
        return partialScore + " " + examScore;
    }

    public void setPartialScore(Double partialScore) {
        this.partialScore = partialScore;
    }

    public Double getExamScore() {
        return examScore;
    }

    public void setExamScore(Double examScore) {
        this.examScore = examScore;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }
}
