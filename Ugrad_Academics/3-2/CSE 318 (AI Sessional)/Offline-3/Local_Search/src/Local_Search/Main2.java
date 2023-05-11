package Local_Search;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main2 {

    public static void main(String[] args) {

        String[] Constructive_heuristics = {"LDH","SDH","LEH","ROH"};
        String[] datasheets = {"car-f-92","car-s-91","kfu-s-93","tre-s-92","yor-f-83"};

        //Exponential penalty
        for(int i=0 ;i<Constructive_heuristics.length ; i++)
        {
            System.out.println(Constructive_heuristics[i]+" + "+"Exponetial_penalty");
            System.out.println("-------------------------------------------------");
            System.out.println();

            for(int j=0;j<datasheets.length;j++)
            {
                String datasheet_name = datasheets[j];

                System.out.println(datasheet_name);
                System.out.println("--------------");
                String course_file_path = "Input_Datasheets/"+datasheet_name+"/"+datasheet_name+".crs";
                String student_file_path = "Input_Datasheets/"+datasheet_name+"/"+datasheet_name+".stu";

                List<Student> studentList = new ArrayList<>();
                List<Course> courseList = new ArrayList<>();

                //this ensures that the list will start indexing form 1;
                studentList.add(null);
                courseList.add(null);


                try {

                    //taking input from course_file

                    File course_file = new File(course_file_path);
                    Scanner course_file_input = new Scanner(course_file);

                    String line = "";
                    while (course_file_input.hasNextLine())
                    {
                        line = course_file_input.nextLine();
                        String[] strings = line.split(" ");
                        int course_id = Integer.parseInt(strings[0]);
                        int total_student_enrolled = Integer.parseInt(strings[1]);
                        courseList.add(new Course(course_id,total_student_enrolled));
                    }


                    //taking input from student_file

                    File student_file = new File(student_file_path);
                    Scanner student_file_input = new Scanner(student_file);


                    line = "";
                    int student_id_count = 1;

                    while (student_file_input.hasNextLine())
                    {
                        line = student_file_input.nextLine();
                        String[] strings = line.split(" ");
                        Student student = new Student(student_id_count);

                        for (String string : strings)
                        {
                            int course_id = Integer.parseInt(string);
                            courseList.get(course_id).add_student(student.getStudent_id());
                            student.add_course(course_id);

                        }
                        studentList.add(student);

                        student_id_count++;

                    }

                    //input process ends



                    LSP lsp =new LSP(courseList,studentList,Constructive_heuristics[i],"EP");

                    lsp.Solve_with_Constructive_heuristic();

                    System.out.println("Total Time slots : "+lsp.get_Total_days());
                    System.out.println("Average Penalty: "+lsp.get_Average_Penalty());


                    lsp.Apply_Kempe_Chain_Heuristic();

                    System.out.println("Average Penalty after Kempe Chain: "+lsp.get_Average_Penalty());


                    lsp.Apply_Pairswap_Heuristic();
                    System.out.println("Average Penalty after Pairswap: "+lsp.get_Average_Penalty());



                    System.out.println();
                    System.out.println();




                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }

            }


        }



        //Linear Penalty
        System.out.println("LDH"+" + "+"Linear_penalty");
        System.out.println("-------------------------------------------------");
        System.out.println();


        for(int j=0;j<datasheets.length;j++)
        {
            String datasheet_name = datasheets[j];

            System.out.println(datasheet_name);
            System.out.println("--------------");
            String course_file_path = "Input_Datasheets/"+datasheet_name+"/"+datasheet_name+".crs";
            String student_file_path = "Input_Datasheets/"+datasheet_name+"/"+datasheet_name+".stu";

            List<Student> studentList = new ArrayList<>();
            List<Course> courseList = new ArrayList<>();

            //this ensures that the list will start indexing form 1;
            studentList.add(null);
            courseList.add(null);


            try {

                //taking input from course_file

                File course_file = new File(course_file_path);
                Scanner course_file_input = new Scanner(course_file);

                String line = "";
                while (course_file_input.hasNextLine())
                {
                    line = course_file_input.nextLine();
                    String[] strings = line.split(" ");
                    int course_id = Integer.parseInt(strings[0]);
                    int total_student_enrolled = Integer.parseInt(strings[1]);
                    courseList.add(new Course(course_id,total_student_enrolled));
                }


                //taking input from student_file

                File student_file = new File(student_file_path);
                Scanner student_file_input = new Scanner(student_file);


                line = "";
                int student_id_count = 1;

                while (student_file_input.hasNextLine())
                {
                    line = student_file_input.nextLine();
                    String[] strings = line.split(" ");
                    Student student = new Student(student_id_count);

                    for (String string : strings)
                    {
                        int course_id = Integer.parseInt(string);
                        courseList.get(course_id).add_student(student.getStudent_id());
                        student.add_course(course_id);

                    }
                    studentList.add(student);

                    student_id_count++;

                }

                //input process ends



                LSP lsp =new LSP(courseList,studentList,"LDH","LP");

                lsp.Solve_with_Constructive_heuristic();

                System.out.println("Total Time slots : "+lsp.get_Total_days());
                System.out.println("Average Penalty: "+lsp.get_Average_Penalty());


                lsp.Apply_Kempe_Chain_Heuristic();

                System.out.println("Average Penalty after Kempe Chain: "+lsp.get_Average_Penalty());


                lsp.Apply_Pairswap_Heuristic();
                System.out.println("Average Penalty after Pairswap: "+lsp.get_Average_Penalty());


                System.out.println();
                System.out.println();




            }
            catch (Exception e)
            {
                e.printStackTrace();
            }

        }




    }
}
