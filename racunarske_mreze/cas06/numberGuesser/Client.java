package numberGuesser;

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
             Scanner in = new Scanner(System.in)) {

            while (true) {
                String line = readFromServer.readLine();
                System.out.println(line);

                if (line.startsWith("Cestitam")) {
                    break;
                }

                writeToServer.write(in.nextLine());
                writeToServer.newLine();
                writeToServer.flush();
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
