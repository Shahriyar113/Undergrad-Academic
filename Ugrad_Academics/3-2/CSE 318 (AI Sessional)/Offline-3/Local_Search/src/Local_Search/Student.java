package Local_Search;

import java.util.ArrayList;
import java.util.List;

public class Student {
    private int student_id;
    private List<Integer> enrolled_coursed_list;
    private int penalty; //penalty for the scheduled exam gap for that student
    private int total_course_enrolled;

    public Student (int student_id)
    {
        this.student_id = student_id;
        enrolled_coursed_list = new ArrayList<>();
        penalty = 0;
        total_course_enrolled = 0;
    }

    public Student(int student_id, List<Integer> enrolled_coursed_list) {
        this.student_id = student_id;
        this.enrolled_coursed_list = enrolled_coursed_list;
        penalty = 0;
    }

    public void add_course(int course_id)
    {
        enrolled_coursed_list.add(course_id);
    }

    public int getStudent_id() {
        return student_id;
    }

    public void setStudent_id(int student_id) {
        this.student_id = student_id;
    }

    public List<Integer> getEnrolled_coursed_list() {
        return enrolled_coursed_list;
    }

    public void setEnrolled_coursed_list(List<Integer> enrolled_coursed_list) {
        this.enrolled_coursed_list = enrolled_coursed_list;
    }

    public int getPenalty() {
        return penalty;
    }

    public void setPenalty(int penalty) {
        this.penalty = penalty;
    }

    public int getTotal_course_enrolled() {
       return enrolled_coursed_list.size();
    }

    public Student get_Reference()
    {
        return this;
    }
}
