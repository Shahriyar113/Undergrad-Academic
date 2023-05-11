import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client_Thread extends Thread {


    //jei folder er file upload deya hobe oi folder er absolute path
    public static String Home_path = "C:/Users/ASUS/Desktop/Java_practices/Client_Program/From";
    public static final int chunk_size = 1024;
    Socket socket;
    String upload_request;


    Client_Thread(Socket socket,String upload_request)
    {
        this.socket = socket;
        this.upload_request = upload_request;
    }



     public void run() {


        try {

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pr = new PrintWriter(socket.getOutputStream());

            //Sending upload request to server

            pr.write(upload_request);
            pr.write("\r\n");
            pr.flush();

            String response_from_server = in.readLine();
            if(response_from_server.equalsIgnoreCase("OK"))
            {
                //the file which will be uploaded to the server
                String uploading_file_name = upload_request.split(" ")[1];

                File sending_file = new File (Home_path+"/"+uploading_file_name);

                if(sending_file.exists())
                {
                    pr.write("Sending from client");
                    pr.write("\r\n");
                    pr.flush();

                    System.out.println(uploading_file_name+" is uploading");

                    byte[] single_chunk = new byte[chunk_size];
                    int count = 0;

                    BufferedInputStream bis = new BufferedInputStream(new FileInputStream(sending_file));

                    OutputStream socket_out = socket.getOutputStream();

                    //sending file chunk by chunk
                    while((count = bis.read(single_chunk)) > 0)
                    {
                        socket_out.write(single_chunk, 0, count);
                        socket_out.flush();
                    }

                    System.out.println(uploading_file_name+" upload successful");



                }

                else
                {
                    pr.write("File doesn't exist");
                    pr.write("\r\n");
                    pr.flush();

                    System.out.println("File doesn't exist");
                }

            }

            else //if anything error
            {
                System.out.println(response_from_server);
            }



            socket.close();





        }catch (Exception e)
        {

            System.out.println("Server closed Suddenly");
        }

    }

}
