package Offline3_2;

public class EmptyQueueException extends Exception {

    @Override
    public String toString() {
        return "Queue is empty";
    }
}
