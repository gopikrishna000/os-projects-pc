import java.io.*;
import java.net.*;

public class FileServer {

    public static void main(String[] args) throws IOException {
        int filesize=6022386; // 

        long start = System.currentTimeMillis();
        int bytesRead;
        int current = 0;

       
        ServerSocket servsock = new ServerSocket(1149);
        while (true) {
          System.out.println("Waiting...");

          Socket sock = servsock.accept();
          System.out.println("Accepted connection hear : " + sock);

       // receive file
            byte [] mybytearray  = new byte [filesize];
            InputStream is = sock.getInputStream();
            FileOutputStream fos = new FileOutputStream("C:\\demo.jpg"); // 
            BufferedOutputStream bos = new BufferedOutputStream(fos);
            bytesRead = is.read(mybytearray,0,mybytearray.length);
            current = bytesRead;

            // thanks to dhaval solanki
            do {
               bytesRead =
                  is.read(mybytearray, current, (mybytearray.length-current));
               if(bytesRead >= 0) current += bytesRead;
            } while(bytesRead > -1);

            bos.write(mybytearray, 0 , current);
            bos.flush();
            long end = System.currentTimeMillis();
            System.out.println(end-start);
            bos.close();
          sock.close();
          }
    }

}