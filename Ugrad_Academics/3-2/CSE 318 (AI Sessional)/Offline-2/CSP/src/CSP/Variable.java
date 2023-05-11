package CSP;

import java.util.LinkedList;

public class Variable {

    private int row_no;
    private int column_no;
    private int degree;

    private LinkedList<Integer> domain;

    public Variable(int row_no,int column_no,int N)
    {
        this.row_no = row_no;
        this.column_no = column_no;
        domain = new LinkedList<>();

        //initially every variable has domain = 1...N
        for(int i=1;i<=N;i++)
        {
            domain.addLast(i);
        }

    }

    public void initialize_domain(int N)
    {
        domain.clear();
        for(int i=1;i<=N;i++)
        {
            domain.addLast(i);
        }

    }


    public int getRow_no() {
        return row_no;
    }

    public void setRow_no(int row_no) {
        this.row_no = row_no;
    }

    public int getColumn_no() {
        return column_no;
    }

    public void setColumn_no(int column_no) {
        this.column_no = column_no;
    }

    public LinkedList<Integer> getDomain() {
        return domain;
    }

    public void setDomain(LinkedList<Integer> domain) {
        this.domain = domain;
    }

    public int get_domain_size()
    {
        return domain.size();
    }

    public int getDegree()
    {
        return degree;
    }

    public void calculate_degree(int[][] Latin_Square_Matrix,int N)
    {
        int degree_count = 0;

        //traversing the variable row
        for(int i=1;i<=N;i++)
        {
            if(Latin_Square_Matrix[row_no][i] == 0 && column_no != i)
            {
                degree_count++;
            }
        }

        //traversing the original column
        for(int i=1;i<=N;i++)
        {
            if(Latin_Square_Matrix[i][column_no] == 0 && row_no != i)
            {
                degree_count++;
            }
        }

        this.degree = degree_count;


    }


    public void update_domain(int[][] Latin_Square_Matrix,int N)
    {
        initialize_domain(N);

        for(int i=1;i<=N;i++)
        {
            if(Latin_Square_Matrix[row_no][i] != 0 && column_no != i)
            {
                //domain.remove()
                Integer illegal_value = Latin_Square_Matrix[row_no][i];
                domain.remove(illegal_value);

            }
        }

        for(int i=1;i<=N;i++)
        {
            if(Latin_Square_Matrix[i][column_no] != 0 && row_no != i)
            {

                Integer illegal_value =Latin_Square_Matrix[i][column_no];
                domain.remove(illegal_value);
            }
        }
    }



}
