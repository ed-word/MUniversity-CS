import java.io.*;
import java.net.*;
import java.math.BigInteger;

public class ClientDH { 
    // initialize socket and input output streams 
    private Socket socket            = null; 
    private DataInputStream  inputSys   = null;
    private DataInputStream  inputSoc   = null; 
    private DataOutputStream out     = null; 
  
    // constructor to put ip address and port 
    public ClientDH(String address, int port) 
    {
        int g = 3, n = 7, x = 4, y, a, b=2, k1, k2;
        // establish a connection 
        try
        { 
            socket = new Socket(address, port); 
            System.out.println("Connected"); 
  
            // takes input from terminal 
            inputSys  = new DataInputStream(System.in);
            inputSoc = new DataInputStream(new BufferedInputStream(socket.getInputStream())); 
            // sends output to the socket 
            out    = new DataOutputStream(socket.getOutputStream()); 
        } 
        catch(UnknownHostException u) 
        { 
            System.out.println(u); 
        } 
        catch(IOException i) 
        { 
            System.out.println(i); 
        } 
        
        // string to read message from input 
        String line = "";


        try { 
            g = 3;
            n = 7;
            out.writeUTF(Integer.toString(g));
            out.writeUTF(Integer.toString(n)); 
        } catch(IOException i) { 
            System.out.println(i); 
        }
        

        a = (int)Math.pow(g,x) % n;
        System.out.println("a: " + a);
        try { 
            out.writeUTF(Integer.toString(a));
        } catch(IOException i) { 
            System.out.println(i); 
        }


        try
            { 
                b = Integer.parseInt(inputSoc.readUTF());
                System.out.println("b: " + b);
            } 
            catch(IOException i) 
            { 
                System.out.println(i); 
            } 


        k1 = (int)Math.pow(b, x) % n;
        System.out.println("k1: " + k1);

        // close the connection 
        try
        { 
            inputSys.close();
            inputSoc.close(); 
            out.close(); 
            socket.close(); 
        } 
        catch(IOException i) 
        { 
            System.out.println(i); 
        } 
    } 
  
    public static void main(String args[]) 
    { 
        ClientDH client = new ClientDH("127.0.0.1", 5000);
    }
} 
    
    
    

