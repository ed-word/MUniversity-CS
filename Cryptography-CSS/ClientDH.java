import java.io.*;
import java.net.*;


public class ClientDH { 
    private Socket socket = null; 
    private DataInputStream inputSys = null;
    private DataInputStream inputSoc = null; 
    private DataOutputStream out = null; 
  
    public ClientDH(String address, int port) {
        int g = 3, n = 7, x = 4, y, a, b=2, k1, k2;
        try { 
            socket = new Socket(address, port); 
            System.out.println("Connected"); 
  
            inputSys  = new DataInputStream(System.in);
            inputSoc = new DataInputStream(new BufferedInputStream(socket.getInputStream())); 
            
            out    = new DataOutputStream(socket.getOutputStream()); 
        } catch(UnknownHostException u) { 
            System.out.println(u); 
        } catch(IOException i) { 
            System.out.println(i); 
        } 
        
        String line = "";

        try { 
            g = 3;
            n = 7;
            out.writeUTF(Integer.toString(g));
            out.writeUTF(Integer.toString(n)); 
        } catch(IOException i) { 
            System.out.println(i); 
        }
        System.out.println("Sending (g, n): " + g + ", " + n);
        

        a = (int)Math.pow(g,x) % n;
        System.out.println("Sending a: " + a);
        try { 
            out.writeUTF(Integer.toString(a));
        } catch(IOException i) { 
            System.out.println(i); 
        }


        try {
            b = Integer.parseInt(inputSoc.readUTF());
        } catch(IOException i) { 
            System.out.println(i); 
        }
        System.out.println("Received b: " + b);


        k1 = (int)Math.pow(b, x) % n;
        System.out.println("k1: " + k1);

        try { 
            inputSys.close();
            inputSoc.close(); 
            out.close(); 
            socket.close(); 
        } catch(IOException i) { 
            System.out.println(i); 
        } 
    } 
  
    public static void main(String args[]) { 
        ClientDH client = new ClientDH("127.0.0.1", 5000);
    }
}
