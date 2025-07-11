import java.util.Comparator;
import java.util.Objects;
import java.util.Vector;

public class Group<Student> extends Vector{
    private Assistant assistant;
    private String ID;
    private Comparator<Student> comp = null;

    public Group(Assistant assistant, String ID) {
        this.assistant = assistant;
        this.ID = ID;
    }

    public Group(Assistant assistant, String ID, Comparator<Student> comp) {
        this.assistant = assistant;
        this.ID = ID;
        this.comp = comp;
    }

    public boolean equals(Object o) {
        Group g = (Group) o;
        return ID.equals(g.getID());
    }

    public Assistant getAssistant() {
        return assistant;
    }

    public void setAssistant(Assistant assistant) {
        this.assistant = assistant;
    }

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public Comparator<Student> getComp() {
        return comp;
    }

    public void setComp(Comparator<Student> comp) {
        this.comp = comp;
    }
}
