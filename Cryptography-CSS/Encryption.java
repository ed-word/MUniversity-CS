import java.util.*;
import java.io.*;
import java.security.MessageDigest;


class Encryption {
    public static String Encrypt(String pt) {
        return pt;
    }

    public static String Decrypt(String ct) {
        return ct;
    }

    public static String getHash(String data) {
        String result = null;
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(data.getBytes("UTF-8"));
            return Base64.getEncoder().encodeToString(hash);
        }catch(Exception ex) {
            ex.printStackTrace();
        }
        return result;
    }

    public static void main(String[] args) {
        String pt = "", ct, k;
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter plaintext: ");        
        pt = sc.next(); 

        String hashValue = getHash(pt);
        System.out.println("Hash Value: " + hashValue);

        ct = Encrypt(pt);
        System.out.println("Cipher text: " + ct);

        pt = Decrypt(ct);
        System.out.println("Plain text: " + pt);
    }
}
