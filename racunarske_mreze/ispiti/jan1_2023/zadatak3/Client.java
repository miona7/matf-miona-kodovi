package jan1_2023.zadatak3;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner sc = new Scanner(System.in);) {

            socket.setSoTimeout(5000);
            String firstData = "-1";

            DatagramPacket request = new DatagramPacket(firstData.getBytes(StandardCharsets.UTF_8), firstData.getBytes(StandardCharsets.UTF_8).length, InetAddress.getLocalHost(), Server.PORT);
            byte[] buff = null;
            DatagramPacket serverResponse = null;

            try {
                socket.send(request);
                buff = new byte[Server.BUFFER_SIZE];
                serverResponse = new DatagramPacket(buff, buff.length);
                socket.receive(serverResponse);
                System.out.println((new String(buff)).trim());

            } catch (IOException e) {
                socket.send(request);
                buff = new byte[Server.BUFFER_SIZE];
                serverResponse = new DatagramPacket(buff, buff.length);
                socket.receive(serverResponse);
                System.out.println((new String(buff)).trim());
            }

            while (true) {
                String command = sc.nextLine();
                if (command.contains("exit")) {
                    break;
                }

                if (command.startsWith("next")) {
                    if (command.split(" ").length == 1) {
                        command += " -1";
                    }
                    request = new DatagramPacket(command.getBytes(StandardCharsets.UTF_8), command.getBytes(StandardCharsets.UTF_8).length, InetAddress.getLocalHost(), Server.PORT);
                    socket.send(request);
                    buff = new byte[Server.BUFFER_SIZE];
                    serverResponse = new DatagramPacket(buff, buff.length);
                    socket.receive(serverResponse);
                    System.out.println((new String(buff)).trim());
                }
            }
        } catch (IOException e) {
            System.err.println("losa poruka");
            e.printStackTrace();
        }
    }
}
