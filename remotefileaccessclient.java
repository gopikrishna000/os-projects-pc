// File Name GreetingServer.java

import java.net.*;
import java.io.*;


public class remotefileaccessclient extends Thread
{

  public static Socket socket ;

   public remotefileaccessclient(int port) throws IOException
   {
       Socket socket =new Socket("localhost",8080);
    // serverSocket = new ServerSocket(port);
    // serverSocket.setSoTimeout(50000);
   }
   

public void run()
{
     try
     {
     
        System.out.println("Just connected to "
              + socket.getRemoteSocketAddress());

              System.out.println("FF");
     
        

      // try{
      //   this.sleep(5000);
      // }
      // catch(InterruptedException e){
      //    System.out.println("interrupt time\n");
      // }
      System.out.println("dFF");
      System.out.println("dhFF");
      
      BufferedReader in =
      new BufferedReader(new InputStreamReader(socket.getInputStream(),"UTF-8"));
      String msg;
     while( (msg =in.readLine() )!=null && socket.isConnected())
     System.out.println(msg);
     
     System.out.println("dFFyh");
     System.out.flush();

      //  socket.close();
     }catch(SocketTimeoutException s)
     {
        System.out.println("Socket timed out!");
      
     }catch(IOException e)
     {
        e.printStackTrace();
      
     }
}



public static void main(String [] args)
{
  int port = 8080;
 
  try
  {
   socket =new Socket("localhost",8080);
   System.out.println("0 - Exit , 1- Create new file,2 - Create Directory, 3 - Read Files and Subdirectories, 4 - Create Non-deletable Directory, 5 - Delete Empty Directory\n");
     
   Thread t = new remotefileaccessclient(port);
     t.start();

     try{
      String qry ="3\n./\n1\nhello.mp4\n3\n./\n";
      
      PrintWriter out =
      new PrintWriter(socket.getOutputStream());
 out.println(qry);
   out.flush();

      
     //    byte[] bytestring ;
   //   bytestring= in.readLine();
   //   String msg = new String(bytestring, "UTF-8") ; 
   //   System.out.println(msg);
   }catch(EOFException E){
      System.out.println("EOF\n");
   }

  }catch(IOException e)
  {
     e.printStackTrace();
  }
 }
}