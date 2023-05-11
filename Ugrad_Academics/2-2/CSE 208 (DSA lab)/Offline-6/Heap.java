import java.util.LinkedList;
import java.util.Queue;

public class Heap {
    int heap_size;
    Doubly_Linked_List roots;

    public Heap(int heap_size) {
        this.heap_size = heap_size;
        this.roots = new Doubly_Linked_List(null,null);
    }

    public int getHeap_size() {
        return heap_size;
    }

    public Doubly_Linked_List getRoots() {
        return roots;
    }

    class Doubly_Linked_List
    {
        Tree_Node head;
        Tree_Node tail;

        public Doubly_Linked_List(Tree_Node head, Tree_Node tail) {
            this.head = head;
            this.tail = tail;
        }

        void add(Tree_Node node)
        {
            if(node == null)
            {
                return;
            }

            if(head==null)
            {
                head = node;
                tail=node;
                node.next=null;
                return;
            }
            tail.next=node;
            node.previous = tail;
            tail=node;
            node.next = null;

        }

        public Tree_Node getHead() {
            return head;
        }

        public Tree_Node getTail() {
            return tail;
        }
    }




    class Tree_Node
    {
        int value;
        int degree;
        Tree_Node next;
        Tree_Node previous;
        Tree_Node parent;
        Doubly_Linked_List children;

        public Tree_Node(int value) {
            this.value = value;
            this.degree=0;
            this.next = null;
            this.previous = null;
            this.parent = null;
            this.children = new Doubly_Linked_List(null,null);
        }

        public int getValue() {
            return value;
        }


        public Tree_Node getNext() {
            return next;
        }


        public Tree_Node getPrevious() {
            return previous;
        }


        public Tree_Node getParent() {
            return parent;
        }


        public Doubly_Linked_List getChildren() {
            return children;
        }

        public int getDegree()
        {
            return degree;
        }


    }


    Tree_Node Merging_two_tree(Tree_Node tree_1,Tree_Node tree_2)
    {
        if(tree_1.value > tree_2.value)
        {
            tree_1.children.add(tree_2);
            tree_1.degree++;
            tree_2.parent=tree_1;
            return tree_1;
        }

        else
        {
            tree_2.children.add(tree_1);
            tree_2.degree++;
            tree_1.parent=tree_2;
            return tree_2;
        }

    }


    Heap union(Heap H1,Heap H2)
    {
        Heap new_heap=new Heap(0); //every union operation creates a new heap
        //modification for binary addition
        String H1_binary_string=new String(new StringBuffer(Integer.toBinaryString(H1.heap_size)).reverse());
        String H2_binary_string=new String(new StringBuffer(Integer.toBinaryString(H2.heap_size)).reverse());

        int H1_binary_string_length=H1_binary_string.length();
        int H2_binary_string_length=H2_binary_string.length();

        if(H1_binary_string_length > H2_binary_string_length)
        {
            for (int i=H2_binary_string_length;i<H1_binary_string_length;i++)
            {
                H2_binary_string=new String(new StringBuffer(H2_binary_string).append('0'));
            }
        }

        if(H1_binary_string_length < H2_binary_string_length)
        {
            for (int i=H1_binary_string_length;i<H2_binary_string_length;i++)
            {
                H1_binary_string=new String(new StringBuffer(H1_binary_string).append('0'));
            }
        }

        int binary_addition_length=Integer.max(H1_binary_string_length,H2_binary_string_length);

        Tree_Node temp=null;
        Tree_Node current_H1_root=H1.roots.head;
        Tree_Node current_H2_root=H2.roots.head;

//        if(heap_size>0)
//        {
//            System.out.println(this.roots.head.getValue()+"kub");
//        }

       // System.out.println(current_H2_root.getDegree());


        int carry=0;
        for (int i=0;i<binary_addition_length;i++)
        {



            if(H1_binary_string.charAt(i) =='0' && H2_binary_string.charAt(i)=='1')
            {
                if(carry == 0)
                {

                    Tree_Node next=current_H2_root.next;
                    new_heap.roots.add(current_H2_root);
                    new_heap.heap_size = new_heap.heap_size + (int)Math.pow(2,current_H2_root.getDegree());
                    current_H2_root=next;

                    carry=0;

                }
                else if(carry == 1)
                {
                    temp=Merging_two_tree(temp,current_H2_root);
                    current_H2_root=current_H2_root.next;

                    carry=1;
                }
            }
            if(H1_binary_string.charAt(i) =='1' && H2_binary_string.charAt(i)=='1')
            {
               if(carry == 0)
               {

                   temp = Merging_two_tree(current_H1_root,current_H2_root);
                   current_H1_root=current_H1_root.next;
                   current_H2_root=current_H2_root.next;
                   carry=1;


               }
               else if(carry == 1 )
               {
                   Tree_Node next1=current_H1_root;
                   Tree_Node next2 =current_H2_root;
                   new_heap.roots.add(temp);
                   new_heap.heap_size = new_heap.heap_size + (int)Math.pow(2,temp.getDegree());
                   temp=Merging_two_tree(current_H1_root,current_H2_root);
                   current_H1_root=next1;
                   current_H2_root=next2;

                   carry = 1;
               }
            }
            if(H1_binary_string.charAt(i)=='1' && H2_binary_string.charAt(i)=='0')
            {

                if(carry == 0)
                {
                    Tree_Node next=current_H1_root;
                    new_heap.roots.add(current_H1_root);
                    new_heap.heap_size = new_heap.heap_size + (int)Math.pow(2,current_H1_root.getDegree());
                    current_H1_root=next;

                    carry=0;

                }
                else if(carry == 1 )
                {
                    temp=Merging_two_tree(temp,current_H1_root);
                    current_H1_root=current_H1_root.next;

                    carry = 1;

                }
            }

            if(H1_binary_string.charAt(i)=='0' && H2_binary_string.charAt(i)=='0')
            {
                if(carry == 0)
                {
                    ;//nothing to do

                }
                else if(carry == 1 )
                {
                    new_heap.roots.add(temp);
                    new_heap.heap_size = new_heap.heap_size + (int)Math.pow(2,temp.getDegree());

                    carry =0;

                }
            }

        }

        //adding the remaining temp(carry overflow)

        if(carry == 1)
        {
            new_heap.roots.add(temp);
            new_heap.heap_size = new_heap.heap_size + (int) Math.pow(2, temp.getDegree());
        }

        return new_heap;


    }


    Heap Insert(int value)
    {

        Tree_Node node = new Tree_Node(value);

        //creating a heap of single node
        Heap single_node_heap=new Heap(0);
        single_node_heap.roots.add(node);
        single_node_heap.heap_size++;


        Heap main_heap=union(this,single_node_heap);

        //System.out.println(main_heap.roots.head.getValue());

        System.out.println("Inserted "+node.getValue());

        return main_heap;

    }


    Tree_Node FindMax()
    {
        int MAX = Integer.MIN_VALUE;
        Tree_Node Max_node=null;
        Tree_Node current_root= roots.head;
        while (current_root != null)
        {
            if(current_root.getValue() > MAX)
            {
                MAX = current_root.getValue();
                Max_node = current_root;
                current_root= current_root.next;
            }
        }

        return Max_node;

    }


    void Increase_Key(int prevKey,int newKey)
    {
        Tree_Node target_node=Search(prevKey);

        if(target_node==null)
        {
            System.out.println("key not found");
        }

        target_node.value = newKey;

        //bubble up
        while (target_node.parent !=null && target_node.getValue() > target_node.parent.getValue())
        {
            //swapping
            int temp = target_node.parent.getValue();
            target_node.parent.value = target_node.value;
            target_node.value = temp;

            target_node = target_node.parent;
        }

        System.out.println("Increased "+prevKey+". The updated value is "+newKey);



    }


    Tree_Node Extract_Max()
    {
        //Finding Max node
        int MAX = Integer.MIN_VALUE;
        Tree_Node Max_node=null;
        Tree_Node current_root= roots.head;
        while (current_root != null)
        {
            if(current_root.getValue() > MAX)
            {
                MAX = current_root.getValue();
                Max_node = current_root;
                current_root= current_root.next;
            }
        }

       //if the heap has only one node
        if(Max_node.next == null && Max_node.previous==null)
        {
            roots.head=null;
            roots.tail=null;
        }

            //if max node is the last root node among all the tree
        else if(Max_node.next == null)
        {
            Max_node.previous.next = null;
            roots.tail=Max_node.previous;
        }

        //if max node is the 1st root node among all the tree

        else if(Max_node.previous == null)
        {
            Max_node.next.previous = null;
            roots.head=Max_node.next;
        }

        //if max node is some middle root node among all the tree

        else
        {
            Max_node.previous.next=Max_node.next;
            Max_node.next.previous=Max_node.previous;
        }


        Heap temp_heap = new Heap(0);

        Tree_Node current_child = Max_node.children.head;


        while (current_child!=null)
        {
            Tree_Node temp = current_child.next;
            temp_heap.roots.add(current_child);
            current_child.parent=null;
            current_child = temp;
        }


        temp_heap.heap_size = (int)Math.pow(2,Max_node.getDegree()) - 1;


        Max_node.children = null;
        this.heap_size=heap_size - temp_heap.heap_size -1;

//        System.out.println("1st portion");
//        this.print_heap();
//        System.out.println("2nd portion");
//        temp_heap.print_heap();


        //System.out.println("THENNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
        Heap updated_heap=union(this,temp_heap);
        this.heap_size = updated_heap.heap_size;
        this.roots = updated_heap.roots;



        return Max_node;


    }




    void print_heap()
    {
        String Heap_length_binary_string=new String(new StringBuffer(Integer.toBinaryString(heap_size)).reverse());

        Tree_Node current_root = roots.head;

       // System.out.println(Heap_length_binary_string);

        System.out.println("Printing Binomial Heap...");
        System.out.println("----------------------------");
        System.out.println();

        for (int i=0;i<Heap_length_binary_string.length();i++)
        {

            if(Heap_length_binary_string.charAt(i)=='0')
            {
                continue;
            }
            else
            {
                Queue<Tree_Node> queue=new LinkedList<Tree_Node>();
                System.out.println("Binomial Tree B"+i);
                System.out.println("-------------------");

                int current_tree_order = current_root.getDegree();//current_tree_order = i
//                int current_node_degree=0;
//                Tree_Node current_tree_node=null;
                int count_in_queue=1;
                for (int k=0;k <=current_tree_order ;k++ )
                {
                    if(k==0) //for level 0
                    {
                        System.out.print("Level "+k+" : ");
                        queue.add(current_root);
                        System.out.println(current_root.getValue());
                        continue;
                    }
                    else
                    {
                        //System.out.println();
                        System.out.print("Level "+k+" : ");

                        int p=0;
                        int z=count_in_queue;
                        count_in_queue=0;

                        while (p!=z)
                        {
                            Tree_Node temp = queue.remove();
                            Tree_Node curr=temp.children.head;
                            while (curr != null)
                            {
                                queue.add(curr);
                                System.out.print(curr.getValue()+" ");
                                count_in_queue++;
                                curr = curr.next;

                            }
                            p++;

                        }
                        System.out.println();



                    }

                }
            }

            current_root=current_root.next; //iterating next binomial tree of the heap



        }

        System.out.println("---------------------");
        System.out.println();


    }


    Tree_Node Search(int key)
    {
        String Heap_length_binary_string=new String(new StringBuffer(Integer.toBinaryString(heap_size)).reverse());

        Tree_Node current_root = roots.head;

        // System.out.println(Heap_length_binary_string);


        for (int i=0;i<Heap_length_binary_string.length();i++)
        {

            if(Heap_length_binary_string.charAt(i)=='0')
            {
                continue;
            }
            else
            {
                Queue<Tree_Node> queue=new LinkedList<Tree_Node>();


                int current_tree_order = current_root.getDegree();//current_tree_order = i
//                int current_node_degree=0;
//                Tree_Node current_tree_node=null;
                int count_in_queue=1;
                for (int k=0;k <=current_tree_order ;k++ )
                {
                    if(k==0) //for level 0
                    {
                        queue.add(current_root);
                        if(current_root.getValue() == key)
                        {
                            return current_root;
                        }
                        continue;
                    }
                    else
                    {
                        //System.out.println();

                        int p=0;
                        int z=count_in_queue;
                        count_in_queue=0;

                        while (p!=z)
                        {
                            Tree_Node temp = queue.remove();
                            Tree_Node curr=temp.children.head;
                            while (curr != null)
                            {
                                queue.add(curr);
                                if(curr.getValue() == key)
                                {
                                    return curr;
                                }
                                count_in_queue++;
                                curr = curr.next;

                            }
                            p++;

                        }



                    }

                }


            }

            current_root=current_root.next; //iterating next binomial tree of the heap

        }
        System.out.println(key+" Not found");
        return null;


    }











}
