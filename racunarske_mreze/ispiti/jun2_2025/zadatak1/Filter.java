package jun2_2025.zadatak1;

import java.io.*;
import java.net.*;
import java.util.*;

public class Filter {
    private static final Set<String> ips = new HashSet<>();
    private static final String file = "/home/miona/IdeaProjects/ispiti/src/jun2_2025/zadatak1/filter.txt";

    public static void main(String[] args) {
        loadIps();
        
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Unesite URL: ");

            while (sc.hasNextLine()) {
                try {
                    String line = sc.nextLine();
                    URL url = (new URI(line)).toURL();

                    String host = url.getHost();
                    InetAddress[] addresses = InetAddress.getAllByName(host);

                    boolean allowed = true;

                    for (InetAddress address : addresses) {
                        if (ips.contains(address.getHostAddress())) {
                            allowed = false;
                            break;
                        }
                    }

                    if (allowed) {
                        System.out.println("Dozvoljeno");
                    } else {
                        System.out.println("Nije dozvoljeno");
                    }

                    System.out.print("Unesite URL: ");
                } catch (MalformedURLException e) {
                    System.err.println("Protokol nije podrzan");
                    System.out.print("Unesite URL: ");
                }  catch (URISyntaxException e) {
                    e.printStackTrace();
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private static void loadIps() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file)))) {
            String line;
            while ((line = br.readLine()) != null) {
                InetAddress[] addresses = InetAddress.getAllByName(line);
                for (InetAddress address : addresses) {
                    ips.add(address.getHostAddress());
                }
            }
        } catch (UnknownHostException e) {
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
