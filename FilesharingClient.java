import java.io.*;
import java.net.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class FilesharingClient {

private static OutputStream os;
private static String filename;
private static BufferedInputStream bis;


     public static void main(String[] args) {
        Socket socket;
        try {
            socket = new Socket("localhost",8010);
      
        filename = "apowermirror.exe";
        try{
        File myfile =new File("C:\\EXE\\apowermirror.exe");
        System.out.println(myfile.length());

        bis = new BufferedInputStream(new FileInputStream("C:\\EXE\\apowermirror.exe"));
        int filesize = bis.available();
        byte[] b = new byte[100];
        filename = new String("hello.ppt");
        System.arraycopy(filename.getBytes(StandardCharsets.UTF_8 ), 0, b, 0, 9);
     //   System.arraycopy(filename.getBytes(Charset.forName("UTF-8")), 0, b, 0, filename.length());        
        os = socket.getOutputStream();                        
        os.write(b,0,100);
        byte[] s = intToByteArray(filesize);
        os.write(s,0,4);

        byte[] filebyte = new byte[filesize];
        bis.read(filebyte,0,filesize);
        os.write(filebyte,0,filesize);
        os.flush();


        bis.close();
        socket.close();
        }
        catch(IOException ignore ){
          bis.close();
        }     

    //    socket.close();

    } catch (UnknownHostException e) {
            
    } catch (IOException e) {
       System.out.println(e.getMessage());
     //   e.getStackTrace();
    }
    
    }


    
public static byte[] intToByteArray(int a)
{
    return new byte[] {
        (byte) ((a >> 24) & 0xFF),
        (byte) ((a >> 16) & 0xFF),   
        (byte) ((a >> 8) & 0xFF),   
        (byte) (a & 0xFF)
    };
}



}

