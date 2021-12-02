import java.io.*;
import java.net.*;
import java.util.Scanner;


public class FilesharingServer {
    
    private static PrintWriter remoteOut;
    private static BufferedInputStream remoteIn;
    private static BufferedOutputStream bos;
    private static FileOutputStream fos;
    private static Socket socket;
    private static ServerSocket serversocket;
    private static final Scanner sc = new Scanner(System.in);
    private static String filename;
    private static int filesize;

    public static void main(String[] args) {
      //  System.out.print("Enter username : ");
       // String username = sc.next();
     while(true){
        if (!connect()) return;  
    
        //  Printing incoming messages
    ///    Thread incomingFilesHandlingThread = new Thread(() -> {
            try{
      ///      byte[] bytestring = new byte[100];
            int byteread=0;
            while(byteread!=100){
                byte[] byt = new byte[4];
                int cnt =remoteIn.read(byt);
                byteread +=cnt;
                filename += (new String(byt, "UTF-8"));
            }
filename = filename.trim().replaceAll("^\\x00*","") ;  //regex , for remobing printing of "null" at beginning;
System.out.println(filename+'\n');
System.out.flush();
          ///  remoteIn.read(bytestring,0,100);
          ///  filename = new String(bytestring, "UTF-8") ; 

          //  remoteIn.readLine();

          //byte array size 1, because it is not easy to concatate bytes and remove null byte in betweeen
          byte[] byteint =new byte[4];
           int i=0;
            while(i!=4){
                byte[] byt = new byte[1];
                int cnt =remoteIn.read(byt);
                if(cnt==1){
                byteint[i] = byt[0] ;
                 i=i+1;
                }      
            }
       
    ///        remoteIn.read(byteint,0,4);
            filesize = byteArrayToInt(byteint);
System.out.println(filename+'\n'+filesize);

           // filesize = Integer.parseInt(remoteIn.readLine());
            } catch (IOException i){
                System.out.println(i.getMessage()+"Disconnected From Server");
            }

            try {
                if (socket.isConnected()){
                    File file =new File(("C:\\android_files\\"+filename).trim());      
                      System.out.println(filename+';'+filesize); 
                    
               /*       if( file.mkdir()){
                        System.out.println("created\n");
                    }
                     else{
                       System.out.println("not created\n");
                     } */
             

System.out.println("C:\\android_files\\"+filename);
                      fos = new FileOutputStream(("C:\\android_files\\"+filename).trim());                         
                      System.out.println(filename+'\n'+filesize);
                      bos = new BufferedOutputStream(fos);
                  /*    byte[] buf = new byte[filesize];                      
                      int Size = remoteIn.read(buf,0,filesize);  
                      System.out.println("read file from android");                                                                
                      bos.write(buf,0,filesize);
                      System.out.println("writen to file");
                      bos.flush();    */

                ///      int count;
                            byte[] file_byte = new byte[1024];

            int byteread=0;
            while(byteread!=filesize){               
                int count =remoteIn.read(file_byte);
                byteread +=count;
                bos.write(file_byte,0,count);
                bos.flush();   
            }

            /*
                            while((count =remoteIn.read(file_byte)) > 0){
                                bos.write(file_byte,0,count);
                                 bos.flush();   
                            }   */


                      remoteOut.println("END");
bos.close();
System.out.println("file closed");
                  //    while(true);

                      remoteIn.close();
                      bos.close();
                      socket.close();
                      serversocket.close();

             /*       String temp =remoteIn.readLine();
                   if(temp != null) 
                       System.out.println("\n| "+filename+ ": "+temp);
                else{
                    System.out.println("Disconnected From Server");
                    socket.close();
                    sc.close();
                    break;
                }  */
                }
            } catch (IOException e) {
                System.out.println(e.getMessage()+"  Disconnected From Server " );
                e.printStackTrace();
            }
 ///       });

    ///    incomingFilesHandlingThread.start();

    }
}

    private static boolean connect() {

        
        try {
            serversocket = new ServerSocket(8010);
            System.out.println("Listening at port 8010 \n Waiting for client ... ");            
            socket =serversocket.accept();
            remoteOut = new PrintWriter(socket.getOutputStream(), true);
            remoteIn = new BufferedInputStream(socket.getInputStream());
            System.out.println("Connected To a client! ");
           // remoteOut.println(serverName); // Sending Server Name as the first message
            return true;
        } catch (IOException e) {
            System.out.println("Connection To Server Failed  ");
            e.printStackTrace();
            return false;
        }
    }


    public static int byteArrayToInt(byte[] b) {
                return   b[3] & 0xFF |
                        (b[2] & 0xFF) << 8 |
                        (b[1] & 0xFF) << 16 |
                        (b[0] & 0xFF) << 24;
            }

}
