import java.io.File;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main_Class {

    public static void main(String[] args) {


        AVL_Tree avl_tree = new AVL_Tree();

        try {

            File file = new File("input.txt");

            Scanner input = new Scanner(file);

            char operation = 'i';
            int item = -1;

            while (true) {
                operation = input.next().charAt(0);

                //Press E to "End"

                item = input.nextInt();

                //Inserting
                if (operation == 'I') {
                    avl_tree.insertItem(item);
                    avl_tree.printPreOrder(avl_tree.getRoot());
                    System.out.println();

                }

                //Deleting
                if (operation == 'D')
                {
                    avl_tree.deleteItem(item);
                    avl_tree.printPreOrder(avl_tree.getRoot());
                    System.out.println();
                }

                //Finding
                if (operation == 'F') {

                    System.out.println(avl_tree.Find_Item(item));
                }


            }
        }catch (Exception e)
        {
            if(e instanceof NoSuchElementException)
            {
                System.out.println("End");
            }
        }


        }



}
