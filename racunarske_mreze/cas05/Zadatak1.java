import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Date;

public class Zadatak1 {
    public static void main(String[] args) {
        String host = "localhost";
        // String host = "www.matf.bg.ac.rs";

        System.out.println("Start time: " + new Date());

        for(int port = 1; port < 65536; ++port) {
            System.out.printf("\rTesting port %5d", port);
            try (Socket s = new Socket(host, port)) {
                System.out.println("\rSocket data " + s);
                System.out.println("Found at " + new Date());
            } catch (UnknownHostException e) {
                e.printStackTrace();
                break;
            } catch (IOException e) {
                // ignorisi jer ne postoji server na zadatom hostu i idemo dalje
            }
        }

        System.out.println("\rEnd time: " + new Date());
    }
}
