package MST;

//this is a zero based heap
public class Min_Priority_Queue {

    Graph.Node[] nodes;
    int heap_length;

    Min_Priority_Queue(Graph.Node[] nodes)
    {
        this.nodes=nodes;
        heap_length=nodes.length;

        for(int i=0;i<nodes.length;i++)
        {
            nodes[i].priority_queue_node_index=i;
        }

    }

    int left(int i)
    {
        return 2*i+1;
    }

    int right(int i)
    {
        return 2*i+2;
    }
    int parent(int i)
    {
        return (i-1)/2;
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

        if( l < heap_length && nodes[l].key < nodes[index].key )
        {
            smallest = l;
        }
        else
        {
            smallest = index;
        }

        if(r < heap_length && nodes[r].key < nodes[smallest].key)
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

        if(parent_index >= 0  && nodes[index].key < nodes[parent_index].key)
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

        if(l < heap_length && nodes[index].key > nodes[l].key)
        {
            Min_Heapify(index); //bubble down
        }

        if(r < heap_length && nodes[index].key > nodes[r].key)
        {
            Min_Heapify(index);//bubble down
        }

        if(p >= 0 && nodes[index].key < nodes[p].key )
        {
            insert_heapify(index);//bubble up
        }

    }

    Graph.Node Extract_Min()
    {
        //swaping the largest node(root node) with the last node of the heap..(node = element of the array)
        Graph.Node temp;
        temp=nodes[0];

        nodes[0] = nodes[heap_length-1];
        nodes[0].priority_queue_node_index=0;

        nodes[heap_length-1] = temp;
        nodes[heap_length-1].priority_queue_node_index=heap_length-1;

        heap_length--;


        //making the heap into min heap
        Min_Heapify(0);
        return temp;



    }

    void build_Min_heap()
    {
        for(int i=(heap_length/2)-1;i>=0;i--)
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
