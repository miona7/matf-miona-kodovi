package quiz;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class QuizServer {
    public static final int PORT = 9000;
    public static final int BUFFER_SIZE = 1024;

    private static final String IN = "/home/miona/Desktop/matf-miona-kodovi/racunarske_mreze/cas07/quiz/questions.txt";
    private static final List<Question> questions = new ArrayList<>();

    private static final Map<Client, Session> sessions = new HashMap<>();

    public static void main(String[] args) {
        loadQuestions();

        for (Question question : questions) {
            System.out.println(question);
        }

        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            byte[] buffer = new byte[BUFFER_SIZE]; // za primanje odgovora od klijenta
            byte[] bufferResponse; // za slanje pitanja klijentu

            while (true) {
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                socket.receive(request);

                Client client = new Client(request.getAddress(), request.getPort());
                if (sessions.containsKey(client)) {
                    String answer = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();

                    Session session = sessions.get(client);
                    boolean isCorrect = session.getCurrentQuestion().checkAnswer(answer);

                    StringBuilder responseString = new StringBuilder(isCorrect ? "Tacno!" : "Netacno!");
                    if (session.hasNextQuestion()) {
                        Question next = session.getNextQuestion();
                        responseString.append(" ").append(next.getQuestion());
                        session.setCurrentQuestion(next);
                    } else {
                        sessions.remove(client);
                    }

                    bufferResponse = responseString.toString().getBytes(StandardCharsets.UTF_8);
                } else {
                    Session session = new Session(questions);
                    sessions.put(client, session);
                    Question first = session.getNextQuestion();
                    session.setCurrentQuestion(first);

                    bufferResponse = first.getQuestion().getBytes(StandardCharsets.UTF_8);
                }

                DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length, client.getAddress(), client.getPort());
                socket.send(response);
            }

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadQuestions() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(IN)))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] words = line.split("\\|");
                questions.add(new Question(words[0], words[1]));
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
