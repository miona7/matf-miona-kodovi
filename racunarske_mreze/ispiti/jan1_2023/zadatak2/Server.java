package jan1_2023.zadatak2;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class Server {
    public static final int PORT = 12321;
    private static final List<String> WORDS = new ArrayList<>();

    public static void main(String[] args) {
        loadWords();

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            while (true) {
                Socket clientSocket = serverSocket.accept();
                Thread t = new  Thread(() -> proccessClient(clientSocket));
                t.start();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    private static void proccessClient(Socket clientSocket) {
        try (BufferedReader readFromClient = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
             BufferedWriter writeToClient = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()))) {

            // server zamislja rec na indexu index
            int index = ThreadLocalRandom.current().nextInt(0, WORDS.size());
            String chosenWord = WORDS.get(index);

            writeToClient.write("Pogodi o cemu razmisljam: " + WORDS);
            writeToClient.newLine();
            writeToClient.flush();

            int i = 0;
            String hint = "";
            while (true) {
                String word = readFromClient.readLine();

                if (word == null) {
                    break;
                }

                word = word.trim();
                if (word.equals(chosenWord)) {
                    writeToClient.write("Cestitam! Pogodili ste rec.");
                    writeToClient.newLine();
                    writeToClient.flush();
                    break;
                } else {
                    if (i >= chosenWord.length() - 1) {
                        writeToClient.write("Nisi uspeo da pogodis... (" +  chosenWord + ")");
                        writeToClient.newLine();
                        writeToClient.flush();
                        break;
                    } else {
                        hint += chosenWord.charAt(i);
                        writeToClient.write("Netacno! (" + hint + ")");
                        writeToClient.newLine();
                        writeToClient.flush();
                        i++;
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadWords() {
        try (Scanner sc = new Scanner(new File("/home/miona/IdeaProjects/ispiti/src/jan1_2023/zadatak2/moguce_reci.txt"))) {
            while (sc.hasNext()) {
                WORDS.add(sc.next().trim());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
