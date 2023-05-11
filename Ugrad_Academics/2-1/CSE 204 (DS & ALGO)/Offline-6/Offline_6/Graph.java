package Offline_6;

public class Graph {

    Node[] Graph_nodes; //Array for the adjacency list
    int[] Friends;
    int Total_Collected_pieces;
    int Total_Pieces_Exisits;


    Graph(int number_of_nodes, int number_of_friends) {
        Total_Collected_pieces = 0;
        Total_Pieces_Exisits=0;
        //initializing the the array of nodes for adjacency list
        Graph_nodes = new Node[number_of_nodes];

        for (int i = 0; i < number_of_nodes; i++) {
            Graph_nodes[i] = new Node(i, null);
        }

        //the index of this array represents the "ID no" of each friend
        //the value in particular index represents the number of "collected pieces" by that friend
        //initially all the value of this array is "0";
        Friends = new int[number_of_friends];

        for (int i = 0; i < number_of_friends; i++) {
            Friends[i] = 0;
        }


    }



    class Node {
        int city_No;
        Adjacency_Node next;
        int number_of_pieces_exists;  // the number of pieces on this city
        Boolean is_Visited;  //the city is visited or not;


        Node(int city_no, Adjacency_Node n) {
            city_No = city_no;
            next = n;
            number_of_pieces_exists = 0;
            is_Visited = false;
        }

        void setNumber_of_pieces_exists(int n) {
            number_of_pieces_exists = n;
            //Counting the total pieces exists in Mamaland
            Total_Pieces_Exisits = Total_Pieces_Exisits + number_of_pieces_exists;
        }

        int getNumber_of_pieces_exists() {
            return number_of_pieces_exists;
        }

        int getCity_No() {
            return city_No;
        }
    }

    class Adjacency_Node {
        int adjacent_city_No;
        Adjacency_Node next;

        Adjacency_Node(int city_no, Adjacency_Node n) {
            adjacent_city_No = city_no;
            next = n;
        }

        int getAdjacent_city_No() {
            return adjacent_city_No;
        }

    }


    //this function will be called each time when there is a road between two cities(edge between "city_no" and "adjacent_city_no")
    //that means this function will build the adjacency list of the graph

    void add_Nodes(int city_no, int adjacent_city_no) {
        Adjacency_Node new_adjacency_node = new Adjacency_Node(adjacent_city_no, null);

        //if the city_node has not any adjacency node
        if (Graph_nodes[city_no].next == null) {
            Graph_nodes[city_no].next = new_adjacency_node;
        }

        //if the city_node has one or more than one adjacency node

        else {
            Adjacency_Node Current_Node = Graph_nodes[city_no].next;

            while (Current_Node.next != null) {
                Current_Node = Current_Node.next;
            }

            Current_Node.next = new_adjacency_node;

        }


    }

    //this function set the number_of_pieces at the given location
    void set_Number_of_pieces_In_Location(int city_no, int num_of_pieces) {
        Graph_nodes[city_no].setNumber_of_pieces_exists(num_of_pieces);
    }


    // "friend_id" no friend will start from "starting node of the graph"
    void BFS_travarse(int starting_node_index, int friend_id)
    {
        //this is our starting node from where "friend id" will start traversing
        Node starting_Node = Graph_nodes[starting_node_index];

        CustomQueue<Node> BFS_queue = new CustomQueue<>();

        //At first no matter what the starting node will be enqueued
        BFS_queue.enqueue(starting_Node);

        starting_Node.is_Visited = true;  //making a node visited while enqueuing
        //collecting the existing node whenever visiting a node(city)
        Friends[friend_id] = Friends[friend_id] + starting_Node.getNumber_of_pieces_exists();

        //counting the total collected pieces
        Total_Collected_pieces = Total_Collected_pieces +starting_Node.getNumber_of_pieces_exists();


        // after collecting the pieces at the current location,now that location have no hidden pieces
        starting_Node.setNumber_of_pieces_exists(0);


        //Running time of this nested loop = 2*n ( n= total number of nodes)
        while (!BFS_queue.isEmpty())
        {
            Node popped_node=null;
            try {
                popped_node = BFS_queue.dequeue();
            }catch (Exception e)
            {
                e.printStackTrace();
            }

            Adjacency_Node Current_node = popped_node.next;

            //while enqueuing a node in the queue, it should be checked that
            //the node is previously visited or not..if visited,then don,t enqueue it,otherwise enqueue the node
            //a node is enqueued means the node is visited...So mark the node "visited"...
            // Then, i should check whether there are pieces exists or not at that node(location)
            //if pieces exists, then the "friend id" will collect all of it and then that location will have no pieces

            while (Current_node != null)
            {
                if (!Graph_nodes[Current_node.getAdjacent_city_No()].is_Visited) {
                    BFS_queue.enqueue(Graph_nodes[Current_node.getAdjacent_city_No()]);
                    Graph_nodes[Current_node.getAdjacent_city_No()].is_Visited = true;
                    Friends[friend_id] = Friends[friend_id] + Graph_nodes[Current_node.getAdjacent_city_No()].getNumber_of_pieces_exists();
                    //counting the total collected pieces
                    Total_Collected_pieces = Total_Collected_pieces + Graph_nodes[Current_node.getAdjacent_city_No()].getNumber_of_pieces_exists();
                    // after collecting the pieces at the current location,now that location have no hidden pieces
                    Graph_nodes[Current_node.getAdjacent_city_No()].setNumber_of_pieces_exists(0);

                    Current_node = Current_node.next;

                } else {
                    Current_node = Current_node.next;
                }
            }


        }
    }


    void DFS_travarse(int starting_node_index, int friend_id)
    {
        Node starting_Node = Graph_nodes[starting_node_index];

        if(!starting_Node.is_Visited)
        {
            starting_Node.is_Visited = true;
            //collecting the existing node whenever visiting a node(city)
            Friends[friend_id] = Friends[friend_id] + starting_Node.getNumber_of_pieces_exists();

            //counting the total collected pieces
            Total_Collected_pieces = Total_Collected_pieces + starting_Node.getNumber_of_pieces_exists();

            // after collecting the pieces at the current location,now that location have no hidden pieces
            starting_Node.setNumber_of_pieces_exists(0);
        }

        Adjacency_Node Current_Node=starting_Node.next;

        while(Current_Node !=null )
        {
            if(Graph_nodes[Current_Node.getAdjacent_city_No()].is_Visited)
            {
                Current_Node = Current_Node.next;
            }

            else {
                DFS_travarse(Current_Node.getAdjacent_city_No(), friend_id);
                Current_Node = Current_Node.next;
            }
        }

    }



    void Print_Friend_Info()
    {
        for (int i=0;i< Friends.length ;i++)
        {
            System.out.println(i+" collecetd "+Friends[i]+" pieces");
        }
    }

    //return total collected pieces by all friends
    int getTotal_Collected_pieces() {

        return Total_Collected_pieces;
    }

    //return total pieces exists in Mamaland
    int getTotal_Pieces_Exisits()
    {
        return Total_Pieces_Exisits;
    }


    //after 1 friend visiting all the adjacent node,the visiting info of each node should be reset
    //so that the next friend can visit all the nodes independently

    void Reset_Visiting_Info()
    {
        for(int i=0;i<Graph_nodes.length ;i++)
        {
            Graph_nodes[i].is_Visited=false;
        }
    }

    int[] getFriends()
    {
        return Friends;
    }



}
