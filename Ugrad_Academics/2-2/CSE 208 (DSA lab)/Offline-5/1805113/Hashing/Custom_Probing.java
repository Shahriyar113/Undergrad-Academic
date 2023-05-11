public class Custom_Probing {
    Item[] hash_table;
    int num_of_collision; //during inserting
    int num_of_probe; //during searching
    int Total_items;
    int table_size;


    Custom_Probing(int N)
    {
        Total_items=N;
        table_size=2*N;
        hash_table=new Item[table_size];
        num_of_collision=0;
        num_of_probe=0;


    }

    //1st hash function
    int Hash_1(String key)
    {
        int value=0;
        for(int i=0;i<key.length();i++)
        {
            value= value + (i+1)*483*(int)key.charAt(i);
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

    int auxHash(String key)
    {
        int value = ((int)key.charAt(4)+(int)key.charAt(5))/8;

        return value;
    }


    int Double_Hash(String key,int i)
    {
        int C1=2 ,C2=Total_items/3;
        int value = (Hash_1(key) + C1*i*auxHash(key)+C2*i*i) % (2*Total_items);
        //int value = (Hash_2(key) + C1*i*auxHash(key)+C2*i*i) % (table_size);

        return value;
    }






    void insert_item(String key)
    {
        int probe_no=0;



        while(hash_table[Double_Hash(key,probe_no)]!=null)
        {
            //if duplicate string is inserted
            if(hash_table[Double_Hash(key,probe_no)].getKey().equals(key))
            {
                return;
            }
            probe_no++;
            //System.out.println(Double_Hash(key,probe_no));
        }

        int new_index=Double_Hash(key,probe_no);

        Item new_item=new Item(key,new_index);

        hash_table[new_index] = new_item;

        //ultimately probe_no a current "key" insert er jonno koyta collision holo ta store thake
        num_of_collision=num_of_collision + probe_no;





//        int hash_value = Hash_1(key);
//
//        Item new_item=new Item(key,hash_value);
//        //int hash_value = Hash_2(key);
//
//        //if there is no collision for adding "key"
//        if(hash_table[hash_value]==null)
//        {
//            hash_table[hash_value]=new_item;
//        }
//
//        //there is a collision for adding "key"
//        else
//        {
//            num_of_collision++;
//
//            //probing




    }



    Item search_item(String key)
    {
        int probe_no=0;

        while(hash_table[Double_Hash(key,probe_no)]!=null)
        {
            //if duplicate string is inserted
            if(hash_table[Double_Hash(key,probe_no)].getKey().equals(key))
            {
                num_of_probe=num_of_probe + probe_no;

                return (hash_table[Double_Hash(key,probe_no)]);
            }
            probe_no++;
        }

        //ultimately probe_no a current "key" insert er jonno koyta collision holo ta store thake

        num_of_probe=num_of_probe + probe_no;
        return null;



    }


    void Delete_item(String key)
    {
        int probe_no=0;

        while(hash_table[Double_Hash(key,probe_no)]!=null)
        {
            //if duplicate string is inserted
            if(hash_table[Double_Hash(key,probe_no)].getKey().equals(key))
            {
                num_of_probe=num_of_probe + probe_no;

                hash_table[Double_Hash(key,probe_no)]=null;
                return;
            }
            probe_no++;
        }

        //ultimately probe_no a current "key" insert er jonno koyta collision holo ta store thake

        num_of_probe=num_of_probe + probe_no;




    }


    void print_items()
    {
        for(int i=0;i<2*Total_items;i++)
        {
            System.out.println(hash_table[i]);
        }

    }


}


