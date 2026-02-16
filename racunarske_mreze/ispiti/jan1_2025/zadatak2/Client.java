package jan1_2025.zadatak2;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {

    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner sc = new Scanner(System.in)) {

            System.out.print("Enter your name: ");

            String name = sc.nextLine();

            byte[] buffer = name.getBytes(StandardCharsets.UTF_8); // za slanje zahteva serveru
            DatagramPacket request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);
            socket.send(request);

            byte[] responseBuffer = new byte[Server.BUFF_SIZE]; // za primanje odgovora od servera
            DatagramPacket response = new DatagramPacket(responseBuffer, responseBuffer.length);
            socket.receive(response);

            String responseString = new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8);
            System.out.print(responseString);

            String move = sc.nextLine();

            buffer = move.getBytes(StandardCharsets.UTF_8);
            request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), Server.PORT);
            socket.send(request);

            responseBuffer = new byte[Server.BUFF_SIZE];
            response = new DatagramPacket(responseBuffer, responseBuffer.length);
            socket.receive(response);

            responseString = new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8);
            System.out.println(responseString);

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
