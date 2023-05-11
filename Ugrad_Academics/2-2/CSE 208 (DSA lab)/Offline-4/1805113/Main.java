import java.io.File;
import java.util.Scanner;

class Main {


    public static void main(String[] args) {

        try {
            File file = new File("Input.txt");

            Scanner input = new Scanner(file);

            int num_of_team_nodes = input.nextInt();
            input.nextLine();

            Team[] teams = new Team[num_of_team_nodes];
            int[] w = new int[num_of_team_nodes];
            int[] l = new int[num_of_team_nodes];
            int[] r = new int[num_of_team_nodes];
            int[][] g = new int[num_of_team_nodes][num_of_team_nodes];


            for (int i = 0; i < num_of_team_nodes; i++) {

                    String team_name = input.next();
                    teams[i]=new Team(i,team_name);

                    w[i] = input.nextInt();
                    l[i] = input.nextInt();
                    r[i] = input.nextInt();

                    for (int j = 0; j < num_of_team_nodes; j++) {
                        g[i][j] = input.nextInt();
                    }

            }

            int num_of_game_nodes_in_each_graph =(num_of_team_nodes-1)*(num_of_team_nodes-2)/2;
            int num_of_teams_in_each_graph = num_of_team_nodes-1;
            int source_index=0;


            int total_nodes_in_each_graph=2 + num_of_teams_in_each_graph +num_of_game_nodes_in_each_graph;
            //System.out.println(total_nodes_in_each_graph);
            int sink_index=total_nodes_in_each_graph-1;

//            Graph graph=new Graph(total_nodes_in_each_graph,source_index,sink_index,
//                        num_of_game_nodes_in_each_graph,
//                        num_of_team_nodes,4,w,r,g,teams);
//
//
//            graph.Finding_Max_flow();
//


            //Graph[] graphs=new Graph[num_of_team_nodes];
//
            for(int i=0;i<num_of_team_nodes;i++)
            {
                Graph graph=new Graph(total_nodes_in_each_graph,source_index,sink_index,
                        num_of_game_nodes_in_each_graph,
                        num_of_team_nodes,i,w,r,g,teams);

                graph.Finding_Max_flow();


            }




//            graph.forming_graph();
//            graph.forming_residual_graph();
//
//            graph.show_Graph_AdjacencyList();
//
//            graph.Residual_Graph.show_Graph_AdjacencyList();
//
//
//            graph.show_capacities();
//
//            System.out.println();
//            graph.Residual_Graph.show_capacities();



           // graph.Residual_Graph.show_Graph_AdjacencyList();



        } catch (Exception e) {
            e.printStackTrace();
        }


    }
}





