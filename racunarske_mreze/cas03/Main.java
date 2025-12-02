import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Arrays;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        InetAddress address;

        // IPv4 adresa
        Inet4Address address4;

        // Ipv6 adresa
        Inet6Address address6;

        // System.out.println("bla");

        try {
            address = InetAddress.getByName("google.com"); // od host name-a dobijemo inet adresu
            System.out.println(address);  // ispisujemo adresu
            System.out.println(address.getHostName()); // ispisujemo ime
            System.out.println(Arrays.toString(address.getAddress())); // dobijamo niz od 4 bajta  - potpuni komplement do pola pozitivni, od pola negativni

            InetAddress oldMatf =  InetAddress.getByName("old.matf.bg.ac.rs");
            InetAddress oldMath =  InetAddress.getByName("old.math.rs");

            // ukazuju na istu adresu
            System.out.println(oldMatf);
            System.out.println(oldMath);

            // vraca niz svih ip adresa koje su dodeljene imenu
            System.out.println(Arrays.toString(InetAddress.getAllByName("google.com")));

            // pristupamo ipv6 varijanti
            address6 = (Inet6Address) InetAddress.getByName("ipv6.google.com");
            System.out.println(address6);

            // prvo trazi lokalno, pa onda globalno
            System.out.println(InetAddress.getByName("142.251.208.110").getHostName());

        } catch (UnknownHostException e) {
            System.out.println(e.getMessage());
        }

    }
}