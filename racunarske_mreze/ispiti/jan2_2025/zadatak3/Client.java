package jan2_2025.zadatak3;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in);
             DatagramSocket socket = new DatagramSocket()) {
            // prvo saljemo ime
            System.out.print("Enter your name: ");
            String name = sc.nextLine();

            byte[] buffer = name.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
            DatagramPacket request = new DatagramPacket(buffer, 0, buffer.length, InetAddress.getLocalHost(), Server.PORT);
            socket.send(request);

            while (true) {
                byte[] bufferResponse = new byte[Server.BUFF_SIZE]; // za primanje odgovora od servera
                DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length);
                socket.receive(response);

                String responseString = (new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8)).trim();
                System.out.println(responseString);

                if (responseString.startsWith("Total")) {
                    break;
                }

                String command = sc.nextLine();
                buffer = command.getBytes(StandardCharsets.UTF_8);
                request = new DatagramPacket(buffer, 0, buffer.length, InetAddress.getLocalHost(), Server.PORT);
                socket.send(request);
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
