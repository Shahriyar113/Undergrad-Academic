package Local_Search;

import java.util.ArrayList;
import java.util.List;

public class Course implements Comparable<Course>  {

    private int course_id;
    private List<Integer> enrolled_student_list ; //list of students who enrolled this course
    int total_student_enrolled ; //total num of students who enrolled this course
    private String heuristic_name ;

    private int day_no ; //"day no" corresponds the color of a node
                        //"day no" is the time slot for the exam of this "course"
    private int degree;
    private int saturation_degree;

    public Course(int course_id,int total_student_enrolled)
    {
        this.course_id = course_id;
        enrolled_student_list = new ArrayList<>();
        this.total_student_enrolled = total_student_enrolled;
        day_no = 0;
        degree = 0;
    }


    public Course(int course_id,List<Integer> enrolled_student_list,int total_student_enrolled,String heuristic_name)
    {
        this.course_id = course_id;
        this.enrolled_student_list = enrolled_student_list;
        this.total_student_enrolled = total_student_enrolled;
        day_no = 0;
        degree = 0;
        this.heuristic_name = heuristic_name;
    }

    public Course(int course_id,List<Integer> enrolled_student_list,int total_student_enrolled,int degree,int day_no,String heuristic_name)
    {
        this.course_id = course_id;
        this.enrolled_student_list = enrolled_student_list;
        this.total_student_enrolled = total_student_enrolled;
        this.day_no = day_no;
        this.degree = degree;
        this.heuristic_name = heuristic_name;
    }


    public void add_student(int student_id)
    {
        enrolled_student_list.add(student_id);
    }

    public int getCourse_id() {
        return course_id;
    }

    public List<Integer> getEnrolled_student_list() {
        return enrolled_student_list;
    }

    public int getTotal_student_enrolled()
    {
        return total_student_enrolled;
    }

    public Course get_Reference()
    {
        return this;
    }

    //coloring the node(or course)
    public void setDay_no(int day_no)
    {
        this.day_no = day_no;
    }

    public int getDay_no()
    {
        return day_no;
    }

    public void setDegree(int degree) {
        this.degree = degree;
    }

    public int getDegree()
    {
        return degree;
    }

    public void setHeuristic_name(String heuristic_name) {
        this.heuristic_name = heuristic_name;
    }

    public String getHeuristic_name() {
        return heuristic_name;
    }

    public void setSaturation_degree(int saturation_degree) {
        this.saturation_degree = saturation_degree;
    }

    public int getSaturation_degree() {
        return saturation_degree;
    }


    @Override
    //ascending order sorting
    public int compareTo(Course course) {

        if(heuristic_name.equalsIgnoreCase("LDH")) //for Largest Degree Heuristic
        {
            if(this.getDegree() < course.getDegree())
                return 1;
            else
                return -1;
        }

        else if(heuristic_name.equalsIgnoreCase("LEH")) // //for Largest Enrollment Heuristic
        {
            if(this.getTotal_student_enrolled() < course.getTotal_student_enrolled())
                return 1;
            else
                return -1;
        }

        else if(heuristic_name.equalsIgnoreCase("SDH")) // //for Largest Enrollment Heuristic
        {
            if(this.getSaturation_degree() < course.getSaturation_degree())
                return 1;
            else if(this.getSaturation_degree() == course.getSaturation_degree())
            {
                if (this.getDegree() < course.getDegree())
                    return 1;
                else
                    return -1;
            }
            else
                return -1;


        }

        return 0;

    }




}
