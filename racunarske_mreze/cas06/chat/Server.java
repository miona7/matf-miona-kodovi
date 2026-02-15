package chat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class Server {
    public static final int PORT = 12345;

    public static void main(String[] args) {
        Server server = new Server(PORT);
        server.execute();
    }

    private final int port;
    private Set<UserThread> users;

    Server(int port) {
        this.port = port;
        this.users = Collections.synchronizedSet(new HashSet<>());
    }

    void execute() {
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Server is listening on port " + port);

            while (true) {
                Socket client = serverSocket.accept();
                System.out.println("Accepted connection from " + client.getInetAddress());

                // za svakog novog klijenta kreiramo novu nit
                UserThread user = new UserThread(client, this);
                this.users.add(user);
                user.start();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    synchronized void broadcast(UserThread user, String message) {
        this.users
                .stream()
                .filter(u -> u != user)
                .forEach(u -> u.sendMessage(message));
    }

    void remove(UserThread user) {
        String name = user.getUserName();
        this.users.remove(user);
        System.out.println("Client " + name + " disconnected");
    }

    synchronized List<String> getUsers() {
        return this.users
                .stream()
                .map(UserThread::getUserName)
                .collect(Collectors.toList());
    }
}
