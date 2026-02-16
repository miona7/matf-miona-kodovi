package jan1_2023.zadatak3;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Server {
    public static final int PORT = 12345;
    public static final int BUFFER_SIZE = 1024;

    private static final String SONGS_FILE = "/home/miona/IdeaProjects/ispiti/src/jan1_2023/zadatak3/trending_songs.txt";
    private static final List<String> SONGS = new ArrayList<>();

    public static void main(String[] args) {
        loadSongs();

        try (DatagramSocket serverSocket = new DatagramSocket(PORT)) {

            int globalIndex = 0;
            byte[] buffer = new byte[BUFFER_SIZE]; // za primanje zahteva od klijenta
            byte[] responseBuffer; // za slanje odgovora

            while (true) {
                DatagramPacket clientRequest = new DatagramPacket(buffer, BUFFER_SIZE);
                serverSocket.receive(clientRequest);

                String requestedIndex = (new String(clientRequest.getData(), 0, clientRequest.getLength(), StandardCharsets.UTF_8)).trim();
                // System.out.println("Requested index " + requestedIndex);

                if (requestedIndex.equals("-1")) {
                    String responseSong = SONGS.get(globalIndex);
                    globalIndex = (globalIndex + 1) % SONGS.size();
                    // System.out.println("Response: " + responseSong);

                    responseBuffer = responseSong.getBytes(StandardCharsets.UTF_8);
                    DatagramPacket responsePacket = new DatagramPacket(responseBuffer, responseBuffer.length, clientRequest.getAddress(), clientRequest.getPort());

                    serverSocket.send(responsePacket);
                } else {
                    int index = Integer.parseInt(requestedIndex);
                    if (index >= SONGS.size()) {
                        index = globalIndex;
                        globalIndex = (globalIndex + 1) % SONGS.size();
                    }

                    String responseSong = SONGS.get(index);
                    // System.out.println("Response: " + responseSong);

                    responseBuffer = responseSong.getBytes(StandardCharsets.UTF_8);
                    DatagramPacket responsePacket = new DatagramPacket(responseBuffer, responseBuffer.length, clientRequest.getAddress(), clientRequest.getPort());

                    serverSocket.send(responsePacket);
                }
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
    }

    private static void loadSongs() {
        try (Scanner in = new Scanner(new File(SONGS_FILE))) {
            while (in.hasNextLine()) {
                SONGS.add(in.nextLine());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}