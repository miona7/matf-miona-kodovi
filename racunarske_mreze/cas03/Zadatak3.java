import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

public class Zadatak3 {
    public static void main(String[] args) {
        // loopback sluzi kao konektor za jednu mrezu koju mozemo da simuliramo na jednom racunaru

        InetAddress loopbackAddress = InetAddress.getLoopbackAddress(); // specijalna adresa za komunikaciju uredjaja sa samim sobom
        try {
            NetworkInterface ni = NetworkInterface.getByInetAddress(loopbackAddress);
            System.out.println(ni.getDisplayName());
            System.out.println(ni.getName());

            Enumeration<InetAddress> addresses = ni.getInetAddresses();
            while (addresses.hasMoreElements()) {
                System.out.println(addresses.nextElement());
            }
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
    }
}
