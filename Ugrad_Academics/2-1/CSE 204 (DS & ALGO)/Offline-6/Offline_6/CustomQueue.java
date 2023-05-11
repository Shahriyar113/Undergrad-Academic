package Offline_6;

public class CustomQueue<T> {


    private Node front;
    private Node tail;

    class Node
    {
        T ch;
        Node next;

        Node(T c)
        {
            ch=c;
            next=null;
        }

        T getCh()
        {
            return ch;
        }
    }

    CustomQueue()
    {
        this.front=null;
        this.tail=null;
    }


    CustomQueue (Node front,Node tail)
    {
        this.front=front;
        this.tail=tail;
    }

    void enqueue(T ch)
    {
        Node node=new Node(ch);

        //for pushing very first element into the queue..i.e when it is empty stack

        if(front == null)
        {
           front = node;
           tail=node;
           return;
        }

        tail.next=node;
        tail=node;
    }

    T dequeue() throws EmptyQueueException
    {
        if(front == null)
        {

            throw new EmptyQueueException();
        }
        Node popped_node=front;
        front=front.next;
        return popped_node.getCh();
    }

    //This method will just return the value of front node without removing it
    T peek() throws EmptyQueueException
    {
        if(front == null)
        {
            throw new EmptyQueueException();
        }

        return front.getCh();
    }

    boolean isEmpty()
    {
        if(front == null)
        {

            return true;
        }
       else
            return false;
    }

}
