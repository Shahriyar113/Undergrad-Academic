package SS;

import java.util.ArrayList;
import java.util.LinkedList;

class Graph {
    Node[] Graph_nodes; //Array of nodes for maintaing the priority queue
    int num_of_nodes,num_of_edges;
    double[][] weights; //basically this is the adjacency matrix of the graph
    ArrayList<BF_Edge> edge_list;


    Graph(int num_of_nodes,int num_of_edges) {

        //initializing the the array of nodes for adjacency list
        this.num_of_nodes=num_of_nodes;
        this.num_of_edges=num_of_edges;

        Graph_nodes = new Node[num_of_nodes];

        for (int i = 0; i < num_of_nodes; i++) {
            Graph_nodes[i] = new Node(i, null);
        }

        weights = new double[num_of_nodes][num_of_nodes];
        edge_list=new ArrayList<BF_Edge>();


    }



    class Node {
        int id_No;
        Adjacency_Node next;
        char color; //when a node will extract from priority queue,the node will be "Black colored"
                   //A node is "White Colored" means the node is still in the priority queue;
        Node parent_Node;

        //shortest_path ==> Shortest path cost from source to this node
        double shortest_path; // parameter of priority queue
                //also represents the minimum weight conncted with the corresponded key

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


        weights[id_No][adjacent_id_no]=w;

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
                System.out.print(current_node.get_Adjacent_id_No()+" ");
                current_node=current_node.next;

            }

            System.out.println();
        }

    }


    void show_Graph_Adjacency_Matrix()
    {
        for (int r=0;r<num_of_nodes;r++)
        {
            for (int c=0;c<num_of_nodes;c++)
            {
                System.out.print(weights[r][c]+" ");
            }
            System.out.println();
        }
    }

    void reset()
    {

        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].color ='W';
            Graph_nodes[i].parent_Node=null;
            Graph_nodes[i].shortest_path=0;

        }
        edge_list=new ArrayList<BF_Edge>();

    }


    //Complexity ==> O(ElogV)
    void Dijkstra_Shortest_Path(int source,int destination)
    {
        Node source_node=Graph_nodes[source];
        Node destination_node=Graph_nodes[destination];

        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].shortest_path = Integer.MAX_VALUE;
            Graph_nodes[i].parent_Node=null;
        }

        Graph_nodes[source].shortest_path=0;


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
                        u.shortest_path + v.getWeight() < v.getCorresponding_node().shortest_path)
                {
                   v.getCorresponding_node().parent_Node=u;
                   v.getCorresponding_node().shortest_path =  u.shortest_path + v.getWeight();

                   //priority queue index== node ta pririty queue er kon index a ase sheita
                    min_pq.Min_heapify_dynamic(v.getCorresponding_node().priority_queue_node_index);  //cost ==>O(Elogv) //(considering both the while loop)

                }

                v = v.next;
            }

            //when a node is extracted means it's shortest path from source is finally updated;
            //No more change will happen

//            if(u.get_id_No() == destination)
//            {
//                break;
//            }



        }

        double source_to_des_Cost = Graph_nodes[destination].shortest_path;

        //finding the path from source to destination
        //back_tracking from destination to source via "parent_Node"

        LinkedList<Integer> path_list = new LinkedList<>();

        Node current_node = Graph_nodes[destination];

        while(current_node != Graph_nodes[source])
        {

            path_list.addFirst(current_node.get_id_No());
            current_node = current_node.parent_Node;
        }

        path_list.addFirst(Graph_nodes[source].get_id_No());


        System.out.println("Dijkstra Shortest path: "+source_to_des_Cost);
        System.out.println("The shortest path is: ");
        System.out.println(path_list);



    }


    void Making_Edge_List()
    {
        for (int i=0;i<num_of_nodes;i++)
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


    void Bellman_Ford_Shortest_Path(int source,int destination)
    {
        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].shortest_path = Integer.MAX_VALUE;
            Graph_nodes[i].parent_Node=null;
        }
        Graph_nodes[source].shortest_path=0;

        //will create the list of edges (u,v)
        Making_Edge_List();
        int update_count=0;

        for (int i=1;i<=num_of_nodes-1;i++)
        {
            for (BF_Edge edge : edge_list)
            {
                Node u = edge.u;
                Node v =edge.v;
                if(u.shortest_path + edge.weight < v.shortest_path)
                {
                    update_count++;
                    v.shortest_path = u.shortest_path + edge.weight;
                    v.parent_Node = u;

                }
            }
            if(update_count==0) // |V|-1 shonkhok bar iterate korar agei jodi update howa off hoye jay
            {
                break;
            }
            update_count=0;

        }

        //checking for negative edge cycle
        for (BF_Edge edge : edge_list)
        {
            Node u = edge.u;
            Node v = edge.v;
            if (u.shortest_path + edge.weight < v.shortest_path)
            {
                System.out.println("The graph contains a negative cycle");
                return;
            }
        }

        //if there is no negative edge cycle,then show the necessary info

        double source_to_des_Cost = Graph_nodes[destination].shortest_path;

        //finding the path from source to destination
        //back_tracking from destination to source via "parent_Node"

        LinkedList<Integer> path_list = new LinkedList<>();

        Node current_node = Graph_nodes[destination];

        while(current_node != Graph_nodes[source])
        {

            path_list.addFirst(current_node.get_id_No());
            current_node = current_node.parent_Node;
        }

        path_list.addFirst(Graph_nodes[source].get_id_No());


        System.out.println("The graph does not contains a negative cycle");
        System.out.println("Bellman Ford Shortest path: "+source_to_des_Cost);
        System.out.println("The shortest path is: ");
        System.out.println(path_list);


    }



}





