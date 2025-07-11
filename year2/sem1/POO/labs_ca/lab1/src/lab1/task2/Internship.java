package lab1.task2;
import java.util.Random;

public class Internship {
    String name;
    String minGrade;
    Student[] students;

    Student chooseCandidateRandomly() {
        Random random = new Random();
        return students[random.nextInt(students.length)];
    }

    void chooseCandidateForInterview() {
        for (int i = 0; i < students.length; i++) {
            if (students[i].grade >= Double.parseDouble(minGrade))
                System.out.println("Candidate " + students[i].name + " got a phone interview at " + name);
        }
    }
}
