package jun1_2025.zadatak1;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class Ping {
    private static String OUT = "/home/miona/IdeaProjects/ispiti/src/jun1_2025/zadatak1/reachable_ips.txt";

    public static void main(String[] args) {
        try (PrintWriter out = new PrintWriter(new OutputStreamWriter(new FileOutputStream(OUT)), true)) {

            // lepse kroz petlju ali me mrzelo

            PingThread t1 = new PingThread(1, 20, out, "192.168.0.");
            PingThread t2 = new PingThread(21, 40, out, "192.168.0.");
            PingThread t3 = new PingThread(41, 60, out, "192.168.0.");
            PingThread t4 = new PingThread(61, 80, out, "192.168.0.");
            PingThread t5 = new PingThread(81, 100, out, "192.168.0.");

            t1.start();
            t2.start();
            t3.start();
            t4.start();
            t5.start();

            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
