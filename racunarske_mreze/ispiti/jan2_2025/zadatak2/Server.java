package jan2_2025.zadatak2;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Server {

    public static final int PORT = 5555;

    private static final String ANIMALS_FILE = "/home/miona/IdeaProjects/ispiti/src/jan2_2025/zadatak2/animals.txt";
    private static final List<String> ANIMALS = new ArrayList<>();

    public static void main(String[] args) {
        loadAnimals();
        try (ServerSocket socket = new ServerSocket(PORT)) {
            while (true) {
                Socket client = socket.accept();
                Thread t = new Thread(() -> proccessClient(client));
                t.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadAnimals() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(ANIMALS_FILE)))) {
            String line;
            while ((line = br.readLine()) != null) {
                ANIMALS.add(line);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void proccessClient(Socket client) {
        try (BufferedReader readFromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter writeToClient = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))) {

            writeToClient.write("Welcome to server for guessing the animal!\nAvailable animals are: " + ANIMALS + "\nEnter your name: \n");
            writeToClient.flush();

            String name = readFromClient.readLine();
            writeToClient.write(name + ", guess the animal I chose: \n");
            writeToClient.flush();

            Random random = new Random();
            int index = random.nextInt(ANIMALS.size());
            String animal = ANIMALS.get(index);

            while (true) {
                String guess = readFromClient.readLine();
                writeToClient.write("Your guees: " + guess + "\n");
                writeToClient.flush();

                if (guess.compareTo(animal) < 0) {
                    writeToClient.write("Server: Too early in alphabet\n");
                    writeToClient.flush();
                } else if (guess.compareTo(animal) > 0) {
                    writeToClient.write("Server: Too late in alphabet\n");
                    writeToClient.flush();
                } else {
                    writeToClient.write("Server: Correct!\n");
                    writeToClient.flush();
                    break;
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
