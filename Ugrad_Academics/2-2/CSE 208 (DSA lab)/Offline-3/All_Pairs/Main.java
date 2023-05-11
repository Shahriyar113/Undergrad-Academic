package All_Pairs;

import java.io.File;
import java.util.Scanner;

class Main {



    public static void main(String[] args) {

        try {
            File file=new File("Input.txt");

            Scanner input = new Scanner(file);

            int num_of_nodes =input.nextInt();
            int num_of_edges = input.nextInt();

            Graph graph=new Graph(num_of_nodes,num_of_edges);


            for(int i=0;i<num_of_edges;i++)
            {

                int node1=input.nextInt();
                int node2=input.nextInt();
                double weight=input.nextDouble();

                graph.add_Nodes(node1,node2,weight);


            }


            //graph.FW_ALL_Pair_Shortest_Path();

            graph.Johnson_All_pair_Shortest_Path();


        }catch (Exception e)
        {
            e.printStackTrace();
        }




    }


}





