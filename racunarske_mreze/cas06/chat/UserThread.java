package chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class UserThread extends Thread {
    private final Server server;
    private final Socket client;
    private BufferedReader fromUser;
    private PrintWriter toUser;
    private String userName;

    UserThread(Socket client, Server server) {
        this.client = client;
        this.server = server;

        try {
            this.fromUser = new BufferedReader(new InputStreamReader(client.getInputStream()));
            this.toUser = new PrintWriter(this.client.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        try {
            // procitamo ime novog korisnika
            this.userName = this.fromUser.readLine();
            System.out.println("Connected users: " + server.getUsers());
            // System.out.println("User " + this.userName + " connected");

            // obavestimo sve ostale da imamo novog korisnika
            this.server.broadcast(this, "New user connected " + this.userName);

            // obradjujemo klijenta
            String clientMessage;
            do {
                clientMessage = this.fromUser.readLine();
                // vesna k.... raspala -> pukla veza
                if (clientMessage == null) {
                    break;
                }

                // saljemo poruku svim ostalim klijentima
                this.server.broadcast(this, "[" + this.userName + "]: "  + clientMessage);

            } while (!clientMessage.equalsIgnoreCase("bye"));

            // obavestavamo sve klijente da je klijent napustio caskanje
            this.server.broadcast(this, this.userName + " has left the chat :(");

        } catch (IOException e) {
            System.err.printf("Error in user thread: [%2d]" + Thread.currentThread().getId());
            e.printStackTrace();
        } finally {
            // izbacujemo klijenta iz skupa
            this.server.remove(this);

            // zatvaramo soket
            try {
                this.client.close();
            } catch (IOException e) {}
        }
    }

    String getUserName() {
        return this.userName;
    }

    void sendMessage(String message) {
        this.toUser.println(message);
    }
}
