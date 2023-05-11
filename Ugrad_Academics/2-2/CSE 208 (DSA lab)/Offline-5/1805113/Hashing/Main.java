import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

//        File file=new File("Input.txt");
//        Scanner input = new Scanner(file);

        //Random string Generator
        Scanner input=new Scanner(System.in);
        System.out.print("Enter the number of string: ");
        int N = input.nextInt();

        String Characters="abcdefghijklmnopqrstwxyz";
        String random_string="";
        List<String> searched_strings=new ArrayList<>();
        int length=7;
        int total_num_of_generating_string=N;

        Separate_Chaining separate_chaining=new Separate_Chaining(N);
        Double_Hashing double_hashing=new Double_Hashing(N);
        Custom_Probing custom_probing=new Custom_Probing(N);

        Random random=new Random();

        for(int i=0;i<total_num_of_generating_string;i++)
        {
            for(int j=0;j<length;j++)
            {
                random_string = random_string + Characters.charAt(random.nextInt(Characters.length()));
            }
             //System.out.println(random_string+" "+custom_probing.Double_Hash(random_string,0));
            //System.out.println(random_string);
            //inserting

            separate_chaining.insert_Item(random_string);
            double_hashing.insert_item(random_string);
            custom_probing.insert_item(random_string);

            //search korar jonno generated 1000 string
            if(i>=1000 && i<2000)
            {
                searched_strings.add(random_string);
            }


            random_string="";
        }

        for (int i=0;i<searched_strings.size();i++)
        {
           separate_chaining.search_item(searched_strings.get(i));
           double_hashing.search_item(searched_strings.get(i));
           custom_probing.search_item(searched_strings.get(i));

        }




        System.out.println("total_colision at sp:" +separate_chaining.num_of_collision);
        System.out.println("Avg probe at sp: "+separate_chaining.num_of_probe/1000.0);
        System.out.println();

        System.out.println("total_colision at dh:" +double_hashing.num_of_collision);
        System.out.println("Avg probe at dh: "+double_hashing.num_of_probe/1000.0);
        System.out.println();

        System.out.println("total_colision at cp:" +custom_probing.num_of_collision);
        System.out.println("Avg probe at cp: "+custom_probing.num_of_probe/1000.0);







//        String[] strings={"ancient","puzzled","benefit", "ancient","zigzags"};
//
//        Separate_Chaining sp=new Separate_Chaining(5);
//
//        for(int i=0;i<strings.length;i++)
//        {
//            System.out.println(strings[i]+" "+sp.Hash_2(strings[i]));
//        }
//
//
//
//
//        for(int i=0;i<strings.length;i++)
//        {
//            sp.insert_Item(strings[i]);
//        }
//
//        //sp.print_items();
//        for(int i=0;i<strings.length;i++)
//        {
//            System.out.println(sp.search_item(strings[i]));
//        }
//





    }

}
