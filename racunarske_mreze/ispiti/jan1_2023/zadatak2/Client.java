package jan1_2023.zadatak2;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (Socket clientSocket = new Socket(InetAddress.getLocalHost(), Server.PORT);
             BufferedReader readFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             BufferedWriter writeToServer = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
             Scanner scanner = new Scanner(System.in);) {

            String serverMessage = readFromServer.readLine();
            System.out.println(serverMessage);

            while (true) {
                String guess =  scanner.nextLine().trim();
                writeToServer.write(guess);
                writeToServer.newLine();
                writeToServer.flush();

                String response = readFromServer.readLine();
                if (response.startsWith("Cestitam!")) {
                    System.out.println(response);
                    break;
                }

                if (response.startsWith("Nisi")) {
                    System.out.println(response);
                    break;
                }

                System.out.println(response);
            }

        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
