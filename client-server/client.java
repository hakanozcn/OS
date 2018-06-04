import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;
public class client {
    
    public static void main(String args[]) throws IOException
    {
try
(
       
       
        Scanner scanner=new Scanner(System.in);
        Socket socket=new Socket("Localhost",1042);
        Scanner clientscanner=new Scanner(socket.getInputStream());
        PrintStream print=new PrintStream(socket.getOutputStream());)
{
 String text;
        while ((text = scanner.next()) != null) {
				// Girdiyi sokete yazma
                                System.out.print("Data:");
                                System.out.println(text);
				print.println(text);

				// Cevabý ekrana yazdýrma
                                System.out.print("Decrypted data:");
				System.out.println(clientscanner.next());
			}
       
        
        
         socket.close();
        }
        catch (IOException ioe) {
			System.err.println(ioe);
		}
       
    }
}