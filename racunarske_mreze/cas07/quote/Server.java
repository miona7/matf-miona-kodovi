package quote;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Server {
    public static final int PORT = 5050;
    public static final int BUFF_SIZE = 1024;
    private static final String QUOTES_FILE = "/home/miona/IdeaProjects/cas6/src/quote/liners.txt";
    private static final List<String> QUOTES = new ArrayList<>();

    public static void main(String[] args) {
        loadQuotes();

        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            byte[] responseBytes;
            byte[] buffer = new byte[BUFF_SIZE];
            Random r =  new Random();

            while (true) {
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                socket.receive(request);

                String response = QUOTES.get(r.nextInt(QUOTES.size()));
                responseBytes = response.getBytes(StandardCharsets.UTF_8);
                DatagramPacket responsePacket = new DatagramPacket(responseBytes, responseBytes.length, request.getAddress(), request.getPort());
                socket.send(responsePacket);
            }

        } catch (SocketException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void loadQuotes() {
        try (Scanner file = new Scanner(new BufferedInputStream(new FileInputStream(QUOTES_FILE)))) {
            while (file.hasNextLine()) {
                QUOTES.add(file.nextLine());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
