package jan1_2022.zadatak3;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;

public class Server {
    public static final int PORT = 12345;
    public static final int BUFFER_SIZE = 1024;
    private static final Path dir = Path.of("/home/miona/IdeaProjects/ispiti/src/jan1_2022/zadatak1/tests");

    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket(PORT)) {
            int index = -1;
            boolean getIndex = false;

            String name = null;
            boolean getName = false;

            while (true) {
                socket.setSoTimeout(5000);

                try {
                    byte[] buffer = new byte[BUFFER_SIZE]; // za primanje zahteva od klijenta
                    DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                    socket.receive(request);

                    String requestString = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();

                    if (!getIndex) {
                        try {
                            index = Integer.parseInt(requestString);
                            getIndex = true;
                        }  catch (NumberFormatException e) {
                        }
                    }

                    if (!getName) {
                        try {
                            int tmp = Integer.parseInt(requestString);
                        }  catch (NumberFormatException e) {
                            name = requestString;
                            getName = true;
                        }
                    }

                    if (getName && getIndex) {
                        System.out.println(index);
                        System.out.println(name);

                        Path file = dir.resolve(name);
                        System.out.println(file.toAbsolutePath());

                        String line = decode(file.toAbsolutePath().toFile(), index);

                        index = -1;
                        getIndex = false;

                        name = null;
                        getName = false;

                        if (line == null) {
                            continue;
                        }

                        System.out.println(line);

                        byte[] bufferResponse = line.getBytes(StandardCharsets.UTF_8); // za slanje odgovora klijentu
                        DatagramPacket response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    }
                } catch (SocketTimeoutException e) {
                    // e.printStackTrace();
                }
            }
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }

    private static String decode(File file, int index) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file)))) {
            String line;
            int i = 0;
            while ((line = br.readLine()) != null) {
                if (index == i) {
                    StringBuilder builder = new StringBuilder();
                    for (int j = line.length() - 1; j >= 0; j--) {
                        builder.append(line.charAt(j));
                    }
                    return builder.toString();
                }
                i++;
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }
}
