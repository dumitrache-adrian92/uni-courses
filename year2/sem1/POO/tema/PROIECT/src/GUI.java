import javax.swing.*;
import javax.swing.event.CaretEvent;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

public class GUI extends JFrame implements ActionListener, ListSelectionListener {
    private JButton studentButton = new JButton("Student");
    private JButton teacherButton = new JButton("Teacher");
    private JButton parentButton = new JButton("Parent");
    private JLabel error = new JLabel("click a button, see what happens");
    private JTextField name = new JTextField();
    private JList<Course> courses = new JList<>();
    private DefaultListModel<Course> coursesDLM = new DefaultListModel<>();
    private JScrollPane coursesScroll = new JScrollPane();
    private JPanel content = new JPanel();
    private JPanel courseInfo = new JPanel();
    private JLabel teacherName = new JLabel();
    private JList<Assistant> assistantList = new JList();
    private DefaultListModel<Assistant> assistantListDLM = new DefaultListModel<>();
    private JScrollPane assistantListScroll = new JScrollPane();
    private JLabel studentGrades = new JLabel();
    private JList<Course> teacherCourses = new JList();
    private DefaultListModel<Course> teacherCoursesDLM = new DefaultListModel<>();
    private JScrollPane teacherCoursesScroll = new JScrollPane();
    private JList toValidate = new JList();
    private DefaultListModel toValidateDLM = new DefaultListModel();
    private JScrollPane toValidateScroll = new JScrollPane();
    private JButton validateGrades = new JButton("Validate grades");
    private JList notifications = new JList();
    private DefaultListModel notificationsDLM = new DefaultListModel();
    private JScrollPane notificationsScroll = new JScrollPane();

    public GUI() {
        super();

        // basic settings
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(690, 690);
        setResizable(false);
        setLayout(null);

        // buttons for switching between pages
        studentButton.setForeground(Color.WHITE);
        teacherButton.setForeground(Color.WHITE);
        parentButton.setForeground(Color.WHITE);
        studentButton.setBackground(new Color(0x947969));
        teacherButton.setBackground(new Color(0x4B7666));
        parentButton.setBackground(new Color(0x475F42));
        studentButton.addActionListener(this);
        teacherButton.addActionListener(this);
        parentButton.addActionListener(this);

        // grid panel to hold switcher buttons
        JPanel pageSwitcher = new JPanel();
        pageSwitcher.setLayout(new GridLayout(1,3, 20, 5));
        pageSwitcher.add(studentButton);
        pageSwitcher.add(teacherButton);
        pageSwitcher.add(parentButton);
        pageSwitcher.setBounds(0, 0, 690, 30);

        add(pageSwitcher);

        // search bar
        name.setBounds(0, 30, 690,30);
        name.setHorizontalAlignment(SwingConstants.CENTER);

        add(name);

        // main content panel
        content.setBounds(0, 60, 690, 630);
        content.setLayout(null);

        add(content);

        // student screen

        // course scrollable list
        courses.addListSelectionListener(this);

        // sub panel of student screen for course info
        courseInfo.setLayout(null);
        courseInfo.setBounds(690 / 2, 0, 690 / 2, 630);

        // labels for teacher names and grades
        teacherName.setBounds(0, 25, 690/2 ,50);
        teacherName.setHorizontalAlignment(SwingConstants.CENTER);
        studentGrades.setBounds(0, 100, 690/2, 50);
        studentGrades.setHorizontalAlignment(SwingConstants.CENTER);

        courseInfo.add(assistantListScroll);
        courseInfo.add(teacherName);
        courseInfo.add(studentGrades);

        // teacher page
        validateGrades.setBounds(690/2 + 75, 525, 690/2 - 150, 50);
        validateGrades.addActionListener(this);

        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            if (e.getSource().equals(studentButton)) {
                // clear previous page
                content.removeAll();
                coursesDLM.removeAllElements();
                courses.removeAll();

                // find student's courses
                for (Course c : Catalog.getInstance().getCourses())
                    for (Student s : c.getAllStudents())
                        if(s.toString().strip().equals(name.getText().strip()))
                            coursesDLM.addElement(c);

                if (coursesDLM.isEmpty()) {
                    error.setText("Student not found.");
                    error.setBounds(0, 0, 690, 500);
                    error.setHorizontalAlignment(SwingConstants.CENTER);
                    error.setVerticalAlignment(SwingConstants.CENTER);
                    content.add(error);
                } else {
                    // show selectable list of courses
                    courses.setModel(coursesDLM);
                    coursesScroll.setViewportView(courses);
                    courses.setLayoutOrientation(JList.VERTICAL);
                    coursesScroll.setBounds(0, 0, 690 / 2, 630);
                    content.add(coursesScroll);
                }

                // reset to make changes visible
                content.revalidate();
                repaint();
                setVisible(true);
            }
            else if (e.getSource().equals(teacherButton)) {
                content.removeAll();
                teacherCoursesDLM.removeAllElements();
                teacherCourses.removeAll();
                toValidateDLM.removeAllElements();
                toValidate.removeAll();

                Teacher t = null;
                Assistant ass = null;
                // find courses
                for (Course c : Catalog.getInstance().getCourses()) {
                    if (c.getTeacher().toString().equals(name.getText().strip())) {
                        teacherCoursesDLM.addElement(c);
                        t = c.getTeacher();
                        continue;
                    }

                    for (Assistant a : c.getAssistants())
                        if (a.toString().equals(name.getText().strip())) {
                            teacherCoursesDLM.addElement(c);
                            ass = a;
                            break;
                        }
                }

                if (teacherCoursesDLM.isEmpty()) {
                    error.setText("Teacher/Assistant not found.");
                    error.setBounds(0, 0, 690, 500);
                    error.setHorizontalAlignment(SwingConstants.CENTER);
                    error.setVerticalAlignment(SwingConstants.CENTER);
                    content.add(error);
                    content.revalidate();
                    repaint();
                    setVisible(true);
                    return;
                } else {
                    // show selectable list of courses
                    teacherCourses.setModel(teacherCoursesDLM);
                    teacherCoursesScroll.setViewportView(teacherCourses);
                    teacherCourses.setLayoutOrientation(JList.VERTICAL);
                    teacherCoursesScroll.setBounds(0, 0, 690 / 2, 630);
                    content.add(teacherCoursesScroll);
                }

                if (t != null) {
                    if (Catalog.getInstance().getVisitor().getExamScores().get(t) != null)
                        toValidateDLM.addAll(Catalog.getInstance().getVisitor().getExamScores().get(t));
                    toValidate.setModel(toValidateDLM);
                    toValidateScroll.setViewportView(toValidate);
                    toValidate.setLayoutOrientation(JList.VERTICAL);
                    toValidateScroll.setBounds(690/2, 0, 690 / 2, 500);
                    content.add(toValidateScroll);
                }
                else {
                    if (Catalog.getInstance().getVisitor().getExamScores().get(ass) != null)
                        toValidateDLM.addAll(Catalog.getInstance().getVisitor().getExamScores().get(ass));
                    toValidate.setModel(toValidateDLM);
                    toValidateScroll.setViewportView(toValidate);
                    toValidate.setLayoutOrientation(JList.VERTICAL);
                    toValidateScroll.setBounds(690/2, 0, 690 / 2, 500);
                    content.add(toValidateScroll);
                }

                content.add(validateGrades);

                content.revalidate();
                repaint();
                setVisible(true);
            }
            else if (e.getSource().equals(parentButton)) {
                content.removeAll();

                Parent p = null;

                for (Observer o : Catalog.getInstance().getObservers())
                    if (((Parent) o).toString().equals(name.getText().strip()))
                        p = (Parent) o;

                if (p == null) {
                    error.setText("Parent not found.");
                    error.setBounds(0, 0, 690, 500);
                    error.setHorizontalAlignment(SwingConstants.CENTER);
                    error.setVerticalAlignment(SwingConstants.CENTER);
                    content.add(error);
                }
                else {
                    notificationsDLM.addAll(p.getNotifications());
                    notifications.setModel(notificationsDLM);
                    notificationsScroll.setViewportView(notifications);
                    notifications.setLayoutOrientation(JList.VERTICAL);
                    notificationsScroll.setBounds(0, 0, 690, 630);
                    content.add(notificationsScroll);
                }

                content.revalidate();
                repaint();
                setVisible(true);
            }
            else if (e.getSource().equals(validateGrades)) {
                Teacher t = null;
                Assistant ass = null;
                // find teacher
                for (Course c : Catalog.getInstance().getCourses()) {
                    if (c.getTeacher().toString().equals(name.getText().strip())) {
                        t = c.getTeacher();
                        continue;
                    }

                    for (Assistant a : c.getAssistants())
                        if (a.toString().equals(name.getText().strip())) {
                            ass = a;
                            break;
                        }
                }

                if (t != null) {
                    t.accept(Catalog.getInstance().getVisitor());
                    toValidateDLM.removeAllElements();
                    toValidate.removeAll();
                }
                else if (ass != null) {
                    ass.accept(Catalog.getInstance().getVisitor());
                    toValidateDLM.removeAllElements();
                    toValidate.removeAll();
                }
            }
        }
    }

    public void valueChanged(ListSelectionEvent e) {
        if (courses.isSelectionEmpty())
            return;

        String assistantName = "Not defined";

        Student sCast;
        for (Group<Student> g : courses.getSelectedValue().getGroups().values())
            for (Object s : g) {
                sCast = (Student) s;
                if (s.toString().strip().equals(name.getText().strip())) {
                    assistantName = g.getAssistant().toString();
                    break;
                }
            }

        teacherName.setText("Teacher: " + courses.getSelectedValue().getTeacher().toString() + " ||| Assistant: " + assistantName);

        studentGrades.setText("Partial grade: not graded ||| Exam grade: not graded");
        for (Grade g : courses.getSelectedValue().getGrades())
            if (g.getStudent().toString().strip().equals(name.getText().strip())) {
                if (g.getPartialScore() != null && g.getExamScore() != null)
                    studentGrades.setText("Partial grade: " + g.getPartialScore() + " ||| Exam grade: " + g.getExamScore());
                else if (g.getPartialScore() != null && g.getExamScore() == null)
                    studentGrades.setText("Partial grade: " + g.getPartialScore() + " ||| Exam grade: not graded");
                else if (g.getPartialScore() == null && g.getExamScore() != null)
                    studentGrades.setText("Partial grade: not graded" + " ||| Exam grade: " + g.getExamScore());
                break;
            }

        assistantListDLM.removeAllElements();
        assistantList.removeAll();

        assistantListDLM.addAll(courses.getSelectedValue().getAssistants());
        assistantList.setModel(assistantListDLM);
        assistantListScroll.setBounds(35, 175, 690 / 2 - 70, 200);
        assistantListScroll.setViewportView(assistantList);

        content.add(courseInfo);
        content.revalidate();
        repaint();
        setVisible(true);
    }
}
