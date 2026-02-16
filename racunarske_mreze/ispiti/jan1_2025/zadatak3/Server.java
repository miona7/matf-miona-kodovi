package jan1_2025.zadatak3;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;

public class Server {
    public static final int PORT = 5555;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            while (true) {
                // prvo prihvatamo konekciju od klijenta
                Socket client = serverSocket.accept();
                // pokrecemo novu nit za svakog novog klijenta
                Thread t = new Thread(() -> proccesClient(client));
                t.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void proccesClient(Socket client) {
        try (BufferedReader readFromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
             BufferedWriter writeToClient = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))) {

            while (true) {
                // writeToClient.write("Enter command: ");
                // writeToClient.flush();

                String line = readFromClient.readLine();
                if (line == null) {
                    System.err.println("Line is null");
                    break;
                }

                String[] command = line.split(" ");
                System.out.println(Arrays.toString(command));

                if (command[0].equals("EXIT") && command.length == 1) {
                    writeToClient.write("Connection closed.\n");
                    writeToClient.flush();
                    break;
                }

                if (command[0].equals("ENC") && command.length >= 3) {
                    // enkodiraj
                    try {
                        int shift = Integer.parseInt(command[1]);
                        String result = "";
                        for (int i = 2; i < command.length; i++) {
                            StringBuilder builder = new StringBuilder();
                            for (int j = 0; j < command[i].length(); j++) {
                                if (Character.isLowerCase(command[i].charAt(j))) {
                                    char c = command[i].charAt(j);
                                    char newChar = (char) ('a' + (c - 'a' + shift) % 26);
                                    builder.append(newChar);
                                } else {
                                    builder.append(command[i].charAt(j));
                                }
                            }
                            builder.append(" ");
                            result += builder.toString();
                        }
                        writeToClient.write("Result: " + result + "\n");
                        writeToClient.flush();
                    } catch (NumberFormatException e) {
                        writeToClient.write("Invalid command format.\n");
                        writeToClient.flush();
                    }
                } else if (command[0].equals("DEC") && command.length >= 3) {
                    // dekodiraj
                    try {
                        int shift = Integer.parseInt(command[1]);
                        String result = "";
                        for (int i = 2; i < command.length; i++) {
                            StringBuilder builder = new StringBuilder();
                            for (int j = 0; j < command[i].length(); j++) {
                                if (Character.isLowerCase(command[i].charAt(j))) {
                                    char c = command[i].charAt(j);
                                    char newChar = (char) ('a' + (c - 'a' - shift) % 26);
                                    builder.append(newChar);
                                } else {
                                    builder.append(command[i].charAt(j));
                                }
                            }
                            builder.append(" ");
                            result += builder.toString();
                        }
                        writeToClient.write("Result: " + result + "\n");
                        writeToClient.flush();
                    } catch (NumberFormatException e) {
                        writeToClient.write("Invalid command format.\n");
                        writeToClient.flush();
                    }
                } else {
                    writeToClient.write("Invalid command format.\n");
                    writeToClient.flush();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
