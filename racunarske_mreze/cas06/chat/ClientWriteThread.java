package chat;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class ClientWriteThread extends Thread {

    private PrintWriter toServer;
    private final String userName;

    ClientWriteThread(Socket socket, String userName) {
        this.userName = userName;
        try {
            toServer = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            System.err.println("Error opening output stream");
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        // prvo saljemo ime serveru

        this.toServer.println(this.userName);

        // saljemo ostale poruke
        try (Scanner in = new Scanner(System.in)) {
            String text;
            do {
                System.out.printf("\r[%s]: ", this.userName);
                text = in.nextLine();
                toServer.println(text);
            } while (!text.equalsIgnoreCase("bye"));
        }
    }
}
