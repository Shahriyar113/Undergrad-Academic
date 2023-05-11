package All_Pairs;

//this is a 1 based heap
public class Min_Priority_Queue {

    Graph.Node[] nodes;
    int heap_length;

    Min_Priority_Queue(Graph.Node[] nodes, int length)
    {
        this.nodes=new Graph.Node[nodes.length];
        heap_length=length;

        for(int i=1;i<=length;i++)
        {
            this.nodes[i]=nodes[i];
        }

        for(int i=1;i<=length;i++)
        {
            this.nodes[i].priority_queue_node_index=i;
        }

    }

    int left(int i)
    {
        return 2*i;
    }

    int right(int i)
    {
        return 2*i+1;
    }
    int parent(int i)
    {
        return i/2;
    }

    public Graph.Node[] get_nodes()
    {
        return nodes;
    }

    public int getHeap_length()
    {
        return heap_length;
    }

    void Min_Heapify(int index)
    {
        int l,r,smallest;
        Graph.Node temp;

        l=left(index);
        r=right(index);

        if( l <= heap_length && nodes[l].dijkstra_shortest_path < nodes[index].dijkstra_shortest_path )
        {
            smallest = l;
        }
        else
        {
            smallest = index;
        }

        if(r <= heap_length && nodes[r].dijkstra_shortest_path < nodes[smallest].dijkstra_shortest_path)
        {
            smallest = r;
        }

        if(smallest != index)
        {
            temp = nodes[index];

            nodes[index] = nodes[smallest];
            nodes[index].priority_queue_node_index=index;


            nodes[smallest] = temp;
            nodes[smallest].priority_queue_node_index=smallest;


            Min_Heapify(smallest);
        }


    }



    void insert_heapify(int index)
    {

        int parent_index= parent(index);
        Graph.Node temp;

        if(parent_index >= 1  && nodes[index].dijkstra_shortest_path < nodes[parent_index].dijkstra_shortest_path)
        {
            temp = nodes[index];

            nodes[index] = nodes[parent_index];
            nodes[index].priority_queue_node_index=index;

            nodes[parent_index] = temp;
            nodes[parent_index].priority_queue_node_index=parent_index;

            insert_heapify(parent_index);

        }


    }



    //when arbitrary node.key is changed,this function will made the nodes a priority queue again

    void Min_heapify_dynamic(int index)
    {
        int l=left(index);
        int r=right(index);
        int p=parent(index);

        if(l <= heap_length && nodes[index].dijkstra_shortest_path > nodes[l].dijkstra_shortest_path)
        {
            Min_Heapify(index); //bubble down
        }

        if(r <= heap_length && nodes[index].dijkstra_shortest_path > nodes[r].dijkstra_shortest_path)
        {
            Min_Heapify(index);//bubble down
        }

        if(p >= 1 && nodes[index].dijkstra_shortest_path < nodes[p].dijkstra_shortest_path )
        {
            insert_heapify(index);//bubble up
        }

    }

    Graph.Node Extract_Min()
    {
        //swaping the largest node(root node) with the last node of the heap..(node = element of the array)
        Graph.Node temp;
        temp=nodes[1];

        nodes[1] = nodes[heap_length];
        nodes[1].priority_queue_node_index=1;

        nodes[heap_length] = temp;
        nodes[heap_length].priority_queue_node_index=heap_length;

        heap_length--;


        //making the heap into min heap
        Min_Heapify(1);
        return temp;



    }

    void build_Min_heap()
    {
        for(int i=(heap_length/2);i>=1;i--)
        {
            Min_Heapify(i);
        }
    }

    boolean isEmpty()
    {
        if (heap_length==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }




}
