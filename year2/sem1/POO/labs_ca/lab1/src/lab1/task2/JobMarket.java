package lab1.task2;

public class JobMarket {
    public static void main(String[] args) {
        Student[] students = new Student[4];
        for(int i = 0; i < students.length; i++)
            students[i] = new Student();

        students[0].name = "Gigel";
        students[1].name = "Dorel";
        students[2].name = "Marcel";
        students[3].name = "Ionel";
        students[0].grade = 5;
        students[1].grade = 10;
        students[2].grade = 4.99;
        students[3].grade = 1;

        Internship google = new Internship();
        google.students = students;
        google.minGrade = "9";
        google.name = "Google";
        google.chooseCandidateForInterview();

        Internship facebook = new Internship();
        facebook.students = students;
        facebook.minGrade = "7";
        facebook.name = "Facebook";
        facebook.chooseCandidateForInterview();

        Internship amazon = new Internship();
        amazon.students = students;
        amazon.minGrade = "5";
        amazon.name = "Amazon";
        amazon.chooseCandidateForInterview();

        Internship microsoft = new Internship();
        microsoft.students = students;
        microsoft.minGrade = "2";
        microsoft.name = "Microsoft";
        microsoft.chooseCandidateForInterview();

        Student task3_1 = new Student();
        task3_1.name = "lol";
        task3_1.grade = 6;
        Student task3_2 = new Student();
        task3_2.name = "lol";
        task3_2.grade = 6;
    }
}
