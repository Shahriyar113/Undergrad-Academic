package Offline2;

public class InvalidCommandException extends Exception {
    @Override
    public String toString() {
        return "Invalid Command!Try again";
    }
}
