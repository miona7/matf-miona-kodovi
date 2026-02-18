package jan1_2022.zadatak3;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner sc = new Scanner(System.in)) {

            while (true) {

                try {
                    String line = sc.nextLine();
                    byte[] buffer = line.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
                    DatagramPacket request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);
                    socket.send(request);

                    line = sc.nextLine();
                    buffer = line.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
                    request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);
                    socket.send(request);


                    byte[] bufferResponse = new byte[Server.BUFFER_SIZE];
                    DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length);
                    socket.receive(response);

                    String responseString = (new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8)).trim();
                    System.out.println(responseString);

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
}
