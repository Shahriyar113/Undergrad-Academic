package Local_Search;

//LSP means "Local Search Problem"

import java.awt.event.MouseAdapter;
import java.util.*;

public class LSP {
    List<Course> courseList;
    List<Student> studentList;
    String heuristic_name;//LDH,SDH,LEH,ROH
    String Penalty_type;// LP or EP

    //this is the adjacency matrix of the graph of "graph coloring problem"
    //where every node denotes a "course"
    //and an edge between two nodes(or courses) represents the conflict between those two courses
    // conflict means "A student enrolled those two courses"

    int[][] adjacency_matrix;

    public LSP(List<Course> courses,List<Student> students,String heuristic_name,String penalty_type)
    {
        this.courseList = new ArrayList<>();
        this.studentList = new ArrayList<>();
        this.heuristic_name = heuristic_name;
        this.Penalty_type = penalty_type;

        //copying the course list and student list

        for(Course course : courses)
        {
            if(course == null)
                this.courseList.add(null); //start indexing from 1
            else
                this.courseList.add(new Course(course.getCourse_id(),course.getEnrolled_student_list(),
                    course.getTotal_student_enrolled(),heuristic_name));
        }

        for(Student student : students )
        {
            if(student==null)
                this.studentList.add(null); //start indexing from 1
            else
                this.studentList.add(new Student(student.getStudent_id(),student.getEnrolled_coursed_list()));
        }

        //copy end



        //start addressing from 1
        adjacency_matrix = new int[this.courseList.size()][this.studentList.size()];

        //Build_the_graph_2();
       Build_the_graph();
    }


    public void Solve_with_Constructive_heuristic()
    {
        //Largest_Degree_Heuristic
        if(heuristic_name.equalsIgnoreCase("LDH"))
        {
            Apply_Largest_Degree_Heuristic();
        }
        //Saturation_Degree_Heuristic
        else if(heuristic_name.equalsIgnoreCase("SDH"))
        {
            Apply_Saturation_Degree_Heuristic();
        }
        //Largest_Enrollment_Heuristic
        else if(heuristic_name.equalsIgnoreCase("LEH"))
        {
            Apply_Largest_Enrollment_Heuristic();
        }
        else if(heuristic_name.equalsIgnoreCase("ROH"))
        {
            Apply_Random_Ordering_Heuristic();
        }



    }

    public List<Student> get_A_copy_of_Student_list()
    {
        List<Student> studentList = new ArrayList<>();
        for(Student student : this.studentList )
        {
            if(student==null)
                studentList.add(null); //start indexing from 1
            else
                studentList.add(new Student(student.getStudent_id(),student.getEnrolled_coursed_list()));
        }
        return studentList;
    }

    public List<Course> get_A_copy_of_Course_list()
    {
        List<Course> courseList = new ArrayList<>();
        for(Course course : this.courseList)
        {
            if(course == null)
                courseList.add(null); //start indexing from 1
            else
                courseList.add(new Course(course.getCourse_id(),course.getEnrolled_student_list(),
                        course.getTotal_student_enrolled(),course.getHeuristic_name()));
        }
        return courseList;
    }

    public List<Course> get_A_copy_of_Course_list_2()
    {
        List<Course> courseList = new ArrayList<>();
        for(Course course : this.courseList)
        {
            if(course == null)
                courseList.add(null); //start indexing from 1
            else
                courseList.add(new Course(course.getCourse_id(),course.getEnrolled_student_list(),
                        course.getTotal_student_enrolled(),course.getDegree(),course.getDay_no(),
                        course.getHeuristic_name()));
        }
        return courseList;
    }

    boolean is_conflicting(Course course1,Course course2)
    {
        for(int i=0;i<course1.getEnrolled_student_list().size();i++)
        {
            for (int j=0;j<course2.getEnrolled_student_list().size();j++)
            {
                if((int)course1.getEnrolled_student_list().get(i) == (int)course2.getEnrolled_student_list().get(j))
                {
                    //System.out.println("Here");
                    return true;
                }
            }
        }


        return false;
    }

    //populating the adjacency matrix (i.e. creating the edges between nodes)
    public void Build_the_graph()
    {
        for(int i=1;i<courseList.size();i++)
        {
            for (int j=1;j<courseList.size();j++ )
            {
                if(i!=j)
                {
                    if(is_conflicting(courseList.get(i),courseList.get(j)))
                    {
                        adjacency_matrix[i][j] = 1;
                    }
                }

            }
        }
    }

    public void Build_the_graph_2()
    {
        for (Student student : studentList)
        {
            if(student != null) //remeber that the 1st student in the list is "null" for starting indexing from 1
            {
                for (int i=0;i<student.getEnrolled_coursed_list().size()-1;i++)
                {
                    for (int j=i+1;j<student.getEnrolled_coursed_list().size();j++)
                    {
                        adjacency_matrix[student.getEnrolled_coursed_list().
                                get(i)][student.getEnrolled_coursed_list().get(j)] = 1;

                        adjacency_matrix[student.getEnrolled_coursed_list().
                                get(j)][student.getEnrolled_coursed_list().get(i)] = 1;
                    }
                }
            }

        }
    }



    //counting degree of a node
    int Calculate_degree(int node)
    {
        int degree_count = 0;
        for(int i=1;i<courseList.size();i++)
        {
            if(adjacency_matrix[node][i] == 1)
            {
                degree_count++;
            }
        }
        return degree_count;
    }

    void Calculate_All_node_degree()
    {
        int degree_count=0;
        for(int i=1;i<courseList.size();i++)
        {
           for (int j=1;j<courseList.size();j++)
           {
               if(adjacency_matrix[i][j] == 1)
               {
                   degree_count++;
               }
           }

           courseList.get(i).setDegree(degree_count);
           degree_count = 0;
        }
    }

    void Update_saturation_degree_of_neighbours(int node)
    {
        for(int i=1;i<courseList.size();i++)
        {
            if(adjacency_matrix[node][i] == 1)
            {
                courseList.get(i).setSaturation_degree(courseList.get(i).getSaturation_degree() + 1);
            }
        }
    }

    public void print_All_course_info()
    {
        for(Course course:courseList)
        {
            if(course == null)
                continue;
            System.out.println(course.getCourse_id()+": "+course.getEnrolled_student_list());
        }
    }

    public void print_All_student_info()
    {
        for(Student student:studentList)
        {
            if(student == null)
                continue;
            System.out.println(student.getStudent_id()+": "+student.getEnrolled_coursed_list());
        }
    }

    void print_Adjacency_Matrix()
    {
        for(int i=1;i<courseList.size();i++)
        {
            for(int j=1;j<courseList.size();j++)
            {
                System.out.print(adjacency_matrix[i][j]+" ");
            }
            System.out.println();
        }
    }

    //this method will return a list of colors of the neighbours of "node"
    public List<Integer> get_Neighbour_Colors(int node)
    {
       List<Integer> Neighbour_colors = new ArrayList<>();

        for(int i=1;i<courseList.size();i++)
        {
            if(adjacency_matrix[node][i] == 1)
            {
                //"i" is a neighbour of "node"
                if(courseList.get(i).getDay_no() != 0)
                    Neighbour_colors.add(courseList.get(i).getDay_no());
            }
        }

        return Neighbour_colors;


    }



    //Applying Constructive Heuristic

    //coloring the nodes (or scheduling the exam)
    public void Apply_Largest_Degree_Heuristic()
    {
        //Calculating the degree of all nodes
        Calculate_All_node_degree();

        //creating an Priority list for courses
        PriorityQueue<Course> course_priority_queue = new PriorityQueue<>();
        for(Course course : this.courseList)
        {
            if(course == null)
                continue;
            course_priority_queue.add(course);
        }

        //coloring the nodes(scheduling the exams)
        for(int i=1;i<courseList.size();i++)
        {
            //picking a node with largest_degree
            Course course = course_priority_queue.poll();
            Integer day_no_count = 1;

            List<Integer> Neighbour_Colors = get_Neighbour_Colors(course.getCourse_id());

            if(Neighbour_Colors.isEmpty()) //if all the neighbour nodes are uncolored
            {
                courseList.get(course.getCourse_id()).setDay_no(1); //giving those nodes "day 1" color
            }
            else
            {
               while(true)
               {
                   //finding the appropriate time slot for that exam
                  if(!Neighbour_Colors.contains(day_no_count))
                  {
                      courseList.get(course.getCourse_id()).setDay_no(day_no_count);
                      break;
                  }
                  day_no_count++;
               }
            }
        }

    }


    public void Apply_Largest_Enrollment_Heuristic()
    {

        //creating an Priority list for courses
        PriorityQueue<Course> course_priority_queue = new PriorityQueue<>();
        for(Course course : this.courseList)
        {
            if(course == null)
                continue;
            course_priority_queue.add(course);
        }

        //coloring the nodes(scheduling the exams)
        for(int i=1;i<courseList.size();i++)
        {
            //picking a node with largest_Enrollment
            Course course = course_priority_queue.poll();
            Integer day_no_count = 1;

            List<Integer> Neighbour_Colors = get_Neighbour_Colors(course.getCourse_id());

            if(Neighbour_Colors.isEmpty()) //if all the neighbour nodes are uncolored
            {
                courseList.get(course.getCourse_id()).setDay_no(1); //giving those nodes "day 1" color
            }
            else
            {
                while(true)
                {
                    //finding the appropriate time slot for that exam
                    if(!Neighbour_Colors.contains(day_no_count))
                    {
                        courseList.get(course.getCourse_id()).setDay_no(day_no_count);
                        break;
                    }
                    day_no_count++;
                }
            }
        }

    }



    public void Apply_Saturation_Degree_Heuristic()
    {
        //Calculating the degree of all nodes
        Calculate_All_node_degree();

        //creating an Priority list for courses
        PriorityQueue<Course> course_priority_queue = new PriorityQueue<>();
        for(Course course : this.courseList)
        {
            if(course == null)
                continue;
            course_priority_queue.add(course);
        }

        //coloring the nodes(scheduling the exams)
        for(int i=1;i<courseList.size();i++)
        {
            //Updating the saturation degree of neighbours of selected node
            Update_saturation_degree_of_neighbours(course_priority_queue.peek().getCourse_id());

            //picking a node with largest_Saturation_degree

            Course course = course_priority_queue.poll();
            Integer day_no_count = 1;

            List<Integer> Neighbour_Colors = get_Neighbour_Colors(course.getCourse_id());

            if(Neighbour_Colors.isEmpty()) //if all the neighbour nodes are uncolored
            {
                courseList.get(course.getCourse_id()).setDay_no(1); //giving those nodes "day 1" color
            }
            else
            {
                while(true)
                {
                    //finding the appropriate time slot for that exam
                    if(!Neighbour_Colors.contains(day_no_count))
                    {
                        courseList.get(course.getCourse_id()).setDay_no(day_no_count);
                        break;
                    }
                    day_no_count++;
                }
            }


        }

    }



    public void Apply_Random_Ordering_Heuristic()
    {
        List<Course> new_Course_list = get_A_copy_of_Course_list();
        Random random = new Random(3);

        new_Course_list.remove(0);//as the 1st course of the list is "null"

        //coloring the nodes(scheduling the exams)

        while (!new_Course_list.isEmpty())
        {
            //picking a node randomly
            int Random_value = random.nextInt(new_Course_list.size());

            Course course = new_Course_list.get(Random_value);
            new_Course_list.remove(course);


            Integer day_no_count = 1;

            List<Integer> Neighbour_Colors = get_Neighbour_Colors(course.getCourse_id());

            if(Neighbour_Colors.isEmpty()) //if all the neighbour nodes are uncolored
            {
                courseList.get(course.getCourse_id()).setDay_no(1); //giving those nodes "day 1" color
            }
            else
            {
                while(true)
                {
                    //finding the appropriate time slot for that exam
                    if(!Neighbour_Colors.contains(day_no_count))
                    {
                        courseList.get(course.getCourse_id()).setDay_no(day_no_count);
                        break;
                    }
                    day_no_count++;
                }
            }


        }

    }


    //Apply Perturbative heuristic

    //will return a list of all pairs of vertices which are directly connected
    public List<Node_Pair> get_All_connected_pairs()
    {
        List<Node_Pair> node_pairs = new ArrayList<>();

        for(int i=1;i<courseList.size();i++)
        {
            for (int j=1;j<courseList.size();j++)
            {
               if(adjacency_matrix[i][j] == 1)
               {
                   node_pairs.add(new Node_Pair(i,j));
               }
            }
        }

        return node_pairs;
    }

    //here the course list is the list after kempe chain swapping
    public boolean is_hard_constraint_violated_after_applying_Kempe_chain(List<Course> courseList,List<Integer> kempe_chain_list)
    {
        for (Integer node : kempe_chain_list)
        {
            for(int i=1;i<courseList.size();i++)
            {
                if(adjacency_matrix[node][i] == 1 &&
                        courseList.get(node).getDay_no() == courseList.get(i).getDay_no())
                {
                    return true;
                }
            }
        }
        return false;

    }


    //"Node" means course_id
    //color means "day_no"(i.e timeslot)
    public void Apply_Kempe_Chain_Heuristic()
    {
        List<Node_Pair> node_pairs = get_All_connected_pairs();


        Random random = new Random(3);



        for (int k=0;k<1000;k++)
        {
            //Randomly select a node pair
            List<Course> copy_course_list = get_A_copy_of_Course_list_2();

            Node_Pair node_pair = node_pairs.get(random.nextInt(node_pairs.size()));
            int node1 = node_pair.getNode1();
            int node2 = node_pair.getNode2();
            int color1 = copy_course_list.get(node1).getDay_no();
            int color2 = copy_course_list.get(node2).getDay_no();

            //creating kempe chain

            Queue<Integer> queue = new LinkedList<>();
            List<Integer> kempe_chain_list = new ArrayList<>();

            queue.add(node1);
            kempe_chain_list.add(node1);


            while (!queue.isEmpty())
            {
                int removed_node = queue.remove();
                int removed_node_color = copy_course_list.get(removed_node).getDay_no();

                if(removed_node_color == color1)
                {
                    for(int i=1;i<copy_course_list.size();i++)
                    {
                        if(adjacency_matrix[removed_node][i] == 1 &&
                                copy_course_list.get(i).getDay_no() == color2 &&
                                !kempe_chain_list.contains(i) )
                        {

                            queue.add(i);
                            kempe_chain_list.add(i);

                        }
                    }
                }

                else
                {
                    for(int i=1;i<copy_course_list.size();i++)
                    {
                        if(adjacency_matrix[removed_node][i] == 1 &&
                                copy_course_list.get(i).getDay_no() == color1 &&
                                !kempe_chain_list.contains(i) )
                        {

                            queue.add(i);
                            kempe_chain_list.add(i);

                        }
                    }
                }



            }

            //node means "course id"
            //swaping the colors in the kempe chain

            for(Integer node: kempe_chain_list)
            {
                if(copy_course_list.get(node).getDay_no() == color1)
                    copy_course_list.get(node).setDay_no(color2);
                else
                    copy_course_list.get(node).setDay_no(color1);

            }


            //checking constraints after swapping


            List<Course> Curr_course_list = this.courseList;
            List<Course> Modified_course_list = copy_course_list;


            if(!is_hard_constraint_violated_after_applying_Kempe_chain(Modified_course_list,
                    kempe_chain_list))
            {
                double Curr_average_penalty = get_Average_Penalty();

                this.courseList = Modified_course_list;
                double Updated_average_penalty = get_Average_Penalty();

                if(Updated_average_penalty < Curr_average_penalty)
                {
                    this.courseList = Modified_course_list;
                }
                else
                {
                    this.courseList = Curr_course_list;
                }


            }
        }


    }



    //here the course list is the list after kempe chain swapping
    public boolean is_hard_constraint_violated_after_applying_pairswap(List<Course> courseList,int node1,int node2)
    {
        for(int i=1;i<courseList.size();i++)
        {
            if(adjacency_matrix[node1][i] == 1 &&
                    courseList.get(node1).getDay_no() == courseList.get(i).getDay_no())
            {
                return true;
            }
        }

        for(int i=1;i<courseList.size();i++)
        {
            if(adjacency_matrix[node2][i] == 1 &&
                    courseList.get(node2).getDay_no() == courseList.get(i).getDay_no())
            {
                return true;
            }
        }


        return false;

    }







    public void Apply_Pairswap_Heuristic()
    {
        Random random = new Random();
        List<Node_Pair> node_pairs = get_All_connected_pairs();

        for (int k=0;k<1000;k++)
        {
            List<Course> copy_course_list = get_A_copy_of_Course_list_2();

            Node_Pair random_node_pair = node_pairs.get(random.nextInt(node_pairs.size()));
            int node1 = random_node_pair.getNode1();
            int node2 = random_node_pair.getNode2();

            int color1 = copy_course_list.get(node1).getDay_no();
            int color2 = copy_course_list.get(node2).getDay_no();


            //swaping those 2 nodes colors
            copy_course_list.get(node1).setDay_no(color2);
            copy_course_list.get(node2).setDay_no(color1);

            //checking constraints after swapping
            List<Course> Curr_course_list = this.courseList;
            List<Course> Modified_course_list = copy_course_list;

            if(!is_hard_constraint_violated_after_applying_pairswap(Modified_course_list,node1,node2))
            {
                double Curr_average_penalty = get_Average_Penalty();

                this.courseList = Modified_course_list;
                double Updated_average_penalty = get_Average_Penalty();

                if(Updated_average_penalty < Curr_average_penalty)
                {
                    this.courseList = Modified_course_list;
                }

                else
                {
                    this.courseList = Curr_course_list;
                }

            }



        }





    }





    public double get_Exponential_penalty(int day_gap)
    {
        if(day_gap <= 5)
        {
            return Math.pow(2,(5-day_gap));
        }
        else
            return 0.0;
    }

    public double get_linear_penalty(int day_gap)
    {
        if(day_gap <= 5)
        {
            return (2*(5-day_gap));
        }
        else
            return 0.0;
    }

    public double get_Penalty(int day_gap)
    {
        if(Penalty_type.equalsIgnoreCase("EP"))
        {
            return get_Exponential_penalty(day_gap);
        }
        else if(Penalty_type.equalsIgnoreCase("LP"))
        {
            return get_linear_penalty(day_gap);
        }
        else
            return -1.0;
    }



    public double get_Average_Penalty()
    {

        double sum_of_penalties = 0.0;
        int total_students = studentList.size() - 1; //as the 1st element of "studentList" is "null"

        for(int i=1;i<studentList.size();i++)
        {
            //int total_day_gap_of_this_student = 0;
            List<Integer> timeslots = new ArrayList<>();
            //finding the timeslots of the exams of courses which student id = "i" has enrolled
            List<Integer> Enrolled_courses = studentList.get(i).getEnrolled_coursed_list();

            for(int j=0;j<Enrolled_courses.size();j++)
            {
                timeslots.add(courseList.get(Enrolled_courses.get(j)).getDay_no());
            }

            Collections.sort(timeslots);

            for(int j=0;j<timeslots.size()-1;j++ )
            {
                //"day_gap" is the day gap between two successive_exam
                int day_gap = timeslots.get(j+1)-timeslots.get(j);
                //total_day_gap_of_this_student =total_day_gap_of_this_student + day_gap;
                sum_of_penalties = sum_of_penalties + get_Penalty(day_gap);

            }

            //System.out.println(studentList.get(i).getStudent_id()+": "+Enrolled_courses);

            //System.out.println(studentList.get(i).getStudent_id()+": "+timeslots);
            //System.out.println(sum_of_penalties);


        }

        return sum_of_penalties/total_students;
    }



    public int get_Total_days()
    {
        int max = Integer.MIN_VALUE;

        for(int i=1;i<courseList.size();i++)
        {
            if(courseList.get(i).getDay_no() > max)
            {
                max = courseList.get(i).getDay_no();
            }
        }
        return max;
    }










}
