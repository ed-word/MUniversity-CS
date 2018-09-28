import java.net.*; 
import java.io.*; 
  
public class ServerDH { 
    //initialize socket and input stream 
    private Socket          socket   = null; 
    private ServerSocket    server   = null; 
    private DataInputStream inputSys =  null;
    private DataInputStream inputSoc =  null;
    private DataOutputStream out     = null;
  
    // constructor with port 
    public ServerDH(int port) 
    {
    	int g = 3, n = 7, x, y = 6, a=2, b, k1, k2;
        // starts server and waits for a connection 
        try
        { 
            server = new ServerSocket(port); 
            System.out.println("Server started"); 
  
            System.out.println("Waiting for a client ..."); 
  
            socket = server.accept(); 
            System.out.println("Client accepted"); 
  
            inputSys  = new DataInputStream(System.in);
            inputSoc = new DataInputStream( 
                new BufferedInputStream(socket.getInputStream())); 
  
            // sends output to the socket 
            out    = new DataOutputStream(socket.getOutputStream());
  
            String line = ""; 
  				
            // reads message from client until "Over" is sent  
            try
            { 
                g = Integer.parseInt(inputSoc.readUTF());
                n = Integer.parseInt(inputSoc.readUTF()); 
                System.out.println("g: "+ g);
                System.out.println("n: " + n);
            } 
            catch(IOException i) 
            { 
                System.out.println(i); 
            } 


            b = (int)Math.pow(g,y) % n;
            System.out.println("b: " + b);
            try { 
            out.writeUTF(Integer.toString(b));
        } catch(IOException i) { 
            System.out.println(i); 
        }


        try
            { 
                a = Integer.parseInt(inputSoc.readUTF());
                System.out.println("a: " + a);
            } 
            catch(IOException i) 
            { 
                System.out.println(i); 
            }
        	
        k2 = (int)Math.pow(a, y) % n;
        System.out.println("k2: " + k2);

            System.out.println("Closing connection"); 
  
            // close connection 
            socket.close(); 
            inputSys.close();
            inputSoc.close(); 
        } 
        catch(IOException i) 
        { 
            System.out.println(i); 
        } 
    } 
  
    public static void main(String args[]) 
    { 
        ServerDH server = new ServerDH(5000); 
    } 
}