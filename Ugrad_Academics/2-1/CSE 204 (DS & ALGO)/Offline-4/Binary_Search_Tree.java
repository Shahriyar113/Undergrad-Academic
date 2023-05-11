package Offline4;

public class Binary_Search_Tree {


    private Node root;

    Binary_Search_Tree()
    {
        root = null;

    }

    Binary_Search_Tree(Node root)
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

        Node(int itm)
        {
            item=itm;
            Left_Child=null;
            Right_Child=null;
            Parent=null;
        }


        int getItem()
        {
            return item;
        }

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
                    break;
                } else {
                    current_tree_Node = current_tree_Node.Left_Child;
                }
            }

            else  //current_tree_Node.getItem() > value
            {
                if (current_tree_Node.Right_Child == null) {
                    current_tree_Node.Right_Child = new_node; //inserted
                    current_tree_Node.Right_Child.Parent=current_tree_Node; //setting parent
                    break;
                } else {
                    current_tree_Node = current_tree_Node.Right_Child;
                }
            }

        }



    }


    public boolean searchItem(int searching_value)
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

            else //searching_value > current_tree_Node.getItem()
            {
                current_tree_Node = current_tree_Node.Right_Child;
            }
        }

        //successfully terminating this while loop means the searching value is not found
        return false;


    }

    public int getInOrderSuccessor(int value)
    {

        //at first i have to find out the node for the given value for which
        // i want to determine the inOrderSuccessor

        if(root == null) //if the tree is empty
        {
            System.out.println("Tree is empty");
            return Integer.MIN_VALUE;
        }

        Node current_tree_Node=root;
        Node Required_Node = null; //the node for which i will find the inOrderSuccessor


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

        //if the value is not found in the tree
        if(Required_Node == null)
        {
            System.out.println(value+" is not found in the tree");
        }

        //if the value is found then i have to find the inOrderSuccessor for that node now
        else
        {
            // the inOrderSuccessor can be find in two step

            //at first, we have to check whether the node has right subtree or not
            //if right subtree of that node exists then the minimum value of the right subtree
            //will be the inOrderSuccessor

            if(Required_Node.Right_Child != null)
            {
                Node Subtree_root=Required_Node.Right_Child;

                //tree er root theke left a jete jete j node er "left child = null" hobe shei node i lowest value

                while (Subtree_root.Left_Child != null)
                {
                    Subtree_root=Subtree_root.Left_Child;
                }

                return Subtree_root.getItem();  //this is the minimum value of right subtree

            }

            //if the node has no right subtree then the inOrderSuccessor will be one of its ancestors
            //so to find it ,i have to travarse through the parents until i found a node who is
            //the left child of its parent

            else   //when Required_Node.Right_Child == null)
            {
                Node current_ancestor=Required_Node;

                while (current_ancestor != null)
                {
                    Node Grand_parent=current_ancestor.Parent;
                    if(Grand_parent != null && current_ancestor == Grand_parent.Left_Child) //checkig that the current ancestor is the left child of its parent or not
                    {
                        return Grand_parent.getItem();
                    }
                    current_ancestor=Grand_parent;
                }

                //successfully terminating this while loop means there is no such ancestor
                //that means InOrderSuccessor is not found

            }



        }

        System.out.println(value+" has not any successors");
        return Integer.MIN_VALUE;




    }


    public int getInOrderPredecessor(int value)
    {
        //at first i have to find out the node for the given value for which
        // i want to determine the inOrderPredecessor

        if(root == null) //if the tree is empty
        {
            System.out.println("Tree is empty");
            return Integer.MIN_VALUE;
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

        //if the value is not found in the tree
        if(Required_Node == null)
        {
            System.out.println(value+" is not found in the tree");
            return Integer.MIN_VALUE;
        }

        //if the value is found then i have to find the inOrderPredecessor for that node now
        else
        {
            // the inOrderPredecessor can be find in two step

            //at first, we have to check whether the node has left subtree or not
            //if left subtree of that node exists then the maximum value of the left subtree
            //will be the inOrderPredecessor

            if(Required_Node.Left_Child != null)
            {
                Node Subtree_root=Required_Node.Left_Child;

                //tree er root theke right a jete jete j node er "right child = null" hobe shei node i highest value

                while (Subtree_root.Right_Child != null)
                {
                    Subtree_root=Subtree_root.Right_Child;
                }

                return Subtree_root.getItem();  //this is the minimum value of right subtree

            }

            //if the node has no left subtree then the inOrderPredecessor will be one of its ancestors
            //so to find it ,i have to travarse through the parents until i found a node who is
            //the right child of its parent

            else   //Required_Node.Left_Child == null
            {
                Node current_ancestor=Required_Node;

                while (current_ancestor != null)
                {
                    Node Grand_parent=current_ancestor.Parent;
                    if(Grand_parent != null && current_ancestor == Grand_parent.Right_Child) //checkig that the current ancestor is the left child of its parent or not
                    {
                        return Grand_parent.getItem();
                    }
                    current_ancestor=Grand_parent;
                }

                //successfully terminating this while loop means there is no such ancestor
                //that means inOrderPredecessor is not found

            }



        }

        System.out.println(value +" has no predecessors");
        return Integer.MIN_VALUE;


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
                    System.out.println(value+" was the last item and it is deleted ");
                    return;
                }

                Node Required_Node_Parent=Required_Node.Parent;

                if(Required_Node == Required_Node_Parent.Left_Child)
                {
                    Required_Node_Parent.Left_Child=null;
                    System.out.println(value+" is deleted for as 0 left child ");
                    return;
                }

                else //Required_Node == Required_Node_Parent.Right_Child
                {
                    Required_Node_Parent.Right_Child=null;
                    System.out.println(value+" is deleted as 0 right child");
                    return;
                }
            }

            //if the node has 1 children,then deletion is also easy
            else if(Required_Node.Left_Child == null || Required_Node.Right_Child == null)
            {
                //if there the Required_Node is root
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
                        System.out.println(value+" is deleted");
                        return;
                    }

                    Node Required_Node_Parent=Required_Node.Parent;

                    if(Required_Node == Required_Node_Parent.Left_Child)
                    {
                        Required_Node_Parent.Left_Child = Required_Node.Left_Child;
                        Required_Node.Left_Child.Parent=Required_Node_Parent;
                        System.out.println(value+" is deleted as 1 left child");

                    }
                    else //Required_Node == Required_Node_Parent.Right_Child
                    {
                        Required_Node_Parent.Right_Child = Required_Node.Left_Child;
                        Required_Node.Left_Child.Parent=Required_Node.Parent;
                        System.out.println(value+" is deleted as 1 right child");


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
                        System.out.println(value+" is deleted");
                        return;
                    }

                    Node Required_Node_Parent=Required_Node.Parent;

                    if(Required_Node == Required_Node_Parent.Left_Child)
                    {
                        Required_Node_Parent.Left_Child = Required_Node.Right_Child;
                        Required_Node.Right_Child.Parent=Required_Node_Parent;
                        System.out.println(value+" is deleted as 1 left child else");

                    }
                    else //Required_Node == Required_Node_Parent.Right_Child
                    {
                        Required_Node_Parent.Right_Child = Required_Node.Right_Child;
                        Required_Node.Right_Child.Parent=Required_Node_Parent;
                        System.out.println(value+" is deleted as 1 right child else");

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
                    System.out.println(value+" is deleted as 2 left child");

                }
                else //Replacable_node == Replacable_node_Parent.Right_Child
                {
                    Replacable_node_Parent.Right_Child= Replacable_node.Right_Child;
                    if(Replacable_node.Right_Child != null)
                    {
                        Replacable_node.Right_Child.Parent=Replacable_node_Parent;
                    }
                    System.out.println(value+" is deleted as 2 right child");


                }



            }



        }




    }


    //if the item is not found in the tree then the following method will return -1
    public int getItemDepth(int value)
    {
        int depth = 0;

        //ai if condition na likhleo hoto

        if(root == null) //if the tree is empty;
        {
            System.out.println("Tree is empty");
            return -1;
        }
        Node current_tree_Node=root;

        while (current_tree_Node != null)
        {
            if (current_tree_Node.getItem() == value) {
                return depth;
            }

            else if (value < current_tree_Node.getItem()) {
                current_tree_Node = current_tree_Node.Left_Child;
                depth++;
            }

            else //value > current_tree_Node.getItem()
            {
                current_tree_Node = current_tree_Node.Right_Child;
                depth++;
            }
        }

        //successfully terminating this while loop means the value is not found

        System.out.println(value+" is not found");
        return -1;


    }

    public int getMaxItem()
    {
        if(root == null)
        {
            System.out.println("Tree is Empty");
            return Integer.MIN_VALUE;
        }

        Node current_tree_Node=root;

        //tree er root theke right a jete jete j node er "right child = null" hobe shei node i highest value

        while (current_tree_Node.Right_Child != null)
        {
            current_tree_Node=current_tree_Node.Right_Child;
        }

        return current_tree_Node.getItem();


    }

    public int getMinItem()
    {
        if(root == null)
        {
            System.out.println("Tree is empty");
            return Integer.MAX_VALUE;
        }

        Node current_tree_Node=root;

        //tree er root theke left a jete jete j node er "left child = null" hobe shei node i lowest value

        while (current_tree_Node.Left_Child != null)
        {
            current_tree_Node=current_tree_Node.Left_Child;
        }

        return current_tree_Node.getItem();


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
            System.out.print(root.getItem()+" ");
            printPreOrder(root.Left_Child);
            printPreOrder(root.Right_Child);

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
