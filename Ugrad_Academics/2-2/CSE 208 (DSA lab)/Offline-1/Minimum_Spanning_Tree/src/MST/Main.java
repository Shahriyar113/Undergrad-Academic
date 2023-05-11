package MST;

import java.io.File;
import java.util.Scanner;

class Main {



    public static void main(String[] args) {

        try {
            File file=new File("Input.txt");

            Scanner input = new Scanner(file);

            int num_of_nodes =input.nextInt();
            int num_of_edge = input.nextInt();

            Graph graph=new Graph(num_of_nodes);

            Kruskal_Sorting kruskal_sorting=new Kruskal_Sorting(); //for kruskal sorting



            for(int i=0;i<num_of_edge;i++)
            {

                int node1=input.nextInt();
                int node2=input.nextInt();
                double weight=input.nextDouble();

                graph.add_Nodes(node1,node2,weight);

                graph.add_Nodes(node2,node1,weight);

                kruskal_sorting.list.add(new Edges_And_Weights(node1,node2,weight));

            }
            System.out.println();



            graph.MST_Prims(0);

            System.out.println();
            System.out.println();

            graph.Kruskal_MST(kruskal_sorting.list);

        }catch (Exception e)
        {
            e.printStackTrace();
        }




    }


}





