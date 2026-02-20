package quiz;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class QuizClient {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner scanner = new Scanner(System.in)) {

            byte[] buffer = new byte[1]; // za slanje odgovora serveru
            // pocetni zahtev kako bismo uspostavili sesiju
            DatagramPacket request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), QuizServer.PORT);
            socket.send(request);

            byte[] bufferResponse = new byte[QuizServer.BUFFER_SIZE]; // za primanje pitanja od servera

            while (true) {
                DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length);
                socket.receive(response);

                String responseString = (new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8)).trim();
                System.out.println(responseString);

                if (responseString.equals("Tacno!") || responseString.equals("Netacno!")) {
                    break;
                }

                String answer = scanner.nextLine();
                buffer = answer.getBytes(StandardCharsets.UTF_8);
                request = new DatagramPacket(buffer, buffer.length, InetAddress.getLocalHost(), QuizServer.PORT);
                socket.send(request);
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
