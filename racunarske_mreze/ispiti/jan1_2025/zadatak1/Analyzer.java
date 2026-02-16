package jan1_2025.zadatak1;

import java.io.*;
import java.net.InetAddress;
import java.util.*;

public class Analyzer {
    public static final String IN = "/home/miona/IdeaProjects/ispiti/src/jan1_2025/zadatak1/domains.txt";
    public static final String OUT = "/home/miona/IdeaProjects/ispiti/src/jan1_2025/zadatak1/ip.with.domains.txt";

    public static void main(String[] args) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(IN)));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(OUT)))) {

            Map<String, List<String>> ips = new HashMap<String, List<String>>();

            String line;
            while ((line = br.readLine()) != null) {
                String address = InetAddress.getByName(line).getHostAddress();
                if(!ips.containsKey(address)) {
                    ips.put(address, new ArrayList<>());
                }
                ips.get(address).add(line);
            }

            for(Map.Entry<String, List<String>> entry : ips.entrySet()) {
                // System.out.println(entry.getKey() + ": " + entry.getValue());

                bw.write(entry.getKey() + "\n");

                bw.write("- Domains:\n");

                List<String> domains = entry.getValue();
                for(String domain : domains) {
                    bw.write("--- " + domain + "\n");
                }

                bw.newLine();
                bw.flush();
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
