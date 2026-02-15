package chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ClientReadThread extends Thread {

    private BufferedReader fromServer;
    private String userName;

    ClientReadThread(Socket server, String userName) {
        this.userName = userName;
        try {
            this.fromServer = new BufferedReader(new InputStreamReader(server.getInputStream()));
        } catch (IOException e) {
            System.err.println("Error getting input stream");
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (true) {
            try {
                String msg = this.fromServer.readLine();
                if(msg == null) {
                    System.err.println("\rServer closed");
                    break;
                }

                System.out.println("\r" + msg);

                System.out.printf("\r[%s]: ", this.userName);
            } catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }
    }
}
