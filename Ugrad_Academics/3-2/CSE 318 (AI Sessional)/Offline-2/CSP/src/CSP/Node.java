package CSP;

import java.util.LinkedList;
import java.util.Random;

public class Node {

    private int[][] Latin_Square_Matrix;
    private int dimension;
    private LinkedList<Variable> variables;
    Random random = new Random();

    public Node(int[][] Latin_Square_Matrix,int N,LinkedList<Variable> variables)
    {
        dimension = N;
        this.Latin_Square_Matrix = new int[N+1][N+1];
        this.variables = new LinkedList<Variable>();

        //copying the matrix elements
        for(int i=1;i<N+1;i++)
        {
            for(int j=1;j<N+1;j++)
            {
               this.Latin_Square_Matrix[i][j] = Latin_Square_Matrix[i][j];
            }

        }

        //copying the variables
        for (Variable variable:variables)
        {
            this.variables.addLast(new Variable(variable.getRow_no(),variable.getColumn_no(),N));
        }

    }


    public int[][] getLatin_Square_Matrix() {
        return Latin_Square_Matrix;
    }

    public void setLatin_Square_Matrix(int[][] latin_Square_Matrix) {
        Latin_Square_Matrix = latin_Square_Matrix;
    }

    public int getDimension() {
        return dimension;
    }


    public void setDimension(int dimension) {
        this.dimension = dimension;
    }

    public LinkedList<Variable> getVariables() {
        return variables;
    }

    public void setVariables(LinkedList<Variable> variables) {
        this.variables = variables;
    }

    public void Update_All_Variable_Domain()
    {
        for (Variable variable:variables)
        {
            variable.update_domain(Latin_Square_Matrix,dimension);
        }
    }

    public void Update_All_Variable_Degree()
    {
        for (Variable variable:variables)
        {
            variable.calculate_degree(Latin_Square_Matrix,dimension);
        }
    }


    public Variable Select_A_Variable_By_VAH1()
    {
        int smallest = Integer.MAX_VALUE;
        Variable smallest_domain_variable = null;

        for (Variable variable : variables)
        {
            if(variable.get_domain_size() < smallest)
            {
                smallest = variable.get_domain_size();
                smallest_domain_variable = variable;
            }
        }

        variables.remove(smallest_domain_variable);

        //System.out.println("removing "+smallest_domain_variable.getRow_no()+" "+smallest_domain_variable.getColumn_no());


        return smallest_domain_variable;

    }




    public Variable Select_A_Variable_By_VAH2()
    {
        int largest = Integer.MIN_VALUE;
        Variable largest_degree_variable = null;

        for (Variable variable : variables)
        {
            if(variable.getDegree() > largest)
            {
                largest = variable.getDegree();
                largest_degree_variable = variable;
            }
        }

        variables.remove(largest_degree_variable);

        //System.out.println("At node: "+this+": "+variables.size());
        //System.out.println("("+largest_degree_variable.getRow_no() +","+
            //  largest_degree_variable.getColumn_no() +") removed");



        return largest_degree_variable;

    }


    public Variable Select_A_Variable_By_VAH3()
    {
        int smallest = Integer.MAX_VALUE;
        Variable  VAH3_variable = null;

        for (Variable variable : variables)
        {
            if(variable.get_domain_size() <= smallest)
            {

                if(variable.get_domain_size() == smallest)
                {
                    //tie breaking by VAH2
                    smallest = variable.get_domain_size();
                    if(variable.getDegree() > VAH3_variable.getDegree())
                    {
                        VAH3_variable = variable;
                    }

                }

                else {
                    smallest = variable.get_domain_size();

                    VAH3_variable = variable;
                }
            }
        }

        variables.remove(VAH3_variable);

        return VAH3_variable;

    }




    public  Variable Select_A_Variable_By_VAH4()
    {
        double smallest = Integer.MAX_VALUE;
        Variable smallest_ratio_variable = null;


        for (Variable variable : variables)
        {
            double VAH1_value=(double)variable.get_domain_size();
            double VAH2_value=(double)variable.getDegree();
            if(VAH2_value == 0)
            {
                VAH2_value = 1.0;
            }

            double VAH4_value = VAH1_value/VAH2_value;

            if(VAH4_value < smallest)
            {
                smallest = VAH4_value;
                smallest_ratio_variable = variable;
            }
        }

        variables.remove(smallest_ratio_variable);

        return smallest_ratio_variable;
    }


    public Variable Select_A_Variable_By_VAH5()
    {

        int total_variables = variables.size();

        Variable randomly_selected_variable = variables.get(random.nextInt(total_variables));

       // System.out.println(variables.contains(randomly_selected_variable));
        variables.remove(randomly_selected_variable);
        //System.out.println(variables.contains(randomly_selected_variable));

        //System.out.println(randomly_selected_variable.getRow_no()+" "+randomly_selected_variable.getColumn_no()+" removed");
        return randomly_selected_variable;
    }


}
