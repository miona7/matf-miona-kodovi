import java.io.*;
import java.net.Socket;

public class Client {
    public static void main(String[] args) {
        String host = "localhost";
        System.out.println("Connecting to " + host);
        try (Socket client = new Socket(host, Server.PORT)) {
            System.out.println("Connected to " + host);
            try (BufferedReader br = new BufferedReader(new InputStreamReader(client.getInputStream()))) {
                String time = br.readLine();
                System.out.println(time);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
