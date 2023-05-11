package MST;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Graph {
    Node[] Graph_nodes; //Array of nodes for maintaing the priority queue
    int time=0;
    int num_of_nodes;
    double[][] weights; //basically this is the adjacency matrix of the graph
    ArrayList<MST_Edge> mst_edges;


    Graph(int number_of_nodes) {

        //initializing the the array of nodes for adjacency list
        num_of_nodes=number_of_nodes;
        Graph_nodes = new Node[number_of_nodes];

        for (int i = 0; i < number_of_nodes; i++) {
            Graph_nodes[i] = new Node(i, null);
        }

        weights = new double[num_of_nodes][num_of_nodes];
        mst_edges=new ArrayList<MST_Edge>();


    }



    class Node {
        int id_No;
        Adjacency_Node next;
        char color; //when a node will extract from priority queue,the node will be "Black colored"
                   //A node is "White Colored" means the node is still in the priority queue;
        Node parent_Node;
        int finishing_time=0;
        double key;// parameter of priority queue
                //also represents the minimum weight conncted with the corresponded key

        int priority_queue_node_index;


        Node(int city_no, Adjacency_Node n) {
            id_No = city_no;
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

        Adjacency_Node(int city_no, Adjacency_Node n, Node corresponding_node) {
            adjacent_id_No = city_no;
            next = n;
            Corresponding_node=corresponding_node;
        }

        int get_Adjacent_id_No() {
            return adjacent_id_No;
        }

        Node getCorresponding_node()
        {
            return Corresponding_node;
        }

    }

    class DS_Node //for disjoint set forest
    {
        int id_no;
        DS_Node parent;
        int rank;

        DS_Node(int id)
        {
            id_no=id;
        }

        int get_DS_node_id()
        {
            return id_no;
        }
    }




    void add_Nodes(int id_No, int adjacent_id_no,double w) {

        Adjacency_Node new_adjacency_node = new Adjacency_Node(adjacent_id_no, null,Graph_nodes[adjacent_id_no]);

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
        time=0;

        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].color ='W';
            Graph_nodes[i].parent_Node=null;

        }
    }


    void MST_Prims(int root)
    {
        //assuming "0" is the source node
        for (int i=0;i<num_of_nodes;i++)
        {
            Graph_nodes[i].key = Integer.MAX_VALUE;
            Graph_nodes[i].parent_Node=null;
        }

        Graph_nodes[root].key=0;

        Min_Priority_Queue min_pq = new Min_Priority_Queue(Graph_nodes);

        min_pq.build_Min_heap(); // cost ==> O(V)

        while (!min_pq.isEmpty())
        {
            Node u = min_pq.Extract_Min(); //cost => O(VlogV) (considering the while loop)
            ; //when a node will extract from priority queue,the node will be "Black colored"
            u.color='B';

            Adjacency_Node v=u.next;

            while(v !=null) //O(E)
            {
                if(v.getCorresponding_node().color == 'W' &&
                        weights[u.get_id_No()][v.getCorresponding_node().get_id_No()] < v.getCorresponding_node().key)
                {
                   v.getCorresponding_node().parent_Node=u;
                   v.getCorresponding_node().key =  weights[u.get_id_No()][v.getCorresponding_node().get_id_No()];
                   min_pq.Min_heapify_dynamic(v.getCorresponding_node().priority_queue_node_index);  //cost ==>O(Elogv) //(considering both the while loop)

                }

                v = v.next;
            }



        }


        //storing the MST edges
        for(int i=0;i<num_of_nodes;i++)
        {
            if(Graph_nodes[i].parent_Node!=null)
            {
                int node1=Graph_nodes[i].get_id_No();
                int node2=Graph_nodes[i].parent_Node.get_id_No();
                double weight = weights[Graph_nodes[i].get_id_No()][Graph_nodes[i].parent_Node.get_id_No()];
                mst_edges.add(new MST_Edge(node1,node2,weight));
            }
        }

        double MST_cost=0.0;

        for(MST_Edge x : mst_edges)
        {
            MST_cost = MST_cost + x.weight;
        }

        System.out.println("Cost of the Minimum Spanning tree for prim: "+MST_cost);
        System.out.println();
        System.out.println("List of edges selected by prim: ");

        for(MST_Edge x : mst_edges)
        {
            System.out.println(x);
        }


    }

    //will make set for a single node
    //cost ==> O(1)
    DS_Node Make_Set(int id_no)
    {
        DS_Node ds_node=new DS_Node(id_no);
        ds_node.parent = ds_node;
        ds_node.rank=0;

        return ds_node;
    }

    DS_Node Find_Set(DS_Node x)
    {
        if (x != x.parent)
        {
            x.parent=Find_Set(x.parent); //path compression;
        }
        return x.parent;
    }

    void Link(DS_Node x,DS_Node y)
    {
        if(x.rank > y.rank)
        {
            y.parent=x;
        }

        else
        {
            x.parent=y;
        }

        if(x.rank == y.rank)
        {
            y.rank=y.rank+1;
        }



    }

    void Union(DS_Node x,DS_Node y)
    {
        Link(Find_Set(x),Find_Set(y));
    }





    void Kruskal_MST(List<Edges_And_Weights> list)
    {

        DS_Node[] ds_nodes=new DS_Node[num_of_nodes];

        //making disjoint sets for all the nodes
        for (int i=0;i<num_of_nodes;i++)
        {
            ds_nodes[i]=Make_Set(i);
        }


        //soring the edges
        Kruskal_Sorting r=new Kruskal_Sorting();
        Collections.sort(list,r);

        //for storing the MST edges
        List<MST_Edge> mst_edges=new ArrayList<>();


        for (Edges_And_Weights l : list)
        {
            DS_Node u= ds_nodes[l.node1];
            DS_Node v= ds_nodes[l.node2];

            if(Find_Set(u) != Find_Set(v))
            {
                mst_edges.add(new MST_Edge(l.node1,l.node2,l.weight));
                Union(u,v);
            }
        }


        double MST_cost=0.0;

        for(MST_Edge x : mst_edges)
        {
            MST_cost = MST_cost + x.weight;
        }

        System.out.println("Cost of the Minimum Spanning tree for Kruskal: "+MST_cost);
        System.out.println();
        System.out.println("List of edges selected by Kruskal: ");

        for(MST_Edge x : mst_edges)
        {
            System.out.println(x);
        }


    }

}





