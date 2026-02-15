package chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client {
    public static void main(String[] args) {
        String hostname = "localhost";
        Client client = new Client(hostname, Server.PORT);
        client.execute();
    }

    private final String hostName;
    private final int port;
    private String userName;

    Client(String hostName, int port) {
        this.hostName = hostName;
        this.port = port;
    }

    void execute() {
        try {
            this.setName();

            try (Socket socket = new Socket(this.hostName, this.port);) {
                System.out.println("Connected to " + this.hostName + ":" + this.port);

                // niti potrebne klijentu
                // za citanje poruka koje dobija od servera
                ClientReadThread rt = new ClientReadThread(socket, this.userName);
                rt.start();

                // za slanje poruka serveru
                ClientWriteThread wt = new ClientWriteThread(socket, this.userName);
                wt.start();

                rt.join();
                wt.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void setName() throws IOException {
        System.out.print("Enter your name: ");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        this.userName = br.readLine();
    }
}
