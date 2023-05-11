package CSP;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class CSP {

    private LinkedList<Variable> variables; //this is basically list of unassigned variables of root node
    private boolean is_All_Variable_Assigned;
    private Node Solved_Node;
    private long number_of_total_nodes;
    private long number_of_backtracks;

    long node_count = 0;
    long back_track_count = 0;



    public CSP()
    {
        variables = new LinkedList<Variable>();
        is_All_Variable_Assigned = false;
        Solved_Node = null;

        number_of_backtracks =0;
        number_of_total_nodes =0;

        node_count = 0;
        back_track_count = 0;

    }

    public void add_variable(Variable variable)
    {
        variables.addLast(variable);
    }


    public LinkedList<Variable> getVariables() {
        return variables;
    }

    public void setVariables(LinkedList<Variable> variables) {
        this.variables = variables;
    }


    public static Variable get_Next_Unassigned_Variable(String heuristic_name, Node node)
    {
        Variable var = null;
        if(heuristic_name.equalsIgnoreCase("VAH1"))
        {
            node.Update_All_Variable_Domain();
            var = node.Select_A_Variable_By_VAH1();

        }
        else if(heuristic_name.equalsIgnoreCase("VAH2"))
        {

            node.Update_All_Variable_Degree();

            var = node.Select_A_Variable_By_VAH2();
        }

        else if(heuristic_name.equalsIgnoreCase("VAH3"))
        {
            node.Update_All_Variable_Domain();
            node.Update_All_Variable_Degree();

            var = node.Select_A_Variable_By_VAH3();
        }

        else if(heuristic_name.equalsIgnoreCase("VAH4"))
        {
            node.Update_All_Variable_Domain();
            node.Update_All_Variable_Degree();

            var = node.Select_A_Variable_By_VAH4();
        }

        else if(heuristic_name.equalsIgnoreCase("VAH5"))
        {
            var = node.Select_A_Variable_By_VAH5();
        }

        return var;


    }


    public boolean is_Consistent_for_FT(Node node)
    {
        node.Update_All_Variable_Domain();

        for(Variable variable:node.getVariables())
        {
            if(variable.get_domain_size() == 0)
            {
                return false;
            }
        }

        return true;

    }



    public boolean is_Consistent_for_BT(int[][] Latin_Square_Matrix, int N, Variable variable, int assigned_value)
    {

        int row_no = variable.getRow_no();
        int column_no = variable.getColumn_no();

        //traversing the variable row
        for(int i=1;i<=N;i++)
        {
            if(column_no != i && Latin_Square_Matrix[row_no][i] == assigned_value)
            {
                return false;
            }
        }

        //traversing the variable column
        for(int i=1;i<=N;i++)
        {
            if(row_no != i && Latin_Square_Matrix[i][column_no] == assigned_value)
            {
                return false;
            }
        }

        return true;



    }


    //for printing any Latin_Square_Matrix
    public void print_Latin_Square_Matrix(int[][] Latin_Square_Matrix,int N)
    {
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                System.out.print(Latin_Square_Matrix[i][j]+" ");
            }
            System.out.println();

        }
    }

    public void print_Solved_Latin_Square_Matrix()
    {
        int[][] solved_Latin_Square_matrix = Solved_Node.getLatin_Square_Matrix();
        int N = Solved_Node.getDimension();
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                System.out.print(solved_Latin_Square_matrix[i][j]+" ");
            }
            System.out.println();

        }
    }

    public Node getSolved_Node()
    {
        return Solved_Node;
    }

    public long getNumber_of_total_nodes()
    {
        return number_of_total_nodes;
    }

    public long getNumber_of_backtracks()
    {
        return number_of_backtracks;
    }


    public int[][] make_a_copy_of_Matrix(int[][] matrix,int N)
    {
        int[][] new_copy = new int[N+1][N+1];
        for(int i=1;i<N+1;i++)
        {
            for(int j=1;j<N+1;j++)
            {
                new_copy[i][j] = matrix[i][j];
            }

        }

        return new_copy;
    }

    //least constraining value
    public Variable Perform_Value_Ordering_heuristic_for_BT(int[][] Latin_Square_Matrix, int N, Variable variable)
    {
        //copying the matrix
        int[][] Copy_Martix = new int[N+1][N+1];

        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                Copy_Martix[i][j] = Latin_Square_Matrix[i][j];
            }

        }


        //all copy complete

        //My task to order values of "variable"

        List<Value_Contraint> value_contraints = new ArrayList<Value_Contraint>();

        int row_no = variable.getRow_no();
        int column_no = variable.getColumn_no();


        //ordering
        for(int value=1;value<=N;value++)
        {
            Copy_Martix[row_no][column_no] = value;

            int constraint_count = 1 ;

            for(int i=1;i<=N;i++)
            {
                if(Latin_Square_Matrix[row_no][i] == 0 && column_no != i)
                {
                    Variable new_var = new Variable(row_no,i,N);
                    new_var.update_domain(Copy_Martix,N);
                    constraint_count = constraint_count * new_var.get_domain_size();

                }

            }

            for(int i=1;i<=N;i++)
            {
                if(Latin_Square_Matrix[i][column_no] == 0 && row_no != i)
                {
                    Variable new_var = new Variable(i,column_no,N);
                    new_var.update_domain(Copy_Martix,N);
                    constraint_count = constraint_count * new_var.get_domain_size();
                }
            }

            value_contraints.add(new Value_Contraint(value,constraint_count));

        }

        Collections.sort(value_contraints);

        //Ordering the value of the variable;
        Variable temp_var = new Variable(row_no,column_no,N);
        temp_var.getDomain().clear();
        for(Value_Contraint value_contraint : value_contraints)
        {
            temp_var.getDomain().addLast(value_contraint.getValue());
        }
        return temp_var;




    }





    public void Perform_Value_Ordering_heuristic_for_FC(int[][] Latin_Square_Matrix, int N, Variable variable)
    {
        //copying the matrix
        int[][] Copy_Martix = new int[N+1][N+1];

        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
               Copy_Martix[i][j] = Latin_Square_Matrix[i][j];
            }

        }

        //copying the variable

        Variable Copy_variable = new Variable(variable.getRow_no(),variable.getColumn_no(),N);
        Copy_variable.getDomain().clear();
        for(Integer value : variable.getDomain())
        {
            Copy_variable.getDomain().addLast(value);
        }

        //all copy complete

        //My task to order values of "variable"

        List<Value_Contraint> value_contraints = new ArrayList<Value_Contraint>();

        int row_no = variable.getRow_no();
        int column_no = variable.getColumn_no();


        //ordering
        for(Integer value : variable.getDomain())
        {
            Copy_Martix[row_no][column_no] = value;

            int constraint_count = 1 ;

            for(int i=1;i<=N;i++)
            {
                if(Copy_Martix[row_no][i] == 0 && column_no != i)
                {
                  Variable new_var = new Variable(row_no,i,N);
                  new_var.update_domain(Copy_Martix,N);
                  constraint_count = constraint_count * new_var.get_domain_size();

                }

            }

            for(int i=1;i<=N;i++)
            {
                if(Copy_Martix[i][column_no] == 0 && row_no != i)
                {
                    Variable new_var = new Variable(i,column_no,N);
                    new_var.update_domain(Copy_Martix,N);
                    constraint_count = constraint_count * new_var.get_domain_size();
                }
            }

            value_contraints.add(new Value_Contraint(value,constraint_count));

        }

        Collections.sort(value_contraints);

        //Ordering the value of the variable;
        variable.getDomain().clear();
        for(Value_Contraint value_contraint : value_contraints)
        {
            variable.getDomain().addLast(value_contraint.getValue());
        }


    }





    public void Simple_Back_Tracking(Node node, Variable variable, int assigned_value, String heuristic_name)
    {
        //for the root node the "variable" will be null

        //if all variables are assigned
        if(is_All_Variable_Assigned)
        {
            return;
        }

        node_count++;

        if (variable != null)
        {
            if(is_Consistent_for_BT(node.getLatin_Square_Matrix(),node.getDimension(),variable,assigned_value))
            {
                //if the result is found
                if(node.getVariables().isEmpty())
                {
                    is_All_Variable_Assigned = true;
                    Solved_Node = node;
                    number_of_total_nodes = node_count;
                    number_of_backtracks = back_track_count;


                    return;
                }


                    //System.out.println("value: "+assigned_value);
                    //print_Latin_Square_Matrix(node.getLatin_Square_Matrix(),node.getDimension());


                Variable var = get_Next_Unassigned_Variable(heuristic_name,node);


                int row_no = var.getRow_no();
                int column_no = var.getColumn_no();

                //Here value order heuristic can be applied
              //  System.out.println("Before: "+var.getDomain());

                var = Perform_Value_Ordering_heuristic_for_BT(node.getLatin_Square_Matrix(),node.getDimension(),var);
                //System.out.println("After: "+var.getDomain());



                for(int i=0;i<var.get_domain_size();i++)
                {
                    int[][] Latin_Square_Matrix = node.getLatin_Square_Matrix();

                    int[][] copy_of_Latin_Square_Matrix = make_a_copy_of_Matrix(Latin_Square_Matrix,node.getDimension());


                    copy_of_Latin_Square_Matrix[row_no][column_no] = var.getDomain().get(i);


                    Node new_Node = new Node(copy_of_Latin_Square_Matrix,node.getDimension(),node.getVariables());
                    Simple_Back_Tracking(new_Node,var,var.getDomain().get(i),heuristic_name);
                    if(is_All_Variable_Assigned == true)
                    {
                        break;
                    }


                }





            }
            else {

                back_track_count++;

                return;

            }

        }
        else
        {

            Variable var = get_Next_Unassigned_Variable(heuristic_name,node);

            int row_no = var.getRow_no();
            int column_no = var.getColumn_no();

            //Here value order heuristic can be applied
            var = Perform_Value_Ordering_heuristic_for_BT(node.getLatin_Square_Matrix(),node.getDimension(),var);

            for(int i=0;i<var.get_domain_size();i++)
            {
                int[][] Latin_Square_Matrix = node.getLatin_Square_Matrix();

                int[][] copy_of_Latin_Square_Matrix = make_a_copy_of_Matrix(Latin_Square_Matrix,node.getDimension());

                copy_of_Latin_Square_Matrix[row_no][column_no] = var.getDomain().get(i);
                Node new_Node = new Node(copy_of_Latin_Square_Matrix,node.getDimension(),node.getVariables());
                Simple_Back_Tracking(new_Node,var,var.getDomain().get(i),heuristic_name);
                if(is_All_Variable_Assigned == true)
                {
                    break;
                }


            }


        }
    }


    public void Forward_Checking(Node node, Variable variable, int assigned_value, String heuristic_name)
    {
       // System.out.println(++global_node_count);
        //for the root node the "variable" will be null

        //if all variables are assigned
        if(is_All_Variable_Assigned)
        {
            return;
        }

        node_count++;

        if (variable != null)
        {
            //if the result is found
            if(node.getVariables().isEmpty())
            {
                is_All_Variable_Assigned = true;
                Solved_Node = node;
                number_of_total_nodes = node_count;
                number_of_backtracks = back_track_count;

                return;
            }
            if(is_Consistent_for_FT(node))
            {


                Variable var = get_Next_Unassigned_Variable(heuristic_name,node);


                int row_no = var.getRow_no();
                int column_no = var.getColumn_no();



               // System.out.println(var.getRow_no()+" "+var.getColumn_no()+" has domain "+var.getDomain());

                //Here value order heuristic can be applied
               // System.out.println("Before: "+var.getDomain());
               Perform_Value_Ordering_heuristic_for_FC(node.getLatin_Square_Matrix(),node.getDimension(),var);
                //System.out.println("After: "+var.getDomain());
               // System.out.println(var.getRow_no()+" "+var.getColumn_no() +" -> "+ var.getDomain());

                for(int i=0;i<var.get_domain_size();i++)
                {
                    //System.out.print(node+" : ");
                    //node.dummy_count = node.dummy_count+1;
                    //System.out.println(node.dummy_count);
                    //System.out.println(var.getRow_no()+" "+var.getColumn_no() +" -> " +var.getDomain().get(i));
                    int[][] Latin_Square_Matrix = node.getLatin_Square_Matrix();
                    //System.out.println(dummy_hashset.contains(node+" "+node.dummy_count));

                    //dummy_hashset.add(node+" "+node.dummy_count);


                    int[][] copy_of_Latin_Square_Matrix = make_a_copy_of_Matrix(Latin_Square_Matrix,node.getDimension());

                    copy_of_Latin_Square_Matrix[row_no][column_no] = var.getDomain().get(i);

                    Node new_Node = new Node(copy_of_Latin_Square_Matrix,node.getDimension(),node.getVariables());
                    Forward_Checking(new_Node,var,var.getDomain().get(i),heuristic_name);
                    if(is_All_Variable_Assigned == true)
                    {
                        break;
                    }


                }

            }
            else {
                back_track_count++;
                return;

            }

        }
        else
        {

            node.Update_All_Variable_Domain();
            Variable var = get_Next_Unassigned_Variable(heuristic_name,node);

            int row_no = var.getRow_no();
            int column_no = var.getColumn_no();


            //Here value order heuristic can be applied
            //System.out.println("Before: "+var.getDomain());
           Perform_Value_Ordering_heuristic_for_FC(node.getLatin_Square_Matrix(),node.getDimension(),var);
            //System.out.println("After: "+var.getDomain());

            //System.out.println(var.getRow_no()+" "+var.getColumn_no() +" -> "+ var.getDomain());

            for(int i=0;i<var.get_domain_size();i++)
            {

                //System.out.print(node+" : ");
                //node.dummy_count = node.dummy_count + 1;
                //System.out.println(node.dummy_count);
                //System.out.println(var.getRow_no()+" "+var.getColumn_no() +" -> " +var.getDomain().get(i));

               //System.out.println(dummy_hashset.contains(node+" "+node.dummy_count));

                //dummy_hashset.add(node+" "+node.dummy_count);

                int[][] Latin_Square_Matrix = node.getLatin_Square_Matrix();

                int[][] copy_of_Latin_Square_Matrix = make_a_copy_of_Matrix(Latin_Square_Matrix,node.getDimension());

                copy_of_Latin_Square_Matrix[row_no][column_no] =var.getDomain().get(i);
                Node new_Node = new Node(copy_of_Latin_Square_Matrix,node.getDimension(),node.getVariables());
                Forward_Checking(new_Node,var,var.getDomain().get(i),heuristic_name);
                if(is_All_Variable_Assigned == true)
                {
                    break;
                }


            }


        }
    }


    public void reset()
    {
        is_All_Variable_Assigned = false;
        Solved_Node = null;

        node_count =0;
        back_track_count =0;
    }







}
