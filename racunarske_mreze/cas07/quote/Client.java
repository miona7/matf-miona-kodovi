package quote;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class Client {

    private static final String HOST = "localhost";

    public static void main(String[] args) {
        try (DatagramSocket socket = new DatagramSocket()) {
            DatagramPacket request = new DatagramPacket(new byte[1], 1, InetAddress.getByName(HOST), Server.PORT);
            socket.send(request);

            DatagramPacket response = new DatagramPacket(new byte[Server.BUFF_SIZE], Server.BUFF_SIZE);
            socket.receive(response);

            String responseString = new String(response.getData(), 0, response.getLength(), StandardCharsets.UTF_8);
            System.out.println(responseString);
        } catch (SocketException e) {
            throw new RuntimeException(e);
        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
