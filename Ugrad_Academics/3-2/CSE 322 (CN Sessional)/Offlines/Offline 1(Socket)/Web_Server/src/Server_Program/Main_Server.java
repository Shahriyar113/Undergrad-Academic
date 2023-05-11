package Server_Program;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Main_Server {

    static final int PORT = 5113;

    public static void main(String[] args) throws IOException {

        ServerSocket serverConnect = new ServerSocket(PORT);
        System.out.println("Server started.\nListening for connections on port : " + PORT + " ...\n");

        // System.out.println(content);

        while(true)
        {
            Socket s = serverConnect.accept();
            //System.out.println("A client connected");

            Server_Thread server_thread = new Server_Thread(s);
            server_thread.start();


    }

}







}
