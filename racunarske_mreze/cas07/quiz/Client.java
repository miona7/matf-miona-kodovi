package quiz;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

// ne radi!!!
public class Client {
    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner scanner = new Scanner(System.in)) {

            socket.setSoTimeout(5000);
            String line = scanner.nextLine();
            byte[] buffer = line.getBytes(); // za slanje odgovora klijentu
            DatagramPacket request = new DatagramPacket(buffer, buffer.length, socket.getLocalAddress(), Server.PORT);
            socket.send(request);

            while (true) {
                try {

                    byte[] bufferResponse = new byte[Server.BUFFER_SIZE];
                    DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length);
                    socket.receive(response);

                    String responseString = (new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8)).trim();

                    System.out.println(responseString);

                    if (responseString.equals("Tacno") || responseString.equals("Netcno")) {
                        break;
                    }

                    line = scanner.nextLine();
                    buffer = line.getBytes(); // za slanje odgovora klijentu
                    request = new DatagramPacket(buffer, buffer.length, socket.getLocalAddress(), Server.PORT);
                    socket.send(request);

                } catch (SocketTimeoutException e) {
                    break;
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
