package Server_Program;

import java.io.*;
import java.net.Socket;
import java.nio.file.Files;
import java.util.Date;

public class Server_Thread extends Thread {

    //public static int html_file_count =0;
    public static String Home_path = "C:/Users/ASUS/Desktop/Java_practices/Web_Server";
    public static final int chunk_size = 1024;


    PrintWriter log_file_writer;


    Socket socket;

    Server_Thread(Socket socket)
    {
        this.socket = socket;
        try {
            log_file_writer=new PrintWriter(new FileWriter("log.txt", true),true);
        }catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void create_new_html_file(String content,String filename) throws IOException
    {
        File file = new File (filename+".html");
        PrintWriter p= new PrintWriter(file);
        p.print(content);
        p.flush();

    }


    public static String read_from_file(String filename) throws IOException
    {

        File file = new File(filename);
        FileInputStream fis = new FileInputStream(file);
        BufferedReader br = new BufferedReader(new InputStreamReader(fis, "UTF-8"));
        StringBuilder sb = new StringBuilder();
        String line;
        while(( line = br.readLine()) != null ) {
            sb.append( line );
            sb.append( '\n' );
        }

        String content = sb.toString();
        return content;
    }


    public void run()
    {

       try {

           BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
           PrintWriter pr = new PrintWriter(socket.getOutputStream());
           try
           {



               String input = in.readLine();

             //  System.out.println(socket);

               if(!input.contains("favicon.ico")) {
                   System.out.println("input : " + input);

                   if(input.contains("HTTP")) {
                       log_file_writer.println("HTTP Request: " + input);
                       log_file_writer.println();
                   }

               }


               // String content = "<html>Hello</html>";

                   if (input.startsWith("GET")) {
                       if (input.split(" ")[1].equalsIgnoreCase("/")) { //http response
                           String content = read_from_file("Home_page.html");

                           pr.write("HTTP/1.1 200 OK\r\n");
                           pr.write("Server: Java HTTP Server: 1.0\r\n");
                           pr.write("Date: " + new Date() + "\r\n");
                           pr.write("Content-Type: text/html\r\n");
                           pr.write("Content-Length: " + content.length() + "\r\n");
                           pr.write("\r\n");
                           pr.write(content);
                           pr.flush();

                           //writing response to log file
                           log_file_writer.println("HTTP Response");
                           log_file_writer.println("--------------");

                           log_file_writer.write("HTTP/1.1 200 OK\r\n");
                           log_file_writer.write("Server: Java HTTP Server: 1.0\r\n");
                           log_file_writer.write("Date: " + new Date() + "\r\n");
                           log_file_writer.write("Content-Type: text/html\r\n");
                           log_file_writer.write("Content-Length: " + content.length() + "\r\n");
                           log_file_writer.write("\r\n");
                           log_file_writer.write("Content:\n");
                           log_file_writer.write(content);

                           log_file_writer.println();
                           log_file_writer.println();




                       } else if (input.split(" ")[1].equalsIgnoreCase("/favicon.ico")) {
                           //ignore
                       } else {
                           String requested_filename = input.split(" ")[1].substring(1);
                           //System.out.println(requested_filename);
                           // String content = read_from_html_file(requested_filename);

                           String portion1 = "<html>\n" +
                                   "\t<head>\n" +
                                   "\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n" +
                                   "\t</head>\n" +
                                   "\t<body>\n";

                           //this file has the absolute path of the "requested file"
                           File Absolute_file = new File(Home_path+"/"+requested_filename);

                           System.out.println("Req file: "+requested_filename );
                           String portion2="";

                           //if requested URL is file then show the content or download
                           if(Absolute_file.isFile())
                           {
                              // System.out.println("A file");
                               if(Absolute_file.exists()) {
                                   if (requested_filename.endsWith("jpg") || requested_filename.endsWith("png") ||
                                           requested_filename.endsWith("jpeg")) {


                                       //sending image file chunk by chunk
                                       File image_file = new File(Home_path+"/"+requested_filename);

                                      // System.out.println(image_file.length());
                                       //System.out.println(image_file.getAbsolutePath());

                                       byte[] single_chunk = new byte[chunk_size];
                                       int count = 0;

                                       BufferedInputStream bis = new BufferedInputStream(new FileInputStream(image_file));

                                       OutputStream socket_out = socket.getOutputStream();

                                       //if a image file
                                       pr.write("HTTP/1.1 200 OK\r\n");
                                       pr.write("Server: Java HTTP Server: 1.0\r\n");
                                       pr.write("Date: " + new Date() + "\r\n");

                                       String MIME_type = Files.probeContentType(image_file.toPath());

                                       pr.write("Content-Type: "+MIME_type+"\r\n");
                                       pr.write("Content-Length: " + image_file.length() + "\r\n");
                                       pr.write("\r\n");
                                       pr.flush();
                                       // pr.write(content);


                                       //writing response to log file
                                       log_file_writer.println("HTTP Response");
                                       log_file_writer.println("--------------");
                                       log_file_writer.write("HTTP/1.1 200 OK\r\n");
                                       log_file_writer.write("Server: Java HTTP Server: 1.0\r\n");
                                       log_file_writer.write("Date: " + new Date() + "\r\n");
                                       log_file_writer.write("Content-Type: "+MIME_type+"\r\n");
                                       log_file_writer.write("Content-Length: " + image_file.length() + "\r\n");
                                       log_file_writer.write("\r\n");
                                       log_file_writer.write("Content: "+image_file.getAbsolutePath()+"\n");
                                       log_file_writer.println();
                                       log_file_writer.println();




                                       while((count = bis.read(single_chunk)) > 0)
                                       {
                                           socket_out.write(single_chunk, 0, count);
                                           socket_out.flush();
                                       }

                                   }

                                   else if(requested_filename.endsWith("txt")) //if a text file
                                   {

                                       String text_content = read_from_file(Home_path+"/"+requested_filename);

                                       portion2 = portion2 + "<large> "+text_content +"</large>\n";


                                   }

                                   else //for other files,file will be download
                                   {
                                       File other_file = new File(Home_path+"/"+requested_filename);

                                       pr.write("HTTP/1.1 200 OK\r\n");
                                       pr.write("Server: Java HTTP Server: 1.0\r\n");
                                       pr.write("Date: " + new Date() + "\r\n");
                                       //pr.write("Content-Type: text/html\r\n");
                                       //pr.write("Content-Length: " + fileCheck.length() + "\r\n");
                                       pr.write("Content-type: application/x-force-download" + "\r\n");
                                       pr.write("Content-Length: " + other_file.length() + "\r\n");
                                       pr.write("\r\n");
                                       pr.flush();


                                       //writing response to log file
                                       log_file_writer.println("HTTP Response");
                                       log_file_writer.println("--------------");

                                       log_file_writer.write("HTTP/1.1 200 OK\r\n");
                                       log_file_writer.write("Server: Java HTTP Server: 1.0\r\n");
                                       log_file_writer.write("Date: " + new Date() + "\r\n");
                                       log_file_writer.write("Content-type: application/x-force-download" + "\r\n");
                                       log_file_writer.write("Content-Length: " + other_file.length() + "\r\n");
                                       log_file_writer.write("\r\n");
                                       log_file_writer.write("Content: "+other_file.getAbsolutePath()+"\n");
                                       log_file_writer.println();
                                       log_file_writer.println();


                                       byte[] single_chunk = new byte[chunk_size];
                                       int count = 0;

                                       BufferedInputStream bis = new BufferedInputStream(new FileInputStream(other_file));

                                       OutputStream socket_out = socket.getOutputStream();

                                       //sending file chunk by chunk
                                       while((count = bis.read(single_chunk)) > 0)
                                       {
                                           socket_out.write(single_chunk, 0, count);
                                           socket_out.flush();
                                       }

                                   }
                               }
                               else
                               {
                                   System.out.println(requested_filename+": file Not found");
                                   throw new IllegalAccessException();
                               }


                           }

                           //if requested URL is directory then show the list of links
                           else //if curr_path is a Directory())
                           {
                               //System.out.println("A directory");
                               if(Absolute_file.exists())
                               {

                                   File[] files = Absolute_file.listFiles();

                                   for (int i=0;i<files.length;i++)
                                   {
                                       //  portion2 = portion2+" <li><a href =\""+files[i].getName()+"\"> "+files[i].getName()+" </a></li>\n";

                                       //creating link for directory ( normal font)
                                       if(files[i].isDirectory())
                                           portion2 = portion2+" <li><a href =\""+"/"+requested_filename+"/"+files[i].getName()+"\"> "+"<b><i>"+files[i].getName()+"</i></b>"+" </a></li>\n";

                                           //creating link for txt,jpg,png ( bold and italic font)
                                       else if(files[i].getName().endsWith("jpg") || files[i].getName().endsWith("jpeg") || files[i].getName().endsWith("png")
                                               ||files[i].getName().endsWith("txt"))
                                           portion2 = portion2+" <li><a href =\""+"/"+requested_filename+"/"+files[i].getName()+"\"> "+files[i].getName()+" </a></li>\n";

                                           //creating link for other files ( should be downloaded)
                                       else
                                           portion2 = portion2+" <li><a href =\""+"/"+requested_filename+"/"+files[i].getName()+"\"> "+files[i].getName()+" </a></li>\n";



                                   }



                               }else
                               {
                                   System.out.println(requested_filename+": file Not found");
                                   throw new IllegalAccessException();

                               }
                           }

                           String portion3 = "</body>\n" +
                                   "</html>";


                           if(Absolute_file.isDirectory() || requested_filename.endsWith("txt"))
                           {
                               String content = portion1 + portion2 + portion3;
                               //create_new_html_file(content, requested_filename);


                               pr.write("HTTP/1.1 200 OK\r\n");
                               pr.write("Server: Java HTTP Server: 1.0\r\n");
                               pr.write("Date: " + new Date() + "\r\n");
                               pr.write("Content-Type: text/html\r\n");
                               pr.write("Content-Length: " + content.length() + "\r\n");
                               pr.write("\r\n");
                               pr.write(content);
                               pr.flush();


                               //writing response to log file
                               log_file_writer.println("HTTP Response");
                               log_file_writer.println("--------------");

                               log_file_writer.write("HTTP/1.1 200 OK\r\n");
                               log_file_writer.write("Server: Java HTTP Server: 1.0\r\n");
                               log_file_writer.write("Date: " + new Date() + "\r\n");
                               log_file_writer.write("Content-Type: text/html\r\n");
                               log_file_writer.write("Content-Length: " + content.length() + "\r\n");
                               log_file_writer.write("\r\n");
                               log_file_writer.write("Content:\n");
                               log_file_writer.write(content);

                               log_file_writer.println();
                               log_file_writer.println();


                           }


                       }




                   }

                   else if(input.startsWith("UPLOAD"))
                   {
                       String uploading_file_name = input.split(" ")[1];

                       if(uploading_file_name.endsWith(".txt") || uploading_file_name.endsWith(".jpg") ||
                               uploading_file_name.endsWith(".png") || uploading_file_name.endsWith(".mp4") )
                       {
                           //Upload request is OK
                           //sending the response to client "OK" so that client can sen the file

                           pr.write("OK");
                           pr.write("\r\n");
                           pr.flush();

                           if(in.readLine().equalsIgnoreCase("Sending from client")) //if file exists in client side
                           {
                               String Upload_file_path = Home_path+"/uploaded file/"+uploading_file_name;
                               File in_file = new File(Upload_file_path);


                               byte[] single_chunk = new byte[1024];
                               int count = 0;


                               FileOutputStream fos = new FileOutputStream(in_file);
                               InputStream socket_in = socket.getInputStream();

                               //recieving file hunk by chunk
                               while((count = socket_in.read(single_chunk)) > 0)
                               {
                                   fos.write(single_chunk, 0, count);
                                   fos.flush();
                               }

                               System.out.println("File upload successful");
                           }

                           else {//if file does not exist in client
                               pr.write("File recieving failed");
                               pr.write("\r\n");
                               pr.flush();
                               System.out.println("File recieving failed");

                           }


                       }

                       else
                       {
                           System.out.println("Error: Invalid File name !!! Invalid uploading Request from client!!!");
                           pr.write("Error: Invalid File name !!! Invalid uploading Request from client!!!");
                           pr.write("\r\n");
                           pr.flush();
                       }


                   }

                   else
                   {


                       System.out.println("Error: Unformatted uploading Request from client!!!");
                       pr.write("Error: Invalid Request to server!!!");
                       pr.write("\r\n");
                       pr.flush();



                   }








               pr.close();
               in.close();
               socket.close();

           }


           catch (Exception e)
           {
               if(e instanceof IllegalAccessException) {
                   pr.write("HTTP/1.1 404 NOT FOUND\r\n");
                   pr.write("Server: Java HTTP Server: 1.0\r\n");
                   pr.write("Date: " + new Date() + "\r\n");
                   pr.flush();

                   log_file_writer.println("HTTP Response");
                   log_file_writer.println("--------------");

                   log_file_writer.write("HTTP/1.1 404 NOT FOUND\r\n");
                   log_file_writer.write("Server: Java HTTP Server: 1.0\r\n");
                   log_file_writer.write("Date: " + new Date() + "\r\n");

                   log_file_writer.println();
                   log_file_writer.println();



                   pr.close();
                   in.close();
                   socket.close();
               }

           }
       }


    catch (Exception e)
       {
           e.printStackTrace();
       }

    }


}
