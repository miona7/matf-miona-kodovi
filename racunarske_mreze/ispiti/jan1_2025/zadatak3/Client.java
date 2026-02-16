package jan1_2025.zadatak3;

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
             Scanner sc = new Scanner(System.in)) {

            while (true) {
                System.out.print("Enter command: ");
                String command = sc.nextLine();
                writeToServer.write(command + "\n");
                writeToServer.flush();

                String line = readFromServer.readLine();
                if (line == null) {
                    break;
                }

                System.out.println(line);

                if (line.equals("Connection closed.")) {
                    break;
                }
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
