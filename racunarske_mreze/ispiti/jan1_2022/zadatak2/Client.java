package jan1_2022.zadatak2;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try (Socket socket = new Socket(InetAddress.getLocalHost(), Server.PORT);
             BufferedReader readFromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             BufferedWriter writeToServer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
             Scanner scanner = new Scanner(System.in)) {

            String name = scanner.nextLine();

            writeToServer.write(name);
            writeToServer.newLine();
            writeToServer.flush();

            System.out.println(readFromServer.readLine());

            while (true) {
                String line = scanner.nextLine();
                writeToServer.write(line);
                writeToServer.newLine();
                writeToServer.flush();

                String[] command = line.split(" ");

                if (command[0].equals("izadji")) {
                    break;
                } else if (command[0].equals("odradi")) {
                    String response = readFromServer.readLine();

                    System.out.println(response);

                    if (response.startsWith("Svi")) {
                        break;
                    }
                }
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
