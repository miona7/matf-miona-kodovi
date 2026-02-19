package numberGuesser;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadLocalRandom;

public class Server {
    public static final int PORT = 12321;

    public static void main(String[] args) {
        try (ServerSocket socket = new ServerSocket(PORT)) {
            while (true) {
                Socket client = socket.accept();
                new Thread(() -> proccessClient(client)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void proccessClient(Socket client) {
        try (BufferedReader readFromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
             BufferedWriter writeToClient = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))) {

            int number = ThreadLocalRandom.current().nextInt(1, 101);

            writeToClient.write("Pogodi koji broj od 1 do 100 sam zamislio\n");
            writeToClient.flush();

            while (true) {
                try {
                    int answer = Integer.parseInt(readFromClient.readLine());

                    if (answer == number) {
                        writeToClient.write("Cestitam! Pogodili ste broj!\n");
                        writeToClient.flush();
                        break;
                    }

                    if (answer < number) {
                        writeToClient.write("Zamisljeni broj je veci od toga\n");
                        writeToClient.flush();
                    }

                    if (answer > number) {
                        writeToClient.write("Zamisljeni broj je manji od toga\n");
                        writeToClient.flush();
                    }

                }  catch (NumberFormatException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
