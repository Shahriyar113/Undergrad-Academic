package Offline4;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        //System.out.println("OK");
        Scanner input=new Scanner(System.in);

        Binary_Search_Tree bst =new Binary_Search_Tree();

        String menu ="1. Insert Item" +"\n"+"2. Search Item" +"\n"+"3. GetInOrderSuccessor" +"\n"+
                "4. GetInOrderPredecessor" +"\n"+"5. Delete Item" +"\n"+"6. GetItemDepth" +"\n"+
                "7. GetMaxItem" +"\n"+"8. GetMinItem" +"\n"+"9. GetHeight" +"\n"+
                "10. PrintInOrder " +"\n"+"11. PrintPreOrder" +"\n"+"12. PrintPostOrder" +"\n"+
                "13. GetSize" +"\n";

        System.out.println("Main Menu");
        System.out.println("----------");
        System.out.println();

        System.out.println(menu);


        while (true)
        {
            System.out.println("Main Menu");
            System.out.println("----------");
            System.out.println();

          //  System.out.println(menu);
            System.out.println();

            System.out.println("Enter a Menu Number:");
            try
            {
                int N=input.nextInt();  //Main menu input

                if(N==1) //inserting input
                {
                    System.out.println("Insert numbers one by one.Enter EXIT to stop and return main menu");
                    System.out.println("---------------------------------------------");
                    System.out.println();

                    while (true)
                    {
                        String inserted_num = input.next();
                        //input.nextLine(); //to remove enter buffer
                        if(inserted_num.equalsIgnoreCase("exit"))
                        {
                            break; //returning to main menu
                        }

                        try {
                           bst.insertItem(Integer.parseInt(inserted_num));
                            System.out.println(inserted_num+" is inserted");
                        }
                        catch (Exception e)
                        {
                            System.out.println("Invalid input inserted.Try again");
                            continue;
                        }

                    }
                }

                else if(N==2)
                {
                    System.out.println("Search a number.Enter EXIT to stop and return main menu");
                    System.out.println();

                    while (true)
                    {
                        System.out.println("Enter a number you want to search: ");
                        String searching_value=input.next();
                        //input.nextLine(); //to remove enter buffer

                        if(searching_value.equalsIgnoreCase("exit"))
                        {
                            break;
                        }
                        input.nextLine(); //to remove enter buffer

                        try {
                            int searching_Integer=Integer.parseInt(searching_value);

                            if(bst.searchItem(searching_Integer))
                            {
                                System.out.println(searching_Integer+" is found");
                            }
                            else
                                System.out.println(searching_Integer+" is not found");

                        }
                        catch (Exception e)
                        {
                            System.out.println("Invalid input for searching.Try Again!");
                            continue;
                        }
                    }


                }


                else if(N==3)
                {
                    System.out.println("GetInOrderSuccessor of a number.Enter EXIT to stop and return main menu");
                    System.out.println();

                    while (true)
                    {
                        System.out.println("Enter a number you want to know the in order successor: ");
                        String searching_value=input.next();
                        //input.nextLine(); //to remove enter buffer
                        if(searching_value.equalsIgnoreCase("exit"))
                        {
                            break;
                        }


                        try {
                            int searching_Integer=Integer.parseInt(searching_value);

                            System.out.println("In Order Successor of "+searching_Integer+" : "+
                                    bst.getInOrderSuccessor(searching_Integer));

                        }
                        catch (Exception e)
                        {
                            System.out.println("Invalid input for successor.Try Again!");
                            continue;
                        }
                    }

                }

               else if(N==4)
                {
                    System.out.println("GetInOrderPredecessor of a number.Enter EXIT to stop and return main menu");
                    System.out.println();

                    while (true)
                    {
                        System.out.println("Enter a number you want to know the in order Predecessor: ");
                        String searching_value=input.next();
                        //input.nextLine(); //to remove enter buffer
                        if(searching_value.equalsIgnoreCase("exit"))
                        {
                            break;
                        }


                        try {
                            int searching_Integer=Integer.parseInt(searching_value);

                            System.out.println("In Order Predecessor of "+searching_Integer+" : "+
                                    bst.getInOrderPredecessor(searching_Integer));

                        }
                        catch (Exception e)
                        {
                            System.out.println("Invalid input for Predecessor.Try Again!");
                            continue;
                        }
                    }

                }


               else if(N==5)
                {
                    System.out.println("Deleting of a number.Enter EXIT to stop and return main menu");
                    System.out.println();

                    while (true)
                    {
                        System.out.println("Enter a number you want to Delete: ");
                        String searching_value=input.next();
                      //  input.nextLine(); //to remove enter buffer
                        if(searching_value.equalsIgnoreCase("exit"))
                        {
                            break;
                        }


                        try {
                            int searching_Integer=Integer.parseInt(searching_value);

                            bst.deleteItem(searching_Integer);

                        }
                        catch (Exception e)
                        {
                           e.printStackTrace();
                            System.out.println("Invalid input for Deletion.Try Again!");
                            continue;
                        }
                    }

                }


               else if(N==6)
                {
                    System.out.println("Get the Depth of a number.Enter EXIT to stop and return main menu");
                    System.out.println();

                    while (true)
                    {
                        System.out.println("Enter a number you want to know the depth: ");
                        String searching_value=input.next();
                       // input.nextLine(); //to remove enter buffer
                        if(searching_value.equalsIgnoreCase("exit"))
                        {
                            break;
                        }


                        try {
                            int searching_Integer=Integer.parseInt(searching_value);

                            System.out.println("The depth of "+searching_Integer+" : "+bst.getItemDepth(searching_Integer));

                        }
                        catch (Exception e)
                        {
                            System.out.println("Invalid input for depth analysis.Try Again!");
                            continue;
                        }
                    }

                }


               else if(N==7)
                {
                    System.out.println("The max Item of BST : "+bst.getMaxItem());
                }

                else if(N==8)
                {
                    System.out.println("The min Item of the BST : "+bst.getMinItem());
                }
                else if(N==9)
                {
                    System.out.println("The Height of the BST : "+bst.getHeight(bst.getRoot()));
                }

                else if(N==10)
                {
                    System.out.print("In Order Traversal: ");
                    bst.printInOrder(bst.getRoot());
                    if(bst.getSize(bst.getRoot()) == 0)
                    {
                        System.out.print("[Empty]");
                    }
                    System.out.println();
                    System.out.println();
                }
                else if(N==11)
                {
                    System.out.print("Pre Order Traversal: ");
                    bst.printPreOrder(bst.getRoot());
                    if(bst.getSize(bst.getRoot()) == 0)
                    {
                        System.out.print("[Empty]");
                    }
                    System.out.println();
                    System.out.println();
                }
                else if(N==12)
                {
                    System.out.print("Post Order Traversal: ");
                    bst.printPostOrder(bst.getRoot());
                    if(bst.getSize(bst.getRoot()) == 0)
                    {
                        System.out.print("[Empty]");
                    }
                    System.out.println();
                    System.out.println();
                }
                else if(N==13)
                {
                    System.out.print("The size of the tree : "+bst.getSize(bst.getRoot()));
                    System.out.println();
                    System.out.println();
                }
                else
                {
                    System.out.println("Menu number should be in between 1 - 13.Try again!");
                }

            }
            catch (Exception e)
            {
                System.out.println("Invalid input.Try Again");
                continue;
            }
        }


    }
}
