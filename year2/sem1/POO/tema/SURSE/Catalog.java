import java.util.ArrayList;
import java.util.Vector;

public class Catalog implements Subject{
    private ArrayList<Course> courses;
    private Vector<Observer> observers;
    private static Catalog instance;
    private ScoreVisitor visitor;

    private Catalog() {
        courses = new ArrayList<>();
        observers = new Vector<>();
        visitor = new ScoreVisitor();
    }

    public static Catalog getInstance() {
        if (instance == null)
            instance = new Catalog();

        return instance;
    }

    public ArrayList<Course> getCourses() {
        return courses;
    }

    public void setCourses(ArrayList<Course> courses) {
        this.courses = courses;
    }

    public ScoreVisitor getVisitor() {
        return visitor;
    }

    public void setVisitor(ScoreVisitor visitor) {
        this.visitor = visitor;
    }

    public void addCourse(Course course) {
        courses.add(course);
    }

    public void removeCourse(Course course) {
        courses.remove(course);
    }

    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    public void notifyObservers(Grade grade) {
        for (Observer i : observers)
            if (i.equals(grade.getStudent().getFather()) || i.equals(grade.getStudent().getMother()))
                i.update(new Notification(grade));
    }

    public Vector<Observer> getObservers() {
        return observers;
    }
}
