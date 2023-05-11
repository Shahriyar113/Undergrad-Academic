package N_Puzzle;

public class Node implements Comparable<Node> {
    private int[][] grid;
    private int k;
    private int g_value;
    private int h_value;
    private int f_value;
    private Node parent;
    private String moving_info;

    public Node(int[][] grid,int k,int g_value,int h_value,Node parent,String moving_info)

    {
        this.grid = grid;
        this.k=k;
        this.g_value=g_value;
        this.h_value=h_value;
        this.f_value=calcluate_f_value();
        this.parent = parent;
        this.moving_info = moving_info;



    }
   public void setMoving_info(String moving_info)
   {
       this.moving_info = moving_info;
   }

    public int[][] getGrid() {
        return grid;
    }

    public int getG_value() {
        return g_value;
    }

    public int getH_value() {
        return h_value;
    }

    public int getF_value() {
        return f_value;
    }

    public int get_K()
    {
        return k;
    }

    public String getMoving_info()
    {
        return moving_info;
    }

    public Node getParent()
    {
        return parent;
    }

    int calcluate_f_value()
    {
       f_value  = g_value + h_value;
       return f_value;
    }

    boolean is_Identical(int[][] grid2)
    {
        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
               if(grid[i][j] != grid2[i][j])
               {
                   return false;
               }
            }
        }

        return true;
    }




    @Override
    public int compareTo(Node node) {
        if(f_value > node.getF_value())
        {
            return 1;
        }
        else
        {
            return -1;
        }

    }
}
