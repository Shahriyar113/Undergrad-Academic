import java.net.Socket;
import java.util.Scanner;

public class Client {


    static final int PORT = 5113;


    public static void main(String[] args) {

        Socket socket = null;

        try {

            while(true) {


                //System.out.print("Enter a upload request:\n");
                Scanner input = new Scanner(System.in);
                String upload_request = input.nextLine();
                socket = new Socket("localhost", PORT);


                Thread cilent_thread = new Client_Thread(socket, upload_request);
                cilent_thread.start();
            }
        }catch (Exception e)
        {
            System.out.println("Server closed");
        }



    }


}
