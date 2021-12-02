// File Name GreetingServer.java

import java.net.*;
import java.io.*;


public class hetroserver extends Thread
{
private ServerSocket serverSocket;

public hetroserver(int port) throws IOException
{
  serverSocket = new ServerSocket(port);
  serverSocket.setSoTimeout(50000);
}

public void run()
{
  while(true)
  {
     try
     {
        System.out.println("Waiting for client on port " +
        serverSocket.getLocalPort() + "...");
        Socket server = serverSocket.accept();
        System.out.println("Just connected to "
              + server.getRemoteSocketAddress());
        BufferedReader in =
              new BufferedReader(new InputStreamReader(server.getInputStream(),"UTF-8"));

      // try{
      //   this.sleep(5000);
      // }
      // catch(InterruptedException e){
      //    System.out.println("interrupt time\n");
      // }
      System.out.println("dFF");
      try{
         System.out.println("dhFF");
        System.out.println(in.readLine());
        System.out.println("dFFyh");
        System.out.flush();
        //    byte[] bytestring ;
      //   bytestring= in.readLine();
      //   String msg = new String(bytestring, "UTF-8") ; 
      //   System.out.println(msg);
      }catch(EOFException E){
         System.out.println("EOF\n");
      }

        System.out.println("FF");
        PrintWriter out =
             new PrintWriter(server.getOutputStream());
        out.println("Thank you for connecting to "
          + server.getLocalSocketAddress() + "\nGoodbye!");
          out.flush();
        server.close();
     }catch(SocketTimeoutException s)
     {
        System.out.println("Socket timed out!");
        break;
     }catch(IOException e)
     {
        e.printStackTrace();
        break;
     }
  }
}
public static void main(String [] args)
{
  int port = 8080;
  try
  {
     Thread t = new hetroserver(port);
     t.start();
  }catch(IOException e)
  {
     e.printStackTrace();
  }
 }
}