import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

public class Server {

    public static final int PORT = 12345;

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server started on port " + PORT);

            while (true) {
                System.out.println("Waiting for connection...");
                try (Socket clientSocket = serverSocket.accept()) {
                    System.out.println("Connection established...");
                    // koristimo samo output stream jer server samo pise klijentu, ne cita nista
                    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter((clientSocket.getOutputStream())));
                    String now = new Date().toString();
                    bw.write(now);
                    bw.newLine();
                    bw.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                System.out.println("Client served!");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
