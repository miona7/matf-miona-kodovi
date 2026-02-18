package sep1_2025.zadatak1;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.List;

public class AnalyzeThread extends Thread {
    private List<String> ips;
    private int port;
    private int active;

    AnalyzeThread(int port, List<String> ips) {
        this.port = port;
        this.ips = ips;
        this.active = 0;
    }

    @Override
    public void run() {
        for (String ip : ips) {
            try (Socket socket = new Socket()) {
                socket.connect(new InetSocketAddress(ip, port), 2000);
                active++;
            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
            }
        }
    }

    public int getActive() {
        return active;
    }
}
