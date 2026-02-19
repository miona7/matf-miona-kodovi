package quiz;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

// popraviti !!!
public class Server {
    public static final int PORT = 9000;
    public static final int BUFFER_SIZE = 1024;
    private static final String IN = "/home/miona/Desktop/git/matf-miona-kodovi/racunarske_mreze/cas07/quiz/questions.txt";
    private static Map<String, String> QA = new HashMap<>();

    public static void main(String[] args) {
        loadQA();

        for (Map.Entry<String, String> entry : QA.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }

        try (DatagramSocket socket = new DatagramSocket(PORT)) {

            while (true) {
                byte[] bufferAnswer = new byte[BUFFER_SIZE]; // za primanje odgovora od klijenta
                DatagramPacket request = new DatagramPacket(bufferAnswer, bufferAnswer.length);
                // npr prvo primimo ime klijenta -> treba mapa da se cuva da bi mogli vise klijenata da obradjujemo u isto vreme
                socket.receive(request);

                for (Map.Entry<String, String> entry : QA.entrySet()) {
                    byte[] bufferQuestion = entry.getKey().getBytes(StandardCharsets.UTF_8); // za slanje pitanja klijentu
                    DatagramPacket response = new DatagramPacket(bufferQuestion, 0, bufferQuestion.length, request.getAddress(), request.getPort());
                    socket.send(response);

                    bufferAnswer = new byte[BUFFER_SIZE];
                    request = new DatagramPacket(bufferAnswer, bufferAnswer.length); // odgovor
                    socket.receive(request);

                    String answer = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();
                    System.out.println(answer);

                    String msg;
                    if (answer.equals(entry.getValue())) {
                        msg = "Tacno!";
                    } else {
                        msg = "Netacno!";
                    }

                    bufferQuestion = msg.getBytes(StandardCharsets.UTF_8); // za slanje pitanja klijentu
                    response = new DatagramPacket(bufferQuestion, 0, bufferQuestion.length, request.getAddress(), request.getPort());
                    socket.send(response);
                }
            }
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadQA() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(IN)))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] words = line.split("\\|");
                QA.put(words[0], words[1]);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
