package jan1_2022.zadatak2;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;
import java.util.NoSuchElementException;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Server {
    public static final int PORT = 12345;

    private static ConcurrentLinkedQueue<String> zadaci = new ConcurrentLinkedQueue<>();

    private static String LOG_FILE = "log.txt";

    public static void main(String[] args) {
        loadZadaci();

        try (ServerSocket socket = new ServerSocket(PORT);
             PrintWriter out = new PrintWriter(new OutputStreamWriter(new FileOutputStream(LOG_FILE)), true)) {

            while (true) {
                Socket client = socket.accept();
                new Thread(() -> proccesClient(client, out)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private static void loadZadaci() {
        zadaci.add("sudovi");
        zadaci.add("ves");
        zadaci.add("kupovina");
        zadaci.add("rucak");
        zadaci.add("ciscenje");
    }

    private  static void proccesClient(Socket client, PrintWriter out) {
        try (BufferedReader readFromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
             BufferedWriter writeToClient = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))) {

            String name =  readFromClient.readLine();

            writeToClient.write("Zdravo " + name + "!");
            writeToClient.newLine();
            writeToClient.flush();

            while (true) {
                String line = readFromClient.readLine();

                String[] commands =  line.split(" ");

                if (commands[0].equals("odradi")) {
                    String zadatak;

                    synchronized (zadaci) {
                        try {
                            zadatak = zadaci.remove();
                        } catch (NoSuchElementException e) {
                            writeToClient.write("Svi zadaci su obavljeni\n");
                            writeToClient.flush();
                            break;
                        }
                    }

                    writeToClient.write("Vas zadatak je: " + zadatak + "\n");
                    writeToClient.flush();

                    String output = LocalDateTime.now().toLocalTime().toString() + ": Korisnik " + name + " je odradio zadatak " + zadatak + ".";
                    synchronized (out) {
                        out.println(output);
                    }
                } else if (commands[0].equals("dodaj")) {
                    String zadatak = commands[1];

                    synchronized (zadaci) {
                        zadaci.add(zadatak);
                    }

                    String output = LocalDateTime.now().toLocalTime().toString() + ": Korisnik " + name + " je dodao zadatak " + zadatak + ".";
                    synchronized (out) {
                        out.println(output);
                    }
                } else if (commands[0].equals("izadji")) {
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
