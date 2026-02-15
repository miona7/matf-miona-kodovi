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

    private static final List<String> SONGS = new ArrayList<>();

    public static void main(String[] args) {
        loadSongs();

        try (DatagramSocket serverSocket = new DatagramSocket(PORT)) {

            int globalIndex = 0;

            while (true) {
                byte[] buffer = new byte[BUFFER_SIZE];
                DatagramPacket clientRequest = new DatagramPacket(buffer, BUFFER_SIZE);
                serverSocket.receive(clientRequest);

                String request = (new String(clientRequest.getData(),
                        0,
                        clientRequest.getLength(),
                        StandardCharsets.UTF_8)).trim();
                if (request.equals("-1")) {
                    byte[] response = SONGS.get(globalIndex).getBytes(StandardCharsets.UTF_8);
                    DatagramPacket responsePacket = new DatagramPacket(response, response.length, clientRequest.getAddress(), clientRequest.getPort());
                    serverSocket.send(responsePacket);
                    globalIndex = (globalIndex + 1) % SONGS.size();
                } else {
                    String[] command = request.split(" ");
                    String commandName = command[0].trim();
                    if (commandName.equals("next") && command.length == 2) {
                        int index = Integer.parseInt(command[1]);
                        if (index == -1 || index >= SONGS.size()) {
                            index = globalIndex;
                            globalIndex = (globalIndex + 1) % SONGS.size();
                        }

                        byte[] response = SONGS.get(index).getBytes(StandardCharsets.UTF_8);
                        DatagramPacket responsePacket = new DatagramPacket(response, response.length, clientRequest.getAddress(),  clientRequest.getPort());
                        serverSocket.send(responsePacket);
                    }
                }
            }

        } catch (SocketException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void loadSongs() {
        try (Scanner in = new Scanner(new File("/home/miona/IdeaProjects/ispiti/src/jan1_2023/zadatak3/trending_songs.txt"))) {
            while (in.hasNextLine()) {
                SONGS.add(in.nextLine());
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
