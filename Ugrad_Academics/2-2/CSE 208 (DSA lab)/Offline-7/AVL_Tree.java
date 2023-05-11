public class AVL_Tree {


    private Node root;

    AVL_Tree()
    {
        root = null;

    }

    AVL_Tree(Node root)
    {
        this.root=root;

    }

    Node getRoot()
    {
        return root;
    }

    class Node
    {
        int item;
        Node Left_Child;
        Node Right_Child;
        Node Parent;
        int height;
        int left_height;
        int right_height;

        Node(int itm)
        {
            item=itm;
            Left_Child=null;
            Right_Child=null;
            Parent=null;
            height=0;
            left_height = -1;
            right_height = -1;
        }


        int getItem()
        {
            return item;
        }

    }


    Node Is_Balanced(Node last_inserted)
    {
        Node rotating_node = null;
        Node current_node = last_inserted;

        while (current_node!=null)
        {
            if(Math.abs(current_node.left_height-current_node.right_height) <= 1 )
            {
                //current_node is balanced
            }
            else
            {
                //for current node ,the height variant got violated
                return current_node;
            }
            current_node = current_node.Parent;
        }

        //if all node are balanced
        return null;

    }



    public void insertItem(int value)
    {

        //the parent of root always null
        //the both child of leaf node always null

        Node new_node=new Node(value);
        if(root == null)
        {
            root=new_node;

            return;
        }

        Node current_tree_Node=root;

        while (true)
        {
            if ( value < current_tree_Node.getItem()) {
                if (current_tree_Node.Left_Child == null) {
                    current_tree_Node.Left_Child = new_node; //inserted
                    current_tree_Node.Left_Child.Parent=current_tree_Node; //setting parent

                    //Reseting the "Height" of parents

                    Node current_Parent = current_tree_Node;

                    //logn time
                    while (current_Parent != null)
                    {
                        if(current_Parent.Right_Child != null)
                        {
                            current_Parent.height = Math.max(current_Parent.Left_Child.height,
                                    current_Parent.Right_Child.height) + 1; //setting each node height

                            current_Parent.left_height = current_Parent.Left_Child.height;//Setting left height
                           // current_Parent.right_height = current_Parent.Right_Child.height;//Setting right height


                        }

                        else //if (current_Parent.Right_Child == null)
                        {
                            current_Parent.height = current_Parent.Left_Child.height + 1;
                            current_Parent.left_height = current_Parent.Left_Child.height;//Setting right height

                        }




                        current_Parent=current_Parent.Parent;

                    }




                    break;
                } else {
                    current_tree_Node = current_tree_Node.Left_Child;
                }
            }

            else  //current_tree_Node.getItem() >= value
            {
                if (current_tree_Node.Right_Child == null) {
                    current_tree_Node.Right_Child = new_node; //inserted
                    current_tree_Node.Right_Child.Parent=current_tree_Node; //setting parent


                    //Reheighting the tree
                    Node current_Parent = current_tree_Node;
                    //logn time
                    while (current_Parent != null)
                    {
                        if(current_Parent.Left_Child != null)
                        {
                            current_Parent.height = Math.max(current_Parent.Left_Child.height,
                                    current_Parent.Right_Child.height) + 1; //setting each node height

                           // current_Parent.left_height = current_Parent.Left_Child.height;//Setting left height
                            current_Parent.right_height = current_Parent.Right_Child.height;//Setting right height


                        }

                        else //if (current_Parent.Left_Child == null)
                        {
                            current_Parent.height = current_Parent.Right_Child.height + 1;
                            current_Parent.right_height = current_Parent.Right_Child.height;//Setting right height

                        }




                        current_Parent=current_Parent.Parent;

                    }

                    break;
                } else {
                    current_tree_Node = current_tree_Node.Right_Child;
                }
            }

        }


        //after every insertion , checking whether the tree is "height balanced" or not
        Node Unbalanced_node = Is_Balanced(new_node);
        if(Unbalanced_node == null)
        {
            //fine..the tree is balanced
        }

        else
        {
            System.out.println("Height Invariant Violated");
            //System.out.println("Violating: "+Unbalanced_node.getItem());

            //Finding the node on which rotation will occur
            try {

               if(Unbalanced_node.Parent == null)
               {
                   root = Rotate(Unbalanced_node,Unbalanced_node.Parent);
               }
               else
               {
                   if(Unbalanced_node.Parent.Left_Child == Unbalanced_node)
                   {
                       Unbalanced_node.Parent.Left_Child = Rotate(Unbalanced_node,Unbalanced_node.Parent);
                   }
                   if(Unbalanced_node.Parent.Right_Child == Unbalanced_node)
                   {
                       Unbalanced_node.Parent.Right_Child = Rotate(Unbalanced_node,Unbalanced_node.Parent);
                   }

               }

            }catch (Exception e)
            {
                e.printStackTrace();
            }


            System.out.print("After rebalancing: ");
        }



    }



    Node Rotate(Node root,Node Unbalanced_node_parent)
    {
        Node current_root = null;

        if(root.left_height > root.right_height)
        {
            current_root = root.Left_Child;
            if(current_root.left_height >= current_root.right_height)
            {
                //left left
                //zig-zig
                //Single rotation

                //Right rotation at root
                root = current_root;
                Node Back_up = root.Right_Child;
                root.Right_Child = root.Parent;
                root.Right_Child.Left_Child = Back_up;

                root.Parent = Unbalanced_node_parent;
                root.Right_Child.Parent = root;

                if(root.Right_Child.Left_Child != null)//Back_up node can be null
                root.Right_Child.Left_Child.Parent = root.Right_Child;

                //reseting the heights

                //height of x
                if(root.Right_Child.Left_Child != null && root.Right_Child.Right_Child != null  )
                { root.Right_Child.height = Math.max(root.Right_Child.Left_Child.height,
                        root.Right_Child.Right_Child.height) + 1;

                    root.Right_Child.left_height = root.Right_Child.Left_Child.height ;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;
                }


                else if(root.Right_Child.Left_Child != null)
                {
                    root.Right_Child.height = root.Right_Child.Left_Child.height + 1;
                    root.Right_Child.left_height = root.Right_Child.Left_Child.height ;
                    root.Right_Child.right_height = -1;

                }

                else if(root.Right_Child.Right_Child != null)
                {
                    root.Right_Child.height =  root.Right_Child.Right_Child.height + 1;
                    root.Right_Child.left_height = -1 ;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;
                }

                else
                {
                    root.Right_Child.height = 0;
                    root.Right_Child.left_height = -1;
                    root.Right_Child.right_height = -1;

                }
                //height of y
                root.height = Math.max(root.Left_Child.height,root.Right_Child.height)+1;

                root.left_height = root.Left_Child.height ;
                root.right_height = root.Right_Child.height ;

                //root.Right_Child.left_height = root.Right_Child.Left_Child.height ;
               // root.Right_Child.right_height = root.Right_Child.Right_Child.height;




            }

            else //current_root.left_height < current_root.right_height
            {
                //left right
                //zig-zag
                //Double rotation

                current_root = current_root.Right_Child;

                //1st rotation
                //left rotating at current_root.parent
                root.Left_Child = current_root;
                Node Back_Up = current_root.Left_Child;
                root.Left_Child.Left_Child = current_root.Parent;
                root.Left_Child.Left_Child.Right_Child = Back_Up;


                root.Left_Child.Parent = root;
                root.Left_Child.Left_Child.Parent = root.Left_Child;

                if( root.Left_Child.Left_Child.Right_Child != null)//Back_up node can be null
                root.Left_Child.Left_Child.Right_Child.Parent = root.Left_Child.Left_Child;


                //2nd rotation
                //Right Rotation at root

                root = current_root;
                Back_Up = current_root.Right_Child;
                root.Right_Child = current_root.Parent;
                root.Right_Child.Left_Child = Back_Up;

                root.Parent = Unbalanced_node_parent;
                root.Right_Child.Parent = root;

                if(root.Right_Child.Left_Child != null) //Back_up node can be null
                root.Right_Child.Left_Child.Parent = root.Right_Child;



                //Reseting Heights

                if(root.Left_Child.Left_Child != null && root.Left_Child.Right_Child != null )
                {
                    root.Left_Child.height = Math.max(root.Left_Child.Left_Child.height,
                        root.Left_Child.Right_Child.height) +1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = root.Left_Child.Right_Child.height;

                }

                else if(root.Left_Child.Left_Child != null)
                {
                    root.Left_Child.height = root.Left_Child.Left_Child.height + 1;

                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = -1;

                }

                else if( root.Left_Child.Right_Child != null)
                {
                    root.Left_Child.height = root.Left_Child.Right_Child.height + 1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = -1;
                }

                else
                {
                    root.Left_Child.height = 0;
                    root.Left_Child.left_height = -1;
                    root.Left_Child.right_height = -1;
                }



                if(root.Right_Child.Left_Child != null && root.Right_Child.Right_Child !=null) {
                    root.Right_Child.height = Math.max(root.Right_Child.Left_Child.height,
                            root.Right_Child.Right_Child.height) + 1;

                    root.Right_Child.left_height = root.Right_Child.Left_Child.height;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;

                }

                else if(root.Right_Child.Left_Child != null )
                {
                    root.Right_Child.height = root.Right_Child.Left_Child.height + 1;

                    root.Right_Child.left_height = root.Right_Child.Left_Child.height;
                    root.Right_Child.right_height = -1;

                }

                else if(root.Right_Child.Right_Child !=null)
                {
                    root.Right_Child.height = root.Right_Child.Right_Child.height + 1;
                    root.Right_Child.left_height = -1;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;

                }
                else
                {
                    root.Right_Child.height = 0;
                    root.Right_Child.left_height = -1;
                    root.Right_Child.right_height = -1;

                }

                root.height = Math.max(root.Left_Child.height,
                        root.Right_Child.height) +1;

                root.left_height = root.Left_Child.height;
                root.right_height = root.Right_Child.height;

               // root.Left_Child.left_height = root.Left_Child.Left_Child.height;
               // root.Left_Child.right_height = root.Left_Child.Right_Child.height;

               // root.Right_Child.left_height = root.Right_Child.Left_Child.height;
               // root.Right_Child.right_height = root.Right_Child.Right_Child.height;



            }






        }

        else //root.left_height < root.right_height
        {
            //System.out.println(current_root.left_height+" "+current_root.right_height);

            current_root=root.Right_Child;
            if(current_root.right_height >= current_root.left_height)
            {
                //current_root = current_root.Right_Child;
                //right right
                //zig-zig
                //single rotation

                //left rotation at root



                root = current_root;
                Node Back_up = root.Left_Child;
                root.Left_Child = root.Parent;
                root.Left_Child.Right_Child = Back_up;

                root.Parent = Unbalanced_node_parent;
                root.Left_Child.Parent = root;

                if(root.Left_Child.Right_Child != null) //Back_up node can be null
                root.Left_Child.Right_Child.Parent = root.Left_Child;



                //reseting the heights

                //height of y

                if(root.Left_Child.Left_Child != null && root.Left_Child.Right_Child != null ) {
                    root.Left_Child.height = Math.max(root.Left_Child.Left_Child.height,
                            root.Left_Child.Right_Child.height) + 1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height ;
                    root.Left_Child.right_height = root.Left_Child.Right_Child.height ;

                }
                else if(root.Left_Child.Left_Child != null )
                {
                    root.Left_Child.height = root.Left_Child.Left_Child.height + 1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height ;
                    root.Left_Child.right_height = -1 ;
                }

                else if(root.Left_Child.Right_Child != null)
                {
                    root.Left_Child.height = root.Left_Child.Right_Child.height + 1;
                    root.Left_Child.left_height = -1;
                    root.Left_Child.right_height = root.Left_Child.Right_Child.height ;

                }

                else
                {
                    root.Left_Child.height = 0;
                    root.Left_Child.left_height = -1;
                    root.Left_Child.right_height = -1 ;

                }
                //height of x(root)
                root.height = Math.max(root.Left_Child.height,root.Right_Child.height)+1;


                root.left_height = root.Left_Child.height ;
                root.right_height = root.Right_Child.height ;

               // root.Left_Child.left_height = root.Left_Child.Left_Child.height ;
                //root.Left_Child.right_height = root.Left_Child.Right_Child.height ;




            }


            else //current_root.right_height < current_root.left_height
            {
                //right left
                //zig-zag
                //Double rotation

                current_root = current_root.Right_Child;

                //1st rotation
                //right rotating at current_root.parent
                root.Right_Child = current_root;
                Node Back_Up = current_root.Right_Child;
                root.Right_Child.Right_Child = current_root.Parent;
                root.Right_Child.Right_Child.Left_Child = Back_Up;


                root.Right_Child.Parent = root;
                root.Right_Child.Right_Child.Parent = root.Right_Child;

                if(root.Right_Child.Right_Child.Left_Child != null) //Back up node can be null
                root.Right_Child.Right_Child.Left_Child.Parent = root.Right_Child.Right_Child;


                //2nd rotation
                //left Rotation at root

                root = current_root;
                Back_Up = current_root.Left_Child;
                root.Left_Child = current_root.Parent;
                root.Left_Child.Right_Child = Back_Up;

                root.Parent = Unbalanced_node_parent;
                root.Left_Child.Parent = root;

                if(root.Left_Child.Right_Child != null) //Back_up node can be null
                root.Left_Child.Right_Child.Parent = root.Left_Child;



                //Reseting Heights

                if(root.Left_Child.Left_Child != null && root.Left_Child.Right_Child != null )
                {
                    root.Left_Child.height = Math.max(root.Left_Child.Left_Child.height,
                            root.Left_Child.Right_Child.height) +1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = root.Left_Child.Right_Child.height;

                }

                else if(root.Left_Child.Left_Child != null)
                {
                    root.Left_Child.height = root.Left_Child.Left_Child.height + 1;

                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = -1;

                }

                else if( root.Left_Child.Right_Child != null)
                {
                    root.Left_Child.height = root.Left_Child.Right_Child.height + 1;
                    root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                    root.Left_Child.right_height = -1;
                }

                else
                {
                    root.Left_Child.height = 0;
                    root.Left_Child.left_height = -1;
                    root.Left_Child.right_height = -1;
                }



                if(root.Right_Child.Left_Child != null && root.Right_Child.Right_Child !=null) {
                    root.Right_Child.height = Math.max(root.Right_Child.Left_Child.height,
                            root.Right_Child.Right_Child.height) + 1;

                    root.Right_Child.left_height = root.Right_Child.Left_Child.height;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;

                }

                else if(root.Right_Child.Left_Child != null )
                {
                    root.Right_Child.height = root.Right_Child.Left_Child.height + 1;

                    root.Right_Child.left_height = root.Right_Child.Left_Child.height;
                    root.Right_Child.right_height = -1;

                }

                else if(root.Right_Child.Right_Child !=null)
                {
                    root.Right_Child.height = root.Right_Child.Right_Child.height + 1;
                    root.Right_Child.left_height = -1;
                    root.Right_Child.right_height = root.Right_Child.Right_Child.height;

                }
                else
                {
                    root.Right_Child.height = 0;
                    root.Right_Child.left_height = -1;
                    root.Right_Child.right_height = -1;

                }

                root.height = Math.max(root.Left_Child.height,
                        root.Right_Child.height) +1;

                root.left_height = root.Left_Child.height;
                root.right_height = root.Right_Child.height;


                //root.Left_Child.left_height = root.Left_Child.Left_Child.height;
                //root.Left_Child.right_height = root.Left_Child.Right_Child.height;

               // root.Right_Child.left_height = root.Right_Child.Left_Child.height;
                //root.Right_Child.right_height = root.Right_Child.Right_Child.height;





            }

        }

        return root;

    }


    public boolean Find_Item(int searching_value)
    {
        //ai if condition na likhleo hoto
        if(root == null) //if the tree is empty
        {
            return false;
        }

        Node current_tree_Node=root;


        while (current_tree_Node != null)
        {
            if (current_tree_Node.getItem() == searching_value) {
                return true;
            }

            else if (searching_value < current_tree_Node.getItem()) {
                current_tree_Node = current_tree_Node.Left_Child;
            }

            else //searching_value >= current_tree_Node.getItem()
            {
                current_tree_Node = current_tree_Node.Right_Child;
            }
        }

        //successfully terminating this while loop means the searching value is not found
        return false;


    }




    void deleteItem(int value)
    {
        //at first i have to find out the node which i want to delete

        if(root == null) //if the tree is empty
        {
            System.out.println("Tree is empty");
            return;
        }

        Node current_tree_Node=root;
        Node Required_Node = null; //the node for which i will find the inOrderPredecessor


        while (current_tree_Node != null)
        {
            if (current_tree_Node.getItem() == value) {
                Required_Node=current_tree_Node;
                break;
            }

            else if (value < current_tree_Node.getItem()) {
                current_tree_Node = current_tree_Node.Left_Child;
            }

            else //value > current_tree_Node.getItem()
            {
                current_tree_Node = current_tree_Node.Right_Child;
            }
        }

        Node searched_unbalanced_node=null;

        //searching the required node completed

        //if the value is not found in the tree,do nothing
        if(Required_Node == null)
        {
            System.out.println(value +" is not found to delete");
            return ;
        }

        //if the value is found then i have to delete that node now
        else //deletion process starts
        {
            //As it is binary tree.so a node has 0 children,1 children or 2 children

            //if the node has 0 children,then deletion is too easy
            if(Required_Node.Left_Child == null && Required_Node.Right_Child == null)
            {
                //if there is only one element in the tree
                //this special condition sould be checked because root node has no parent
                if(Required_Node == root)
                {
                    root = null;
                    //System.out.println(value+" was the last item and it is deleted ");
                    return;
                }

                Node Required_Node_Parent=Required_Node.Parent;

                if(Required_Node == Required_Node_Parent.Left_Child)
                {
                    Required_Node_Parent.Left_Child=null;
                    //System.out.println(value+" is deleted for as 0 left child ");

                }

                else //Required_Node == Required_Node_Parent.Right_Child
                {
                    Required_Node_Parent.Right_Child=null;
                    //System.out.println(value+" is deleted as 0 right child");

                }


                //Re_heighting
                if(Required_Node != root)
                {
                    Node curr_node = Required_Node.Parent;
                    searched_unbalanced_node = Required_Node.Parent;

                    while (curr_node != null)
                    {
                        if(curr_node.Left_Child != null && curr_node.Right_Child != null)
                        {
                            curr_node.height = Math.max(curr_node.Left_Child.height,
                                    curr_node.Right_Child.height)+1;
                            curr_node.left_height = curr_node.Left_Child.height;
                            curr_node.right_height = curr_node.Right_Child.height;

                        }

                        else if(curr_node.Left_Child != null)
                        {
                            curr_node.height = curr_node.Left_Child.height + 1;
                            curr_node.left_height = curr_node.Left_Child.height;
                            curr_node.right_height = -1;
                        }

                        else if(curr_node.Right_Child != null)
                        {
                            curr_node.height = curr_node.Right_Child.height + 1;
                            curr_node.left_height = -1;
                            curr_node.right_height = curr_node.Right_Child.height;
                        }
                        else
                        {
                            curr_node.height = 0;
                            curr_node.left_height = -1;
                            curr_node.right_height =-1;
                        }

                        curr_node = curr_node.Parent;
                    }

                }



            }

            //if the node has 1 children,then deletion is also easy
            else if(Required_Node.Left_Child == null || Required_Node.Right_Child == null)
            {
                //if  the Required_Node is root
                //this extra condition sould be checked because root node has no parent

                //if that 1 child is the left child
                if(Required_Node.Left_Child != null)
                {
                    //if there the Required_Node is root
                    //this special condition sould be checked because root node has no parent
                    if(Required_Node == root)
                    {
                        root = Required_Node.Left_Child;
                        Required_Node.Left_Child.Parent=null; //now Required_node.left child is the root
                        //System.out.println(value+" is deleted");
                        return;
                    }

                    Node Required_Node_Parent=Required_Node.Parent;

                    if(Required_Node == Required_Node_Parent.Left_Child)
                    {
                        Required_Node_Parent.Left_Child = Required_Node.Left_Child;
                        Required_Node.Left_Child.Parent=Required_Node_Parent;
                       // System.out.println(value+" is deleted as 1 left child");

                    }
                    else //Required_Node == Required_Node_Parent.Right_Child
                    {
                        Required_Node_Parent.Right_Child = Required_Node.Left_Child;
                        Required_Node.Left_Child.Parent=Required_Node.Parent;
                        //System.out.println(value+" is deleted as 1 right child");


                    }

                }
                //if that 1 child is the Right child

                else //Required_Node.Right_Child != null
                {
                    //if there the Required_Node is root
                    //this special condition sould be checked because root node has no parent
                    if(Required_Node == root)
                    {
                        root = Required_Node.Right_Child;
                        Required_Node.Right_Child.Parent=null; //now Required_node.left child is the root
                        //System.out.println(value+" is deleted");
                        return;
                    }

                    Node Required_Node_Parent=Required_Node.Parent;

                    if(Required_Node == Required_Node_Parent.Left_Child)
                    {
                        Required_Node_Parent.Left_Child = Required_Node.Right_Child;
                        Required_Node.Right_Child.Parent=Required_Node_Parent;
                        //System.out.println(value+" is deleted as 1 left child else");

                    }
                    else //Required_Node == Required_Node_Parent.Right_Child
                    {
                        Required_Node_Parent.Right_Child = Required_Node.Right_Child;
                        Required_Node.Right_Child.Parent=Required_Node_Parent;
                        //System.out.println(value+" is deleted as 1 right child else");

                    }
                }


                //Re_heighting

                if(Required_Node != root)
                {
                    Node curr_node = Required_Node.Parent;
                    searched_unbalanced_node = Required_Node.Parent;

                    while (curr_node != null)
                    {
                        if(curr_node.Left_Child != null && curr_node.Right_Child != null)
                        {
                            curr_node.height = Math.max(curr_node.Left_Child.height,
                                    curr_node.Right_Child.height)+1;
                            curr_node.left_height = curr_node.Left_Child.height;
                            curr_node.right_height = curr_node.Right_Child.height;

                        }

                        else if(curr_node.Left_Child != null)
                        {
                            curr_node.height = curr_node.Left_Child.height + 1;
                            curr_node.left_height = curr_node.Left_Child.height;
                            curr_node.right_height = -1;
                        }

                        else if(curr_node.Right_Child != null)
                        {
                            curr_node.height = curr_node.Right_Child.height + 1;
                            curr_node.left_height = -1;
                            curr_node.right_height = curr_node.Right_Child.height;
                        }
                        else
                        {
                            curr_node.height = 0;
                            curr_node.left_height = -1;
                            curr_node.right_height =-1;
                        }

                        curr_node = curr_node.Parent;
                    }

                }






            }

            //if the node has 2 children,then deletion is also critical
            //here there are 3 steps
            //1. at first we have to identify the inOrderSuccessor "replacable_node" (minimum value of Right subtree)
            // of that Required node..

            //2. then we have to replace the value of that replacable_node with the
            //Required node

            //3.then the replacable_node will be replaced by the right subtree of itself(Replacable
            //node can not have left child / left subtree as it is the minimum value found)

            else
            {
                //step-1
                //finding the "replacable_node" (minimum node of right subtree)
                Node Replacable_node=Required_Node.Right_Child;

                //tree er root theke left a jete jete j node er "left child = null" hobe shei node i lowest value

                while (Replacable_node.Left_Child != null)
                {
                    Replacable_node=Replacable_node.Left_Child;
                }

                //after terminating this while loop
                //"Replacable_node" is the node with the minimum value of right subtree


                //step - 2
                Required_Node.item=Replacable_node.item;

                //step -3
                Node Replacable_node_Parent = Replacable_node.Parent;
                if(Replacable_node == Replacable_node_Parent.Left_Child)
                {
                    Replacable_node_Parent.Left_Child= Replacable_node.Right_Child;

                    //setting the parent for the replacable right subtree of minimum value node
                    if(Replacable_node.Right_Child != null)
                    {
                        Replacable_node.Right_Child.Parent=Replacable_node_Parent;
                    }
                    //System.out.println(value+" is deleted as 2 left child");

                }
                else //Replacable_node == Replacable_node_Parent.Right_Child
                {
                    Replacable_node_Parent.Right_Child= Replacable_node.Right_Child;
                    if(Replacable_node.Right_Child != null)
                    {
                        Replacable_node.Right_Child.Parent=Replacable_node_Parent;
                    }
                    //System.out.println(value+" is deleted as 2 right child");


                }



                //Re_heighting
                Node curr_node = Replacable_node.Parent;
                searched_unbalanced_node = Replacable_node.Parent;



                while (curr_node != null)
                {
                    if(curr_node.Left_Child != null && curr_node.Right_Child != null)
                    {
                        curr_node.height = Math.max(curr_node.Left_Child.height,
                                curr_node.Right_Child.height)+1;
                        curr_node.left_height = curr_node.Left_Child.height;
                        curr_node.right_height = curr_node.Right_Child.height;

                    }

                    else if(curr_node.Left_Child != null)
                    {
                        curr_node.height = curr_node.Left_Child.height + 1;
                        curr_node.left_height = curr_node.Left_Child.height;
                        curr_node.right_height = -1;
                    }

                    else if(curr_node.Right_Child != null)
                    {
                        curr_node.height = curr_node.Right_Child.height + 1;
                        curr_node.left_height = -1;
                        curr_node.right_height = curr_node.Right_Child.height;
                    }
                    else
                    {
                        curr_node.height = 0;
                        curr_node.left_height = -1;
                        curr_node.right_height =-1;
                    }

                    curr_node = curr_node.Parent;
                }








            }


            //After deleting the node,Tree should be re balanced if height variant get violated

            Node Unbalanced_node = Is_Balanced(searched_unbalanced_node);
            if(Unbalanced_node == null)
            {
                //fine..the tree is balanced
            }

            else
            {
                System.out.println("Height Invariant Violated");
                //System.out.println("Violating: "+Unbalanced_node.getItem());

                //Finding the node on which rotation will occur
                try {

                    if(Unbalanced_node.Parent == null)
                    {
                        root = Rotate(Unbalanced_node,Unbalanced_node.Parent);
                    }
                    else
                    {
                        if(Unbalanced_node.Parent.Left_Child == Unbalanced_node)
                        {
                            Unbalanced_node.Parent.Left_Child = Rotate(Unbalanced_node,Unbalanced_node.Parent);
                        }
                        if(Unbalanced_node.Parent.Right_Child == Unbalanced_node)
                        {
                            Unbalanced_node.Parent.Right_Child = Rotate(Unbalanced_node,Unbalanced_node.Parent);
                        }

                    }

                }catch (Exception e)
                {
                    e.printStackTrace();
                }


                System.out.print("After rebalancing: ");
            }


        }



    }

    public void printInOrder(Node root)
    {

        if(root != null)
        {
            printInOrder(root.Left_Child);
            System.out.print(root.getItem()+" ");
            printInOrder(root.Right_Child);
        }

    }

    public void printPreOrder(Node root)
    {
        if(root != null)
        {
            System.out.print(root.getItem());

            if(root.Left_Child == null && root.Right_Child == null)
            {
                return;
            }

            System.out.print("(");

            printPreOrder(root.Left_Child);
            System.out.print(")");



            System.out.print("(");

            printPreOrder(root.Right_Child);
            System.out.print(")");


        }

    }

    public void printPostOrder(Node root)
    {
        if(root != null)
        {
            printPostOrder(root.Left_Child);
            printPostOrder(root.Right_Child);
            System.out.print(root.getItem()+" ");
        }
    }

    public int getSize(Node root)
    {
        if(root == null)
        {
            return 0;
        }
        else
            return getSize(root.Left_Child) + getSize(root.Right_Child) +1;
    }

    public int getHeight(Node root)
    {
        if(root == null)
        {
            return -1;
        }
        else
        {
            return Math.max(getHeight(root.Left_Child),getHeight(root.Right_Child)) + 1 ;
        }
    }




}
