package jan1_2023.zadatak1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;

public class URLScanner {
    public static void main(String[] args) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = in.readLine()) != null) {

                try {
                    URL url = new URL(line);

                    String protocol = url.getProtocol();
                    String authority = url.getAuthority();
                    String path = url.getPath();
                    String host = url.getHost();

                    if (isIP(host)) {
                        InetAddress address = InetAddress.getByName(host);
                        switch (version(address)) {
                            case 4:
                                byte[] bytes = address.getAddress();
                                System.out.print("(v4) " + protocol + " " +  path + " [");
                                for (int i = 0; i < bytes.length; i++) {
                                    int unbyte = bytes[i] & 0xFF; // konvertujemo signed u unsigned
                                    System.out.print(unbyte);
                                    if(i != 3) {
                                        System.out.print(" ");
                                    }
                                }
                                System.out.println("]");
                                break;
                            case 6:
                                System.out.println("(v6) " + protocol + " " +  path);
                                break;
                        }

                    } else {
                        System.out.println(protocol + " " + authority + " " +  path);
                    }

                } catch (IllegalArgumentException | MalformedURLException e) {
                    System.err.println("Invalid URL: " + line);
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static int version(InetAddress address) {
        if(address instanceof Inet4Address) {
            return 4;
        }

        if(address instanceof Inet6Address) {
            return 6;
        }

        return 0;
    }

    private static boolean isIP(String host) {
        if (host == null) {
            return false;
        }

        if (host.contains("[") && host.contains("]")) {
            return true;
        }

        try {
            InetAddress inetAddress = InetAddress.getByName(host);

            if(host.length() + 1 == inetAddress.toString().length()) {
                return true;
            }

        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        }

        return false;
    }
}
