package All_Pairs;

import javafx.scene.control.skin.CellSkinBase;

import java.util.ArrayList;
import java.util.LinkedList;

class Graph {
    Node[] Graph_nodes; //Array of nodes for maintaing the priority queue
    int num_of_nodes,num_of_edges;
    double[][] weights; //basically this is the adjacency matrix of the graph
    ArrayList<BF_Edge> edge_list;
    double[][] distance_matrix; //for floyd_Warshall
    boolean has_negative_edge_cycle=false;
    double[][] new_weights; //weights after reweighting in johnson's method


    Graph(int num_of_nodes,int num_of_edges) {

        //initializing the the array of nodes for adjacency list
        this.num_of_nodes=num_of_nodes;
        this.num_of_edges=num_of_edges;

        Graph_nodes = new Node[num_of_nodes+2]; //extra 1 is for the extra added node

        for (int i = 1; i <= num_of_nodes; i++) {
            Graph_nodes[i] = new Node(i, null);
        }

        weights = new double[num_of_nodes+1][num_of_nodes+1];
        distance_matrix = new double[num_of_nodes+1][num_of_nodes+1];
        new_weights = new double[num_of_nodes+1][num_of_nodes+1];



        //intiallize the adjacency matrix
        for (int i=1;i<=num_of_nodes;i++)
        {
            for (int j=1;j<=num_of_nodes;j++)
            {
                if(i==j)
                {
                    weights[i][j]=0.0;
                    distance_matrix[i][j]=0.0;
                }
                else
                {
                    weights[i][j]=Integer.MAX_VALUE;
                    distance_matrix[i][j]=Integer.MAX_VALUE;
                }
            }
        }



        edge_list=new ArrayList<BF_Edge>();


    }



    class Node {
        int id_No;
        Adjacency_Node next;
        char color; //when a node will extract from priority queue,the node will be "Black colored"
                   //A node is "White Colored" means the node is still in the priority queue;
        Node parent_Node;

        //shortest_path ==> Shortest path cost from source to this node
        double dijkstra_shortest_path; // parameter of priority queue
                //also represents the minimum weight conncted with the corresponded key
        double Bellman_Ford_shortest_path;

        int priority_queue_node_index;


        Node(int id, Adjacency_Node n) {
            id_No = id;
            next = n;
            color='W';
            parent_Node=null;
        }


        int get_id_No() {
            return id_No;
        }
    }

    class Adjacency_Node {
        int adjacent_id_No;
        Adjacency_Node next;
        Node Corresponding_node; //Every adjacency node have their corresponding node of same id
        double weight;

        Adjacency_Node(int id, Adjacency_Node n, Node corresponding_node,double w) {
            adjacent_id_No = id;
            next = n;
            Corresponding_node=corresponding_node;
            weight=w;
        }

        int get_Adjacent_id_No() {
            return adjacent_id_No;
        }

        Node getCorresponding_node()
        {
            return Corresponding_node;
        }

        double getWeight()
        {
            return weight;
        }


    }


    void add_Nodes(int id_No, int adjacent_id_no,double w) {

        Adjacency_Node new_adjacency_node = new Adjacency_Node(adjacent_id_no, null,Graph_nodes[adjacent_id_no],w);

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


        try {
            weights[id_No][adjacent_id_no]=w;
            distance_matrix[id_No][adjacent_id_no]=w;
        }catch (Exception e)
        {
            ;
        }


    }

    //Complexity ==> O(ElogV)
    void Dijkstra_Shortest_Path(int source)
    {
        Node source_node=Graph_nodes[source];

        for (int i=1;i<=num_of_nodes;i++)
        {
            Graph_nodes[i].dijkstra_shortest_path = Integer.MAX_VALUE;
            Graph_nodes[i].parent_Node=null;
        }

        Graph_nodes[source].dijkstra_shortest_path=0;


        Min_Priority_Queue min_pq = new Min_Priority_Queue(Graph_nodes,num_of_nodes);

        min_pq.build_Min_heap(); // cost ==> O(V)

        while (!min_pq.isEmpty())
        {
            Node u = min_pq.Extract_Min(); //cost => O(VlogV) (considering the while loop)
            ; //when a node will extract from priority queue,the node will be "Black colored"
            u.color='B';

            Adjacency_Node v=u.next;

            while(v !=null) //O(E)
            {
                //Relaxation
                if(v.getCorresponding_node().color == 'W' &&
                        u.dijkstra_shortest_path + new_weights[u.get_id_No()][v.getCorresponding_node().get_id_No()] < v.getCorresponding_node().dijkstra_shortest_path)
                {
                    v.getCorresponding_node().parent_Node=u;
                    v.getCorresponding_node().dijkstra_shortest_path =  u.dijkstra_shortest_path +
                                                                    new_weights[u.get_id_No()][v.getCorresponding_node().get_id_No()];

                    //priority queue index== node ta pririty queue er kon index a ase sheita
                    min_pq.Min_heapify_dynamic(v.getCorresponding_node().priority_queue_node_index);  //cost ==>O(Elogv) //(considering both the while loop)

                }

                v = v.next;
            }


        }


    }


    void Making_Edge_List()
    {
        for (int i=1;i<=num_of_nodes+1;i++)
        {
            Node u = Graph_nodes[i];
            Adjacency_Node v = Graph_nodes[i].next;

            while(v != null)
            {
                edge_list.add(new BF_Edge(u,v.getCorresponding_node(),v.getWeight()));
                v=v.next;

            }

        }
    }


    void Bellman_Ford_Shortest_Path(int source)
    {
        for (int i=1;i<num_of_nodes+1;i++)
        {
            Graph_nodes[i].Bellman_Ford_shortest_path = Integer.MAX_VALUE;
            Graph_nodes[i].parent_Node=null;
        }
        Graph_nodes[source].Bellman_Ford_shortest_path=0;

        //will create the list of edges (u,v)
        Making_Edge_List();

        for (int i=1;i<=num_of_nodes;i++) //because here total nodes = num_of_nodes +1
        {
            for (BF_Edge edge : edge_list)
            {
                Node u = edge.u;
                Node v = edge.v;
                if(u.Bellman_Ford_shortest_path + edge.weight < v.Bellman_Ford_shortest_path)
                {
                    v.Bellman_Ford_shortest_path = u.Bellman_Ford_shortest_path + edge.weight;
                    v.parent_Node = u;

                }
            }

        }

        //checking for negative edge cycle
        for (BF_Edge edge : edge_list)
        {
            Node u = edge.u;
            Node v = edge.v;
            if (u.Bellman_Ford_shortest_path + edge.weight < v.Bellman_Ford_shortest_path)
            {
                has_negative_edge_cycle=true;
                return;
            }
        }


    }


    //O(n^2)
    void Reweighting_Edges() //making all the edges to be positive
    {

        //adding new node and 0 weigthted edges adjacent to the new nodes
        int new_temp_node_id=num_of_nodes+1;
        Graph_nodes[new_temp_node_id]=new Node(new_temp_node_id,null);
        for (int i=1;i<=num_of_nodes;i++)
        {
            add_Nodes(new_temp_node_id,i,0);
        }

        Bellman_Ford_Shortest_Path(new_temp_node_id);

        if(has_negative_edge_cycle == true)
        {
            return;
        }

        //Reweighting
        for (int i=1;i<=num_of_nodes;i++)
        {
            for (int j=1;j<=num_of_nodes;j++)
            {
                new_weights[i][j] = weights[i][j] + Graph_nodes[i].Bellman_Ford_shortest_path - Graph_nodes[j].Bellman_Ford_shortest_path;
            }
        }


    }

    //O(VElogV + V^2)
    void Johnson_All_pair_Shortest_Path()
    {
        Reweighting_Edges(); //O(V^2)

        if(has_negative_edge_cycle == true)
        {
            System.out.println("The graph has negative weighted cycle");
            return;
        }

        //Now all edges are positive
        for (int i=1;i<=num_of_nodes;i++) //O(VElogV)
        {
            Dijkstra_Shortest_Path(i); //O(ElogV)
            for (int j=1;j<=num_of_nodes;j++)
            {
                distance_matrix[i][j] = Graph_nodes[j].dijkstra_shortest_path +
                                        Graph_nodes[j].Bellman_Ford_shortest_path -
                                        Graph_nodes[i].Bellman_Ford_shortest_path;
            }
            reset_all_nodes();
        }

        System.out.println("Shortest Distance Matrix:");
        System.out.println();

        for (int r=1;r<=num_of_nodes;r++)
        {
            for (int c=1;c<=num_of_nodes;c++)
            {
                System.out.print(distance_matrix[r][c]+" ");
            }
            System.out.println();
        }


    }






    //will show the adjacency list of the graph
//    void show_Graph_AdjacencyList()
//    {
//        for (int i=0;i<num_of_nodes;i++)
//        {
//            System.out.print(Graph_nodes[i].get_id_No()+": ");
//            Adjacency_Node current_node = Graph_nodes[i].next;
//
//            while(current_node != null)
//            {
//                System.out.print(current_node.get_Adjacent_id_No()+" ");
//                current_node=current_node.next;
//
//            }
//
//            System.out.println();
//        }
//
//    }

    //Floyd Warshall algo
    //O(n^3)
    void FW_ALL_Pair_Shortest_Path()
    {
        for(int k=1;k<=num_of_nodes;k++)
        {
            for (int i=1;i<=num_of_nodes;i++)
            {
                for (int j=1;j<=num_of_nodes;j++)
                {
                    if(i==j)
                    {
                        continue;
                    }
                    else if (i==k || j==k)
                    {
                        continue;
                    }
                    else
                    {
                        if(distance_matrix[i][k] + distance_matrix[k][j]   < distance_matrix[i][j])
                        {
                            distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                        }
                    }
                }
            }

        }

        for (int r=1;r<=num_of_nodes;r++)
        {
            for (int c=1;c<=num_of_nodes;c++)
            {
                System.out.print(distance_matrix[r][c]+" ");
            }
            System.out.println();
        }




    }


    void show_Graph_Adjacency_Matrix()
    {
        for (int r=1;r<=num_of_nodes;r++)
        {
            for (int c=1;c<=num_of_nodes;c++)
            {
                System.out.print(weights[r][c]+" ");
            }
            System.out.println();
        }
    }

    void reset_all_nodes()
    {
        for (int i=1;i<=num_of_nodes;i++)
        {
            Graph_nodes[i].color = 'W';
            Graph_nodes[i].parent_Node = null;
        }
    }


    void reset_the_whole_graph()
    {

        for (int i=1;i<=num_of_nodes;i++)
        {
            Graph_nodes[i].color ='W';
            Graph_nodes[i].parent_Node=null;
            Graph_nodes[i].dijkstra_shortest_path=0;
            Graph_nodes[i].Bellman_Ford_shortest_path=0;


        }
        edge_list=new ArrayList<BF_Edge>();

        for (int i=1;i<=num_of_nodes;i++)
        {
            for (int j=1;j<=num_of_nodes;j++)
            {
                distance_matrix[i][j] = weights[i][j];
            }
        }



    }



}





