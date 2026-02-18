package jun1_2025.zadatak1;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class PingThread extends Thread {
    private final int from;
    private final int to;
    private final PrintWriter out;
    private String ip;

    public PingThread(int from, int to, PrintWriter out, String ip) {
        this.from = from;
        this.to = to;
        this.out = out;
        this.ip = ip;
    }

    @Override
    public void run() {
        for (int i = from; i <= to; ++i) {
            String address = ip + i;
            // System.out.println(Thread.currentThread().getId() + ": " + address);

            try {
                InetAddress inet = InetAddress.getByName(address);
                // System.out.println(inet.getHostAddress());

                // ne radi govno
                if (inet.isReachable(2000)) {
                    synchronized (out) {
                        out.println(inet.getHostAddress());
                    }
                } else {
                    // ne treba samo radi provere
                    synchronized (out) {
                        out.println(Thread.currentThread().getId());
                    }
                }

            } catch (UnknownHostException e) {
                e.printStackTrace();
            } catch (IOException e) {
            }
        }
    }
}
