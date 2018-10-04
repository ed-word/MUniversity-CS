import java.util.*;
import java.io.*;
import java.security.MessageDigest;


class CustomEncryption {
    public static String esc = "~~";

    public static String Encrypt(String pt, int k[]) {
        int scaleKey;
        int n;
        String ct = "";

        String hashValue = getHash(pt);
        System.out.println("Message Digest: " + hashValue);

        ct += hashValue;
        ct += esc;
        ct += pt;

        n = ct.length();
        System.out.println("length: " + n);        

        char[] ctArr = ct.toCharArray();
        double scale = n / 10;
        for (int i = 0; i < k.length; i++) {
            scaleKey = (int)(k[i] * scale);
            int index = 0;
            for (int j = 0; j < scaleKey; j++) {
                index += scaleKey;
                for (int m = 0; m < k.length; m++) {
                    ctArr[(index+m) % ctArr.length] += scaleKey;
                    ctArr[(index+m) % ctArr.length] %= 256;
                }
            }
        }

        return String.valueOf(ctArr);
    }

    public static String Decrypt(String ct, int k[]) {
        int n = ct.length(), scaleKey;
        String pt = "";
        System.out.println("length: " + n);
        
        double scale = n / 10;
        char[] ctArr = ct.toCharArray();
        for (int i = 0; i < k.length; i++) {
            scaleKey = (int)(k[i] * scale);
            int index = 0;
            for (int j = 0; j < scaleKey; j++) {
                index += scaleKey;
                for (int m = 0; m < k.length; m++) {
                    ctArr[(index+m) % ctArr.length] -= scaleKey;
                    ctArr[(index+m) % ctArr.length] %= 256;
                }
            }
        }
        ct = String.valueOf(ctArr);

        for (int i = 0; i < ct.length(); i++) {
            if (ct.charAt(i) == '~' && ct.charAt(i) == ct.charAt(i-1)) {
                String hashValue = ct.substring(0, i-1);
                System.out.println("Message Digest: " + hashValue);
                pt = ct.substring(i+1, n);
                System.out.println("Hash of message: " + getHash(pt));
                System.out.println("Is Message Digest equal to Hash? " + hashValue.equals(getHash(pt)));
                break;
            }
        }    

        return pt;
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
        String pt = "", ct;
        int[] k = new int[]{3, 1, 2, 7, 5, 2, 8, 4, 9, 6, 7}; 
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter plaintext: ");        
        pt = sc.nextLine(); 

        System.out.println("\nEncrypting");
        ct = Encrypt(pt, k);
        System.out.println("Cipher text: " + ct);

        System.out.println("\nDecrypting");
        pt = Decrypt(ct, k);
        System.out.println("Plain text: " + pt);
    }
}
