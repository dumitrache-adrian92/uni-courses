import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class Test {
    public static void main(String[] args) throws IOException {
        try (FileReader reader = new FileReader("src/catalog.json")) {
            // Read JSON file
            JSONObject doc = (JSONObject) JSONValue.parse(reader);

            // get course array
            JSONArray courseList = (JSONArray) doc.get("courses");

            // parse course array to add to catalog
            courseList.forEach(course -> parseCourse((JSONObject) course));

            // get array of exam scores
            JSONArray examScores = (JSONArray) doc.get("examScores");

            // parse array of exam scores and add them to the visitor
            examScores.forEach(score -> parseExamScore((JSONObject) score));

            // get array of partial scores
            JSONArray partialScores = (JSONArray) doc.get("partialScores");

            // parse array of partial scores and add them to the visitor
            partialScores.forEach(score -> parsePartialScore((JSONObject) score));

            new GUI();

            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));
            Catalog.getInstance().getCourses().get(0).addGrade(new Grade(new Student("a", "a"), "Programare Orientata pe Obiecte"));

            // test memento
            Catalog.getInstance().getCourses().get(0).makeBackup();
            Catalog.getInstance().getCourses().get(0).getGrades().clear();
            Catalog.getInstance().getCourses().get(0).undo();

            System.out.println(Catalog.getInstance().getCourses().get(0).getGrades());

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void parsePartialScore(JSONObject score) {
        JSONObject assistant = (JSONObject) score.get("assistant");
        String assistantName = assistant.get("firstName").toString() + " " + assistant.get("lastName").toString();
        Assistant a = null;

        for (Course c : Catalog.getInstance().getCourses())
            for (Assistant ass : c.getAssistants())
                if (ass.toString().equals(assistantName))
                    a = ass;

        if (Catalog.getInstance().getVisitor().getPartialScores().get(a) == null)
            Catalog.getInstance().getVisitor().getPartialScores().put(a, new ArrayList<>());

        JSONObject student = (JSONObject) score.get("student");
        String studentName = student.get("firstName").toString() + " " + student.get("lastName").toString();
        Student sFound = null;

        for (Course c : Catalog.getInstance().getCourses())
            for (Student s : c.getAllStudents())
                if (s.toString().equals(studentName))
                    sFound = s;

        Catalog.getInstance().getVisitor().addGrade(a, sFound, score.get("course").toString(), (Double) score.get("grade"));
    }

    private static void parseExamScore(JSONObject score) {
        JSONObject teacher = (JSONObject) score.get("teacher");
        String teacherName = teacher.get("firstName").toString() + " " + teacher.get("lastName").toString();
        Teacher t = null;

        for (Course c : Catalog.getInstance().getCourses())
            if (c.getTeacher().toString().equals(teacherName))
                t = c.getTeacher();

        if (Catalog.getInstance().getVisitor().getExamScores().get(t) == null)
            Catalog.getInstance().getVisitor().getExamScores().put(t, new ArrayList<>());

        JSONObject student = (JSONObject) score.get("student");
        String studentName = student.get("firstName").toString() + " " + student.get("lastName").toString();
        Student sFound = null;

        for (Course c : Catalog.getInstance().getCourses())
            for (Student s : c.getAllStudents())
                if (s.toString().equals(studentName))
                    sFound = s;

        Catalog.getInstance().getVisitor().addGrade(t, sFound, score.get("course").toString(), (Double) score.get("grade"));
    }

    private static void parseCourse(JSONObject course) {
        Course c;

        // create teacher object
        JSONObject teacherJSON = (JSONObject) course.get("teacher");
        Teacher teacher = (Teacher) UserFactory.factory("Teacher", teacherJSON.get("firstName").toString(), teacherJSON.get("lastName").toString());

        // create strategy
        BestStudentStrategy strategy;

        if (course.get("strategy").toString().equals("BestPartialScore"))
            strategy = new BestPartialScore();
        else if (course.get("strategy").toString().equals("BestExamScore"))
            strategy = new BestExamScore();
        else if (course.get("strategy").toString().equals("BestTotalScore"))
            strategy = new BestTotalScore();
        else
            strategy = null;

        // create assistant set
        HashSet<Assistant> assistants = new HashSet<>();

        JSONArray assistantsJSON = (JSONArray) course.get("assistants");

        for (int i = 0; i < assistantsJSON.size(); i++)
            assistants.add((Assistant) UserFactory.factory("Assistant",((JSONObject)assistantsJSON.get(i)).get("firstName").toString(),
                    ((JSONObject)assistantsJSON.get(i)).get("lastName").toString()));

        // create groups hashmap
        HashMap<String, Group<Student>> groups = new HashMap<>();

        JSONArray groupsJSON = (JSONArray) course.get("groups");

        for (int i = 0; i < groupsJSON.size(); i++) {
            JSONObject assistant = (JSONObject) ((JSONObject) groupsJSON.get(i)).get("assistant");
            String assistantName = assistant.get("firstName").toString() + " " + assistant.get("lastName").toString();
            Assistant groupAssistant = null;

            // check to see if assistant already exists in set, if not add the new assistant
            for (Assistant a : assistants)
                if (a.toString().equals(assistantName))
                    groupAssistant = a;
            if (groupAssistant == null) {
                groupAssistant = (Assistant) UserFactory.factory("Assistant",assistant.get("firstName").toString(),
                        assistant.get("lastName").toString());
                assistants.add(groupAssistant);
            }

            Group<Student> group = new Group(groupAssistant, ((JSONObject) groupsJSON.get(i)).get("ID").toString());

            // add students to group
            JSONArray studentsJSON = (JSONArray) ((JSONObject)groupsJSON.get(i)).get("students");

            for (int j = 0; j < studentsJSON.size(); j++) {
                // create student object
                Student s = (Student) UserFactory.factory("Student", ((JSONObject) studentsJSON.get(j)).get("firstName").toString(),
                        ((JSONObject) studentsJSON.get(j)).get("lastName").toString());

                JSONObject mother = (JSONObject) ((JSONObject) studentsJSON.get(j)).get("mother");

                if (mother != null) {
                    s.setMother((Parent) UserFactory.factory("Parent", mother.get("firstName").toString(), mother.get("lastName").toString()));
                    Catalog.getInstance().addObserver(s.getMother());
                }

                JSONObject father = (JSONObject) ((JSONObject) studentsJSON.get(j)).get("father");

                if (father != null) {
                    s.setFather((Parent) UserFactory.factory("Parent",father.get("firstName").toString(), father.get("lastName").toString()));
                    Catalog.getInstance().addObserver(s.getFather());
                }
                group.add(s);
            }

            groups.put(group.getID(), group);
        }


        if (course.get("type").equals("FullCourse")) {
            c = new FullCourse.FullCourseBuilder(course.get("name").toString(), teacher, 6)
                    .assistants(assistants)
                    .groups(groups)
                    .strat(strategy)
                    .build();
        }
        else if (course.get("type").equals("PartialCourse")) {
            c = new PartialCourse.PartialCourseBuilder(course.get("name").toString(), teacher, 6)
                    .assistants(assistants)
                    .groups(groups)
                    .strat(strategy)
                    .build();
        }
        else
            c = null;

        if (c != null)
            Catalog.getInstance().addCourse(c);
    }
}
