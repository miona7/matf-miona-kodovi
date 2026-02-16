package jan2_2025.zadatak1;

import java.io.*;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.*;

public class Reachability {
    private static final String IN = "/home/miona/IdeaProjects/ispiti/src/jan2_2025/zadatak1/domains.txt";
    private static final String OUT = "/home/miona/IdeaProjects/ispiti/src/jan2_2025/zadatak1/reachable_stats.txt";

    public static void main(String[] args) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(IN)));
             BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(OUT)))) {

            List<String> domains = new ArrayList<>();
            String domain;
            while ((domain = br.readLine()) != null) {
                domains.add(domain);
            }

            int numOfReachable = 0;
            int numOfUnreachable = 0;

            // ili String -> Integer + predefinisani Comparator da sortira po Integeru
            SortedMap<Integer, List<String>> time = new TreeMap<>();

            // hard kodovano!!! ne radi jebeni reachable
            int i = 0;
            for (String d : domains) {
                try {
                    InetAddress address = InetAddress.getByName(d);

                    long startTime = System.currentTimeMillis();
                    boolean isReachable = address.isReachable(3000);
                    long endTime = System.currentTimeMillis();

                    if (isReachable) {
                        numOfReachable++;

                        long diff = endTime - startTime;
                        int res = (int) diff;

                        time.putIfAbsent(res, new ArrayList<>());
                        time.get(res).add(d);

                    } else {
                        numOfUnreachable++;

                        time.putIfAbsent(i, new ArrayList<>());
                        time.get(i).add(d);

                        i++;
                    }
                } catch (UnknownHostException e) {
                    numOfUnreachable++;
                }
            }

            bw.write("Ukupan broj dostupnih domena: " + numOfReachable + "\n");
            bw.write("Ukupan broj nedostupnih domena: " + numOfUnreachable + "\n");

            bw.write("\nDostupni domeni sa vremenom odziva:\n");

            for (Map.Entry<Integer, List<String>> entry : time.entrySet()) {
                List<String> list = entry.getValue();
                for (String d : list) {
                    bw.write(d + " - " + entry.getKey() + "ms\n");
                }
            }

            bw.write("\nTop 3 najbrza domena:\n");

            i = 1;
            for (Map.Entry<Integer, List<String>> entry : time.entrySet()) {
                List<String> list = entry.getValue();
                for (String d : list) {
                    if (i == 4) {
                        break;
                    }
                    bw.write(d + " - " + entry.getKey() + "ms\n");
                    i++;
                }
                if (i == 4) {
                    break;
                }
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
