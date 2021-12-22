/*
Assignment 3
Lucas Sarweh
ID: 110042658
COMP-2120
Due: Wed Dec 08 2021
*/

/**
 * Demo class for CourseGrades
 */
public class CourseGradesDemo {
    public static void main(String[] args){
        // Create a CourseGrades
        CourseGrades gradesList = new CourseGrades();
        // Create the lab
        GradedActivity lab = new GradedActivity();
        lab.setScore(85.0);
        // Create the pass/fail exam
        PassFailExam passfail = new PassFailExam(20, 3, 70.0);
        // Create the essay
        GradedActivity essay = new GradedActivity();
        essay.setScore(80.0);
        // Create Final
        FinalExam fExam = new FinalExam(50, 10);
        // Set all the scores to the list
        gradesList.setLab(lab);
        gradesList.setPassFailExam(passfail);
        gradesList.setEssay(essay);
        gradesList.setFinalExam(fExam);
        // Print out the list
        System.out.println(gradesList);
    }
}
