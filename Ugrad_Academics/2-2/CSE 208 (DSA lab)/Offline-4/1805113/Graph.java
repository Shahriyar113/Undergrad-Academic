import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Graph {
    Node[] Graph_nodes; //Array of nodes for maintaing the priority queue
    double[][] flows; //basically this is the adjacency matrix of the graph
    double[][] capacities;

    int num_of_nodes; //total nodes in the graph
    int source_index;
    int sink_index;
    int total_game_nodes;
    int total_team_nodes;
    int checking_team_id;

    int[] game_node_indexes;
    int[] team_node_indexes;

    int[] w;
    int[] r;
    int[][] g;

    Graph Residual_Graph;
    Queue<Node> BFS_queue = new LinkedList<Node>();
    Team[] teams;




    Graph(int num_of_nodes,int source_index,int sink_index,int total_game_nodes,int total_team_nodes,
          int checking_team_id,int[] w,int[] r,int[][] g,Team[] teams) {

        this.num_of_nodes=num_of_nodes;
        this.source_index=source_index;
        this.sink_index=sink_index;
        this.total_game_nodes=total_game_nodes;
        this.total_team_nodes=total_team_nodes;
        this.checking_team_id=checking_team_id;

        game_node_indexes=new int[total_game_nodes];
        for(int i=0;i<total_game_nodes;i++)
        {
            game_node_indexes[i]=source_index+i+1;
        }

        team_node_indexes=new int[total_team_nodes];
        for(int i=0;i<total_team_nodes;i++)
        {
            team_node_indexes[i]=source_index+total_game_nodes+1;
        }

        this.w=w;
        this.r=r;
        this.g=g;
        this.teams=teams;

        Graph_nodes=new Node[num_of_nodes];

        flows = new double[num_of_nodes+1][num_of_nodes+1];
        capacities = new double[num_of_nodes+1][num_of_nodes+1];
        BFS_queue = new LinkedList<Node>();




//        Graph_nodes[i] = new Node(i, null)
//
//        Graph_nodes = new Node[num_of_nodes+2]; //extra 1 is for the extra added node
//
//        for (int i = 1; i <= num_of_nodes; i++) {
//            Graph_nodes[i] = new Node(i, null);
//        }
//
//        weights = new double[num_of_nodes+1][num_of_nodes+1];






    }



    class Node {
        int id_No;
        Adjacency_Node next;
        char color; //when a node will extract from priority queue,the node will be "Black colored"
                   //A node is "White Colored" means the node is still in the priority queue;
        Node parent_Node;
        String node_type;
        int team_no;


        Node(int id, Adjacency_Node n) {
            id_No = id;
            next = n;
            color='W';
            parent_Node=null;
            team_no = Integer.MAX_VALUE; //if the node_type is "game node" then team_no=Integer.MAX_VALUE
        }


        int get_id_No() {
            return id_No;
        }
    }

    class Adjacency_Node {
        int adjacent_id_No;
        Adjacency_Node next;
        Node Corresponding_node; //Every adjacency node have their corresponding node of same id
        double capacity;
        double flow;

        Adjacency_Node(int id, Adjacency_Node n, Node corresponding_node,double f,double c) {
            adjacent_id_No = id;
            next = n;
            Corresponding_node=corresponding_node;
            flow=f;
            capacity=c;
        }

        int get_Adjacent_id_No() {
            return adjacent_id_No;
        }

        Node getCorresponding_node()
        {
            return Corresponding_node;
        }

        double getCapacity()
        {
            return capacity;
        }
        double getFlow()
        {
            return flow;
        }


    }




    void BFS_travarse(Node starting_Node,int[] Augmented_path_Array)
    {
        //At first no matter what the starting node will be enqueued

        if(starting_Node.color == 'W')
        {
            BFS_queue.add(starting_Node);
            starting_Node.color='G';
        }



        //Running time of this nested loop = 2*n ( n= total number of nodes)
        while (!BFS_queue.isEmpty())
        {
            Node popped_node=null;
            popped_node = BFS_queue.remove();



          //  System.out.print(popped_node.get_id_No()+" ");

            Adjacency_Node Current_node = popped_node.next;

            //while enqueuing a node in the queue, it should be checked that
            //the node is previously visited or not..if visited,then don,t enqueue it,otherwise enqueue the node
            //a node is enqueued means the node is visited...So mark the node "visited"...
            // Then, i should check whether there are pieces exists or not at that node(location)
            //if pieces exists, then the "friend id" will collect all of it and then that location will have no pieces

            while (Current_node != null)
            {
                if (Current_node.getCorresponding_node().color == 'W') {
                    BFS_queue.add(Current_node.getCorresponding_node());
                    Augmented_path_Array[Current_node.getCorresponding_node().id_No]=popped_node.id_No;
                    Current_node.getCorresponding_node().color = 'G';

                    Current_node = Current_node.next;

                } else {
                    Current_node = Current_node.next;
                }
            }

            popped_node.color='B';



        }
    }


    void forming_graph()
    {
        int graph_node_index=0;

        Graph_nodes[source_index]=new Node(source_index,null); //creating source node
        Graph_nodes[source_index].node_type="SOURCE";

        Graph_nodes[sink_index]=new Node(sink_index,null); //creating source node
        Graph_nodes[sink_index].node_type="SINK";

        //creating team nodes
        graph_node_index=source_index+total_game_nodes+1;


        for(int i=0;i<total_team_nodes;i++)
        {
            if(i!=checking_team_id)
            {
                Graph_nodes[graph_node_index]=new Node(graph_node_index,null);
                Graph_nodes[graph_node_index].node_type="TEAM_NODE";
                Graph_nodes[graph_node_index].team_no=i;

                //creating edges between team_node and sink
                add_Nodes(graph_node_index,sink_index,0,w[checking_team_id]+r[checking_team_id]-w[i]);
                flows[graph_node_index][sink_index] =0;
                capacities[graph_node_index][sink_index]=w[checking_team_id]+r[checking_team_id]-w[i];

                graph_node_index++;
            }

        }


        //creating game nodes

        graph_node_index=source_index+1;

        for(int i=0;i<total_team_nodes-1;i++)
        {
            for(int j=i+1;j<total_team_nodes;j++)
            {
                if(i==checking_team_id || j==checking_team_id)
                {
                    continue;
                }
                else
                {
                    Graph_nodes[graph_node_index]=new Node(graph_node_index,null);
                    Graph_nodes[graph_node_index].node_type="GAME_NODE";


                    //creating edge source node to game node
                    add_Nodes(source_index,graph_node_index,0,g[i][j]);
                    flows[source_index][graph_node_index]=0;
                    capacities[source_index][graph_node_index]=g[i][j];

                    //creating edge game node to team node
                    for(int p=source_index+total_game_nodes+1;p<num_of_nodes-1;p++)
                    {
                        if(Graph_nodes[p].team_no==i || Graph_nodes[p].team_no==j)
                        {
                            add_Nodes(graph_node_index,p,0,Integer.MAX_VALUE);
                            flows[graph_node_index][p]=0;
                            capacities[graph_node_index][p]=Integer.MAX_VALUE;
                        }
                    }

                    graph_node_index++;




                }

            }
        }

    }


    void forming_residual_graph()
    {
        Residual_Graph = new Graph(num_of_nodes,source_index,sink_index,total_game_nodes,
                total_team_nodes, checking_team_id, w, r,g,teams);
        //in residual graph all "flow" value will be infinity...as there are no flow in residual graph
        int graph_node_index=0;

        Residual_Graph.Graph_nodes[Residual_Graph.source_index]=new Node(Residual_Graph.source_index,null); //creating source node
        Residual_Graph.Graph_nodes[Residual_Graph.source_index].node_type="SOURCE";

        Residual_Graph.Graph_nodes[Residual_Graph.sink_index]=new Node(Residual_Graph.sink_index,null); //creating source node
        Residual_Graph.Graph_nodes[Residual_Graph.sink_index].node_type="SINK";

        //creating team nodes
        graph_node_index=Residual_Graph.source_index+Residual_Graph.total_game_nodes+1;


        for(int i=0;i<total_team_nodes;i++)
        {
            if(i!=checking_team_id)
            {
                Residual_Graph.Graph_nodes[graph_node_index]=new Node(graph_node_index,null);
                Residual_Graph. Graph_nodes[graph_node_index].node_type="TEAM_NODE";
                Residual_Graph.Graph_nodes[graph_node_index].team_no=i;

                //creating edges between team_node and sink
                if(capacities[graph_node_index][sink_index] > 0  )
                {

                    if(flows[graph_node_index][sink_index] < capacities[graph_node_index][sink_index])
                    {//forward edge
                        Residual_Graph.add_Nodes(graph_node_index,sink_index, Integer.MAX_VALUE,
                                capacities[graph_node_index][sink_index]-flows[graph_node_index][sink_index]);
                        Residual_Graph.flows[graph_node_index][sink_index]=Integer.MAX_VALUE;
                        Residual_Graph.capacities[graph_node_index][sink_index]=capacities[graph_node_index][sink_index]-flows[graph_node_index][sink_index];

                    }

                    if(flows[graph_node_index][sink_index] > 0 )
                    {//backward edge
                        Residual_Graph.add_Nodes(sink_index,graph_node_index, Integer.MAX_VALUE,
                                flows[graph_node_index][sink_index]);

                        Residual_Graph.flows[graph_node_index][sink_index]=Integer.MAX_VALUE;
                        Residual_Graph.capacities[sink_index][graph_node_index]=flows[graph_node_index][sink_index];
                    }




                }

                //Residual_Graph.add_Nodes(graph_node_index,Residual_Graph.sink_index,Integer.MAX_VALUE,w[checking_team_id]+r[checking_team_id]-w[i]);
                graph_node_index++;
            }

        }


        //creating game nodes

        graph_node_index=source_index+1;

        for(int i=0;i<Residual_Graph.total_team_nodes-1;i++)
        {
            for(int j=i+1;j<Residual_Graph.total_team_nodes;j++)
            {
                if(i==Residual_Graph.checking_team_id || j==Residual_Graph.checking_team_id)
                {
                    continue;
                }
                else
                {
                    Residual_Graph.Graph_nodes[graph_node_index]=new Node(graph_node_index,null);
                    Residual_Graph.Graph_nodes[graph_node_index].node_type="GAME_NODE";


                    //creating edge source node to game node

                    if(capacities[source_index][graph_node_index] > 0  )
                    {

                        if(flows[source_index][graph_node_index] < capacities[source_index][graph_node_index])
                        {//forward edge
                            Residual_Graph.add_Nodes(source_index,graph_node_index, Integer.MAX_VALUE,
                                    capacities[source_index][graph_node_index]-flows[source_index][graph_node_index]);
                            Residual_Graph.flows[source_index][graph_node_index]=Integer.MAX_VALUE;
                            Residual_Graph.capacities[source_index][graph_node_index]=capacities[source_index][graph_node_index]-flows[source_index][graph_node_index];

                        }

                        if(flows[source_index][graph_node_index] > 0 )
                        {//backward edge
                            Residual_Graph.add_Nodes(graph_node_index,source_index, Integer.MAX_VALUE,
                                    flows[source_index][graph_node_index]);

                            Residual_Graph.flows[graph_node_index][source_index]=Integer.MAX_VALUE;
                            Residual_Graph.capacities[graph_node_index][source_index]=flows[source_index][graph_node_index];
                        }




                    }


                    //creating edge game node to team node
                    for(int p=source_index+total_game_nodes+1;p<num_of_nodes-1;p++)
                    {
                        if(Residual_Graph.Graph_nodes[p].team_no==i || Residual_Graph.Graph_nodes[p].team_no==j)
                        {
                            if(capacities[graph_node_index][p] > 0  )
                            {

                                if(flows[graph_node_index][p] < capacities[graph_node_index][p])
                                {//forward edge
                                    Residual_Graph.add_Nodes(graph_node_index,p, Integer.MAX_VALUE,
                                            capacities[graph_node_index][p]-flows[graph_node_index][p]);
                                    Residual_Graph.flows[graph_node_index][p]=Integer.MAX_VALUE;
                                    Residual_Graph.capacities[graph_node_index][p]=capacities[graph_node_index][p]-flows[graph_node_index][p];

                                }

                                if(flows[graph_node_index][p] > 0 )
                                {//backward edge
                                    Residual_Graph.add_Nodes(p,graph_node_index, Integer.MAX_VALUE,
                                            flows[graph_node_index][p]);

                                    Residual_Graph.flows[graph_node_index][p]=Integer.MAX_VALUE;
                                    Residual_Graph.capacities[p][graph_node_index]=flows[graph_node_index][p];
                                }




                            }

                        }
                    }

                    graph_node_index++;




                }

            }
        }

    }



    void Finding_Max_flow()
    {
        forming_graph(); //building the graph
        //show_capacities();


        int index=source_index+total_game_nodes+1;
        int team_id=-1;
        Boolean trivially_eliminated=false;

        for(int i=index;i<num_of_nodes-1;i++)
        {

            if(capacities[i][sink_index] < 0)
            {
                trivially_eliminated=true;
                team_id=i;
                break;
            }
        }

       // trivial case

        if(trivially_eliminated == true)
        {
            System.out.println(teams[checking_team_id] + " is Eliminated");

            int max_win=w[checking_team_id]+r[checking_team_id];
            System.out.println("They can win "+w[checking_team_id] +" + "
                    +r[checking_team_id]+" = "+(w[checking_team_id]+r[checking_team_id]) +" games" );
            System.out.println(teams[Graph_nodes[team_id].team_no]+" has won total "+w[Graph_nodes[team_id].team_no]+" games");
            System.out.println("They play each other 0 times");
            System.out.println("So on average,each of the teams in this group wins "+
                    w[Graph_nodes[team_id].team_no]+"/1"+" = "+w[Graph_nodes[team_id].team_no]+" games");

            System.out.println();

        }



        //Non trivial case
        else {

            while (true) {
                forming_residual_graph();

                int[] Augmented_path_array = new int[num_of_nodes];
                //initializing the array
                for (int i = 0; i < num_of_nodes; i++) {
                    if (i == 0) {
                        Augmented_path_array[i] = -2; //means Oth indexed node can't have any parent
                        continue;
                    }
                    Augmented_path_array[i] = -1;//means ith indexed node have parent but we haven't
                    //find the parent yet

                }


                Residual_Graph.BFS_travarse(Residual_Graph.Graph_nodes[0], Augmented_path_array);

                if (Augmented_path_array[num_of_nodes - 1] == -1) {
                    break; //There is no more augmenting path in Residual graph
                }
//        for(int i=0;i<num_of_nodes;i++)
//        {
//            System.out.print(Augmented_path_array[i]+" ");
//        }

                //finding Augmented path
                LinkedList<AP_Edge> AP_path_edges = new LinkedList<AP_Edge>();
                for (int i = num_of_nodes - 1; i != 0; ) {
                    int node1_id = Augmented_path_array[i];
                    int node2_id = i;
                    double capacity = Residual_Graph.capacities[node1_id][node2_id];
                    AP_path_edges.addFirst(new AP_Edge(node1_id, node2_id, capacity));

                    i = Augmented_path_array[i];

                }

                //finding "bottleneck capacity"
                double bottleneck_capacity = Integer.MAX_VALUE;

                for (AP_Edge x : AP_path_edges) {

                    if (x.capacity < bottleneck_capacity) {
                        bottleneck_capacity = x.capacity;
                    }
                }

                //Augmenting the path in the main graph(updating flow of augmented path)

                for (AP_Edge x : AP_path_edges) {
                    flows[x.node1_id][x.node2_id] = flows[x.node1_id][x.node2_id] + bottleneck_capacity;
                }

                Residual_Graph.reset_all_nodes();


            }


//            System.out.println(teams[checking_team_id]);
//        show_capacities();
//        System.out.println();
//        show_flows();
//        System.out.println();
//        System.out.println();
            //finding if "x" got eliminated or not

            double max_capacity_from_source = 0.0;
            double max_flow_from_source = 0.0;

            for (int i = 0; i < num_of_nodes; i++) {
                max_capacity_from_source = max_capacity_from_source + capacities[0][i];
                max_flow_from_source = max_flow_from_source + flows[0][i];
            }

//
//            double to_sink=0.0;
//            for (int i=index;i<num_of_nodes-1;i++)
//            {
//                to_sink=to_sink+capacities[i][sink_index];
//            }
//
//            System.out.println(max_flow_from_source+"="+to_sink);

            if (max_flow_from_source != max_capacity_from_source) {
                System.out.println(teams[checking_team_id] + " is Eliminated");


                //Finding Min cut

                index = source_index + total_game_nodes + 1;


                List<Integer> result_teams = new ArrayList<Integer>();
                int[] A = new int[num_of_nodes]; //dummy array..no use
                Residual_Graph.BFS_travarse(Residual_Graph.Graph_nodes[0], A);
                int num_of_result_teams_count = 0;


                for (int i = index; i < num_of_nodes - 1; i++) {
                    //System.out.print(i+" ");
                    if (Residual_Graph.Graph_nodes[i].color == 'B') {
                        result_teams.add(Graph_nodes[i].team_no);
                        num_of_result_teams_count++;
                    }
                }


                int total_result_team_wins = 0;
                int total_result_team_remaining_matches = 0;
                String result_team_names = "";

                for (Integer x : result_teams) {
                    total_result_team_wins = total_result_team_wins + w[x];
                    result_team_names = result_team_names + teams[x] + " ";

                }


                for (int i = 0; i < num_of_result_teams_count - 1; i++) {
                    for (int j = i + 1; j < num_of_result_teams_count; j++) {
                        total_result_team_remaining_matches = total_result_team_remaining_matches +
                                g[result_teams.get(i)][result_teams.get(j)];

                    }
                }


                //finding total matches among the result teams


                System.out.println("They can win " + w[checking_team_id] + " + "
                        + r[checking_team_id] + " = " + (w[checking_team_id] + r[checking_team_id]) + " games");
                System.out.println(result_team_names + " have won total " + total_result_team_wins + " games");
                System.out.println("They play each other " + total_result_team_remaining_matches + " times");
                System.out.println("So on average,each of the teams wins " +
                        (total_result_team_wins + total_result_team_remaining_matches) + "/" + num_of_result_teams_count + " = "
                        + ((double) (total_result_team_wins + total_result_team_remaining_matches) / (double) num_of_result_teams_count)
                        + " games");

                System.out.println();


            }
        }












    }








    void add_Nodes(int id_No, int adjacent_id_no,double f,double c) {

        Adjacency_Node new_adjacency_node = new Adjacency_Node(adjacent_id_no, null,Graph_nodes[adjacent_id_no],f,c);

        //if the city_node has not any adjacency node
        if (Graph_nodes[id_No].next == null) {
            Graph_nodes[id_No].next = new_adjacency_node;
        }

        //if the city_node has one or more than one adjacency node

        else {
            Adjacency_Node Current_Node = Graph_nodes[id_No].next;

            while (Current_Node.next != null) {
                Current_Node = Current_Node.next;
            }

            Current_Node.next = new_adjacency_node;

        }



    }


    //will show the adjacency list of the graph
    void show_Graph_AdjacencyList()
    {
        for (int i=0;i<num_of_nodes;i++)
        {
            System.out.print(Graph_nodes[i].get_id_No()+": ");
            Adjacency_Node current_node = Graph_nodes[i].next;

            while(current_node != null)
            {
                int id=Graph_nodes[i].get_id_No();
                int Adj_id=current_node.get_Adjacent_id_No();
                double flow = flows[id][Adj_id];
                double capacity=capacities[id][Adj_id];

                System.out.print(current_node.get_Adjacent_id_No()+"("+flow+","+capacity +")"+" ");

                current_node=current_node.next;

            }

            System.out.println();
        }

    }


    void show_flows()
    {
        for (int r=0;r<num_of_nodes;r++)
        {
            for (int c=0;c<num_of_nodes;c++)
            {
                System.out.print(flows[r][c]+" ");
            }
            System.out.println();
        }
    }

    void show_capacities()
    {
        for (int r=0;r<num_of_nodes;r++)
        {
            for (int c=0;c<num_of_nodes;c++)
            {
                System.out.print(capacities[r][c]+" ");
            }
            System.out.println();
        }
    }

    void reset_all_nodes()
    {
        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].color = 'W';
            Graph_nodes[i].parent_Node = null;
        }
    }







}





