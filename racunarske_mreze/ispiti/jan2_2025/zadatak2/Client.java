package jan2_2025.zadatak2;

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

            String line = readFromServer.readLine();
            System.out.println(line);

            line = readFromServer.readLine();
            System.out.println(line);

            line = readFromServer.readLine();
            System.out.print(line);

            String username = sc.nextLine();
            writeToServer.write(username + "\n");
            writeToServer.flush();

            line = readFromServer.readLine();
            System.out.print(line);

            while (true) {
                String guees = sc.nextLine();
                writeToServer.write(guees);
                writeToServer.newLine();
                writeToServer.flush();

                line = readFromServer.readLine();
                System.out.println(line);

                line = readFromServer.readLine();
                System.out.println(line);

                if (line.contains("Correct!")) {
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
