package jan1_2023.zadatak3;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket()) {

            socket.setSoTimeout(5000);

            String firstData = "-1";

            byte[] buffer = firstData.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
            DatagramPacket request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);

            String responseString = sendAndReceive(socket, request);
            System.out.println("Next song: " + responseString);

            try (Scanner sc = new  Scanner(System.in)) {
                while (true) {
                    String command = sc.nextLine();

                    if (command.contains("exit")) {
                        break;
                    }

                    if (command.startsWith("next")) {
                        String index;
                        String[] tmp = command.split(" ");

                        if (tmp.length == 1) {
                            index = "-1";
                        } else if (tmp.length == 2) {
                            index = tmp[1];
                        } else { // losa komanda se ignorise
                            continue;
                        }

                        // System.out.println("Index: " + index);

                        buffer = index.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
                        request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);

                        responseString = sendAndReceive(socket, request);
                        System.out.println("Next song: " + responseString);
                    }

                    // losa komanda se ignorise
                }
            }  catch (IOException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private static String sendAndReceive(DatagramSocket socket, DatagramPacket request) throws IOException {
        byte[] responseBuffer = new byte[Server.BUFFER_SIZE]; // za primanje odgovora od servera
        DatagramPacket response = new DatagramPacket(responseBuffer, responseBuffer.length);

        for (int attempt = 0; attempt < 2; attempt++) {
            try {
                System.out.println("Sending request...");
                socket.send(request);

                socket.receive(response); // blokirajuce

                return (new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8)).trim();

            } catch (SocketTimeoutException e) {
                if (attempt == 1) {
                    System.out.println("Server ne odgovara. Gasim klijenta.");
                    System.exit(1);
                }
                System.out.println("Timeout... ponovo saljem zahtev.");
            }
        }
        return null; // nikad se ne desava
    }
}