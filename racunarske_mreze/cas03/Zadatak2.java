import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class Zadatak2 {
    public static void main(String[] args) {
        // ako ukucamo host name dobijamo ip adresu i obrnuto

        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println("After lookup we get " + lookup(line));
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }

    }

    private static String lookup(String line) throws UnknownHostException {
        InetAddress address = InetAddress.getByName(line);
        if (isHostName(line)) {
            return address.getHostAddress();
            // return "hostname";
        } else {
            return address.getHostName();
        }
    }

    private static boolean isHostName(String line) {
        // regex . je specijalni karakter pa mora eskejp
        if (line.split("\\.").length != 4) {
            return true;
        }

        return line.chars().anyMatch(c -> !Character.isDigit(c) && c != '.' );
    }
}
