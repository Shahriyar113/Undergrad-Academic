package CSP;

import java.io.File;
import java.util.Scanner;

//for VAH1,VAH3,VAH4
public class Main {

    public static void main(String[] args) {
        try{

            String[] files ={"d-10-01.txt","d-10-06.txt","d-10-07.txt","d-10-08.txt","d-10-09.txt","d-15-01.txt"};
           //String[] files ={"d-10-06.txt"};


            for (int k=0;k<files.length;k++) {
                System.out.println("start Processing from Input file: "+files[k]);
                System.out.println("----------------------------------------------");

                File file = new File(files[k]);
                Scanner input = new Scanner(file);

                //taking input "k"
                int N = input.nextInt();

                //start array indexing from 1;
                int[][] Latin_Square_Matrix = new int[N + 1][N + 1];

                //taking input for Matrix
                for (int i = 1; i < N + 1; i++) {
                    for (int j = 1; j < N + 1; j++) {
                        Latin_Square_Matrix[i][j] = input.nextInt();
                    }

                }


                //checking all performence


                System.out.println("For Backtracking:");
                System.out.println("--------------------");
                //    for backtracking
                for (int i = 1; i <= 5; i++) {
                    CSP csp = new CSP();

                    //Finding variables

                    for (int c = 1; c <= N; c++) {
                        for (int j = 1; j <= N; j++) {
                            if (Latin_Square_Matrix[c][j] == 0) {
                                csp.add_variable(new Variable(c, j, N));
                            }
                        }

                    }

                    Node root = new Node(Latin_Square_Matrix, N, csp.getVariables());
                    if (i != 2 && i != 5) {
                        String heuristic_name = "VAH" + i;
                        long starting_time = System.nanoTime() / 1000000;
                        csp.Simple_Back_Tracking(root, null, 0, heuristic_name);
                        long ending_time = System.nanoTime() / 1000000;
                        csp.print_Solved_Latin_Square_Matrix();
                        System.out.println("Total num of nodes for " + heuristic_name + " : " + csp.getNumber_of_total_nodes());
                        System.out.println("Total backtracks for " + heuristic_name + " : " + csp.getNumber_of_backtracks());
                        System.out.println("Time taken for " + heuristic_name + " : " + (ending_time - starting_time) + " ms");


                        System.out.println();
                        System.out.println();

                    }


                }


                //for Forward Checking

                System.out.println("For Forward Checking:");
                System.out.println("--------------------");
                for (int i = 1; i <= 5; i++) {
                    CSP csp = new CSP();

                    //Finding variables

                    for (int c = 1; c <= N; c++) {
                        for (int j = 1; j <= N; j++) {
                            if (Latin_Square_Matrix[c][j] == 0) {
                                csp.add_variable(new Variable(c, j, N));
                            }
                        }

                    }

                    Node root = new Node(Latin_Square_Matrix, N, csp.getVariables());

                    if (i != 2 && i != 5) {
                        String heuristic_name = "VAH" + i;
                        long starting_time = System.nanoTime() / 1000000;
                        csp.Forward_Checking(root, null, 0, heuristic_name);
                        long ending_time = System.nanoTime() / 1000000;
                        csp.print_Solved_Latin_Square_Matrix();
                        System.out.println("Total num of nodes for " + heuristic_name + " : " + csp.getNumber_of_total_nodes());
                        System.out.println("Total backtracks for " + heuristic_name + " : " + csp.getNumber_of_backtracks());
                        System.out.println("Time taken for " + heuristic_name + " : " + (ending_time - starting_time) + " ms");


                        System.out.println();
                        System.out.println();


                    }

                }


                System.out.println("------------------------------------------");
                System.out.println("End Processing from Input file: "+files[k]);
                System.out.println();
                System.out.println();


            }
//
////
//

        }


        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

}
