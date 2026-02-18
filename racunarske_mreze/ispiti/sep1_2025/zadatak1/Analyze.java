package sep1_2025.zadatak1;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Analyze {
    private static final String IN = "/home/miona/IdeaProjects/ispiti/src/sep1_2025/zadatak1/ips.txt";
    private static String OUT = "/home/miona/IdeaProjects/ispiti/src/sep1_2025/zadatak1/protocol_stats.txt";

    private static List<String> ips = new ArrayList<>();

    public static void main(String[] args) throws InterruptedException {
        loadIPS();

        AnalyzeThread t1 = new AnalyzeThread(80, ips);
        AnalyzeThread t2 = new AnalyzeThread(443, ips);
        AnalyzeThread t3 = new AnalyzeThread(21, ips);
        AnalyzeThread t4 = new AnalyzeThread(22, ips);
        AnalyzeThread t5 = new AnalyzeThread(25, ips);

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

        try (BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(OUT)))) {
            bw.write("HTTP (80): " + t1.getActive() + " active\n");
            bw.write("HTTPS (443): " + t2.getActive() + " active\n");
            bw.write("FTP (21): " + t3.getActive() + " active\n");
            bw.write("SSH (22): " + t4.getActive() + " active\n");
            bw.write("SMTP (25): " + t5.getActive() + " active\n");
            bw.flush();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadIPS() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(IN)))) {
            String line;
            while ((line = br.readLine()) != null) {
                ips.add(line.trim());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}