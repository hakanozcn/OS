import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
public class server {
    
    public static void main(String args[]) throws IOException 
    {
        
        String inputtext;
        
        try(
        ServerSocket serversocket=new ServerSocket(1042);
        Socket serversocket1=serversocket.accept();
        
        PrintStream print=new PrintStream(serversocket1.getOutputStream());
        
        Scanner serverscanner=new Scanner(serversocket1.getInputStream());)
{
        
        while ((inputtext = serverscanner.next()) != null)
        {
          System.out.print("Data:");
	System.out.println(inputtext);
       
       
         System.out.print("Decrypted data:");
        print.println(cesar(inputtext,-3));
        System.out.println(cesar(inputtext,-3));
        
        serversocket.close();
        }}
catch (IOException ioe) {
			System.err.println(ioe);
		}
        
        
    }
  static  String cesar(String msg, int shift){
    String s = "";
    int len = msg.length();
    for(int x = 0; x < len; x++){
        char c = (char)(msg.charAt(x) + shift);
        if (c > 'z')
            s += (char)(msg.charAt(x) - (26-shift));
        else
            s += (char)(msg.charAt(x) + shift);
    }
    return s;
}
}