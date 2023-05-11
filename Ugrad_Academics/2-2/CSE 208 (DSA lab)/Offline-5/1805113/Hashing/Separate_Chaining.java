import java.util.LinkedList;

public class Separate_Chaining {

    Doubly_Linked_list[] hash_table;
    int num_of_collision; //during inserting
    int num_of_probe; //during searching
    int Total_items;
    int table_size;



    Separate_Chaining(int N)
    {
        Total_items=N;
        table_size=2*N;
        hash_table=new Doubly_Linked_list[table_size];
        num_of_collision=0;
        num_of_probe=0;
    }



    class LL_Node
    {
        Item item;
        LL_Node next;
        LL_Node previous;

        public LL_Node(Item item, LL_Node next,LL_Node previous) {
            this.item = item;
            this.next = next;
            this.previous=null;
        }

        public Item getItem() {
            return item;
        }

        public LL_Node getNext() {
            return next;
        }

        public LL_Node getPrevious() {
            return previous;
        }
    }


    class Doubly_Linked_list
    {
        LL_Node head;
        LL_Node tail;
        public Doubly_Linked_list()
        {
            head=null;
            tail=null;
        }

        public LL_Node getHead() {
            return head;
        }

        public LL_Node getTail() {
            return tail;
        }
    }


    //same string 2 bar insert korle ki hobe?
    void insert_Item(String key)
    {
       int hash_value=Hash_1(key);
        //int hash_value=Hash_2(key);

        Item new_item=new Item(key,hash_value);

        LL_Node new_LL_node=new LL_Node(new_item,null,null);

        //there is no chain at that index
        if(hash_table[hash_value] == null)
        {
            hash_table[hash_value]=new Doubly_Linked_list();
            hash_table[hash_value].head = new_LL_node;
            hash_table[hash_value].tail = new_LL_node;

            //System.out.println("Inserting "+new_LL_node.getItem());
        }

        //there is a chain at that index
        else
        {
            //LL_Node current_linked_list_head=hash_table[hash_value].head;
            //LL_Node current_linked_list_tail=hash_table[hash_value].tail;

            hash_table[hash_value].tail.next=new_LL_node;
            new_LL_node.previous=hash_table[hash_value].tail;
            hash_table[hash_value].tail=new_LL_node;
            num_of_collision++;


        }


    }



    //jake search korchi,take jodi insert e na kora hoy tahole 2 ta case hoite pare
    //1) kono 1 chain er shesh prjnto traverse korbe(Unsuccessful search)
    // [ ekhetre num_of_probe = oi chain er length]
    //2) amon akta hash value return holo j index a kono item akhono insert hoy nai
    // [ ekhetre num_of_probe = 0]

    Item search_item(String key)
    {
        int hash_value=Hash_1(key);
        //int hash_value = Hash_2(key);


        Doubly_Linked_list current_linked_list=hash_table[hash_value];

        if (current_linked_list!=null)
        {
            num_of_probe++;
            LL_Node current_node=hash_table[hash_value].head;

            while (current_node!=null)
            {

                if (current_node.getItem().getKey().equals(key)) {
                    return current_node.getItem();
                }

                current_node = current_node.next;
            }
        }

        //will return null if such "key" string is not found
        return null;


    }


    Item Delete_item(String key)
    {
        //int hash_value=Hash_1(key);
        int hash_value = Hash_2(key);


        Doubly_Linked_list current_linked_list=hash_table[hash_value];

        if (current_linked_list!=null)
        {
            //LL_Node current_linked_list_head=hash_table[hash_value].head;
            //LL_Node current_linked_list_tail=hash_table[hash_value].head;

            LL_Node current_node=hash_table[hash_value].head;


            while (current_node!=null)
            {
               // num_of_probe++;
                if (current_node.getItem().getKey().equals(key)) {

                    //deleting the value
                    if(hash_table[hash_value].head == hash_table[hash_value].tail)
                    {
                        hash_table[hash_value]=null;
                    }

                    else if(current_node==hash_table[hash_value].tail)
                    {
                        current_node.previous.next=null;
                        hash_table[hash_value].tail=current_node.previous;

                    }

                    else if(current_node==hash_table[hash_value].head)
                    {
                        hash_table[hash_value].head=current_node.next;
                        current_node.next.previous=null;

                    }

                    else
                    {
                        current_node.previous.next=current_node.next;
                        current_node.next.previous=current_node.previous;
                    }

                    return current_node.getItem() ;


                }

                current_node = current_node.next;
            }
        }

        //will return null if such "key" string is not found
        return null;


    }




    //Hash function a obosshoi "ever string has it's own hash value"
    //i.e. same string er jonno hash_value o same hote hobe ( same string er jonno hash_value different hote parbe na  )
    //1st hash function
    int Hash_1(String key)
    {
        int value=0;
        for(int i=0;i<key.length();i++)
        {
            value= value + (i+1)*437*(int)key.charAt(i);
        }
        return value % (table_size);

    }


    //2nd hash function
    int Hash_2(String key)
    {

        int value=key.length();
        for(int i=0;i<key.length();i++)
        {
            value = value*17 + (int)key.charAt(i) ;
        }
        return value % (table_size);


    }


    void print_items()
    {
        for (int i=0;i<2*Total_items;i++)
        {
           if(hash_table[i]!=null)
           {
               LL_Node current_node=hash_table[i].head;
               while (current_node !=null)
               {
                   System.out.print(current_node.getItem()+" ");
                   current_node=current_node.next;
               }

           }
            System.out.println();
        }
    }






}
