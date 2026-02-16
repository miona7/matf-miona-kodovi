package jan1_2025.zadatak2;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.Random;

public class Server {
    public static final int PORT = 5555;
    public static final int BUFF_SIZE = 1024;

    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket(PORT)) {

            Random random = new Random(); // za biranje poteza servera

            while (true) {

                byte[] buffer = new byte[BUFF_SIZE]; // za primanje zahteva od klijenta

                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                socket.receive(request);

                String name = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();

                String responseString = name + ", what is your move: ";
                byte[] responseBuffer = responseString.getBytes(StandardCharsets.UTF_8); // za slanje odgovora klijentu
                DatagramPacket response = new DatagramPacket(responseBuffer, responseBuffer.length, request.getAddress(), request.getPort());
                socket.send(response);

                request = new DatagramPacket(buffer, buffer.length);
                socket.receive(request);

                String clientMove = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();

                int randomInt = random.nextInt(3);
                String serverMove;
                if (randomInt == 0) {
                    serverMove = "rock";
                    responseString = "Server move: " + serverMove + ". ";

                    if(clientMove.equals("paper")) {
                        responseString += "You win!";
                    } else if (clientMove.equals("rock")) {
                        responseString += "Tied!";
                    } else {
                        responseString += "You lose!";
                    }

                } else if (randomInt == 1) {
                    serverMove = "paper";

                    responseString = "Server move: " + serverMove + ". ";

                    if(clientMove.equals("scissors")) {
                        responseString += "You win!";
                    } else if (clientMove.equals("paper")) {
                        responseString += "Tied!";
                    } else {
                        responseString += "You lose!";
                    }

                } else {
                    serverMove = "scissors";

                    responseString = "Server move: " + serverMove + ". ";

                    if(clientMove.equals("rock")) {
                        responseString += "You win!";
                    } else if (clientMove.equals("scissors")) {
                        responseString += "Tied!";
                    } else {
                        responseString += "You lose!";
                    }
                }

                responseString += "\n";

                responseBuffer = responseString.getBytes(StandardCharsets.UTF_8);
                response = new DatagramPacket(responseBuffer, responseBuffer.length, request.getAddress(), request.getPort());
                socket.send(response);
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
