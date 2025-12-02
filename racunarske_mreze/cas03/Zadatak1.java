import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;

public class Zadatak1 {
    public static void main(String[] args) {
        // unosi nam se adresa, ispisujemo da li je ipv4 ili ipv6

        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = br.readLine()) != null) {
                InetAddress address = InetAddress.getByName(line);
                System.out.println("Ip version of " + line + " is: " + getVersion(address) + " with ip address: "  + address); // printAddress(address));
            }
        } catch (IOException io) {
            System.err.println(io.getMessage());
        }
    }

    // ne radi kako treba
    private static String printAddress(InetAddress address) {
        StringBuilder sb = new StringBuilder();
        for (byte b : address.getAddress()) {
            sb.append((b + 256) % 256).append(".");
        }
        return sb.toString();
    }

    private static String getVersion(InetAddress address) {
//        if (line.contains(".")) {
//            return "ipv4";
//        }
//        if (line.contains(":")) {
//            return "ipv6";
//        }
//        return "unknown";

        // getAddress vraca niz bajtova adrese
        if (address.getAddress().length == 4) {
            return  "ipv4";
        }

        if (address.getAddress().length == 16) {
            return  "ipv6";
        }

        return "unknown";
    }
}
