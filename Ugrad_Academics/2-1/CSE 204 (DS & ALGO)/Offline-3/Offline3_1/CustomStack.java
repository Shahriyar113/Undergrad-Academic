package Offline3_1;

public class CustomStack<T> {


    private Node tail;
    private Node head;
    private int size;


    class Node
    {
        T item;
        Node next;
        Node previous;
        Node(T itm)
        {
            item=itm;
            next=null;
            previous=null;

        }

        T getValue()
        {
            return item;
        }


    }

    CustomStack()
    {
        size=0;
        tail = null;
        head =null;
    }


    CustomStack(Node head)
    {
        this.head=head;
    }


    void push(T item)
    {
        Node node=new Node(item);
        //when the stack is empty
        if(tail == null)
        {
            head=node;
            tail=node;
            size++;

            return;
        }
//        node.next=head;
//        head=node;
        tail.next=node;
        node.previous=tail;
        tail=node;
        size++;


    }


    T pop() throws Exception
    {
        if(tail == null)
        {
            throw new EmptyStackException();
        }

        //when only one element remains in stack
        if(head == tail)
        {
            Node popped_Node=tail;
            tail=null;
            head=null;
            size--;


            return popped_Node.item ;

        }

        Node popped_node=tail;
        tail.previous.next=null;
        tail=tail.previous;
       // tail.next=null;
        size--;

        return popped_node.item;
    }

    //it will just return the topmost element of the stack without removing it
    T peek() throws Exception
    {
        if(tail == null)
        {
            head=null;
            throw new EmptyStackException();
        }
        return tail.item;
    }



    boolean isEmpty()
    {
        if(tail == null)
            return true;
        else
            return false;
    }

    int getSize()
    {
        return size;
    }

    @Override
    public String toString() {
       String str ="";
       Node currentNode=head;
       while(currentNode!=null)
       {
           str=str+currentNode.item+" ";
           currentNode=currentNode.next;
       }
       return str;
    }
}
