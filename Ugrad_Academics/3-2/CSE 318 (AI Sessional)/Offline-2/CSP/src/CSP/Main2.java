package CSP;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main2 {



        public static void main(String[] args) {
            try{

                File file = new File("d-15-01.txt");
                Scanner input = new Scanner(file);

                //taking input "k"
                int N = input.nextInt();

                //start array indexing from 1;
                int[][] Latin_Square_Matrix = new int[N+1][N+1];

                //taking input for Matrix
                for(int i=1;i<N+1;i++)
                {
                    for(int j=1;j<N+1;j++)
                    {
                        Latin_Square_Matrix[i][j] = input.nextInt();
                    }

                }

                //Solvability check

                //if any value is repeated in arow or column

                for(int row=1;row<N+1;row++)
                {
                    for(int col=1;col<N+1;col++)
                    {
                        if(Latin_Square_Matrix[row][col] != 0)
                        {
                            for(int i=1;i<=N;i++)
                            {
                                if(col != i )
                                {
                                    if(Latin_Square_Matrix[row][col] == Latin_Square_Matrix[row][i])
                                    {
                                        System.out.println(row+" "+col);
                                        System.out.println("THERE IS NO SOLUTION");
                                        return;
                                    }
                                }
                            }

                            for(int i=1;i<=N;i++)
                            {
                                if(row != i)
                                {
                                    if(Latin_Square_Matrix[row][col] == Latin_Square_Matrix[i][col])
                                    {
                                        System.out.println(row+" "+col);

                                        System.out.println("THERE IS NO SOLUTION");
                                        return;
                                    }

                                }
                            }
                        }
                    }

                }


                //solvability check ends



                CSP csp = new CSP();
//
            //Finding variables

            for(int i=1;i<=N;i++)
            {
                for(int j=1;j<=N;j++)
                {
                   if(Latin_Square_Matrix[i][j] == 0)
                   {
                       csp.add_variable(new Variable(i,j,N));
                   }
                }

            }


            Node root = new Node(Latin_Square_Matrix,N,csp.getVariables());
            long starting_time = System.currentTimeMillis();

               csp.Simple_Back_Tracking(root,null,0,"VAH3");
         // csp.Forward_Checking(root,null,0,"VAH3");
            long ending_time = System.currentTimeMillis();



            csp.print_Solved_Latin_Square_Matrix();

            System.out.println("Total num of nodes: "+csp.getNumber_of_total_nodes());
            System.out.println("Total num of backtrack: "+csp.getNumber_of_backtracks());
            System.out.println("Total time: "+(ending_time-starting_time)+" ms");





            }


            catch (Exception e)
            {
                e.printStackTrace();
            }
        }



}
