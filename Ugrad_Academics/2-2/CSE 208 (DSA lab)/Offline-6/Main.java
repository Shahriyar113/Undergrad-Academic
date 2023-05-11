import java.io.File;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        try {
            File file = new File("input.txt");
            Scanner input = new Scanner(file);

            Heap main_heap = new Heap(0);

            while (true) {
                if(!input.hasNext())
                {
                    break;
                }

                String input_type = input.next();


                if (input_type.equals("INS"))
                {
                    int value = input.nextInt();
                    main_heap=main_heap.Insert(value);
                   // System.out.println("size" +main_heap.heap_size);

                }
                if (input_type.equals("PRI")) {

                    main_heap.print_heap();

                }
                if (input_type.equals("FIN")) {

                    System.out.println("FindMax returned "+main_heap.FindMax().getValue());

                }
                if (input_type.equals("INC")) {

                    int prevKey =input.nextInt();
                    int newKey=input.nextInt();

                    main_heap.Increase_Key(prevKey,newKey);


                }

                if (input_type.equals("EXT")) {

                    System.out.println("ExtractMax returned "+main_heap.Extract_Max().getValue());


                }

            }
        }catch (Exception e)
        {
            e.printStackTrace();
        }




    }


}
