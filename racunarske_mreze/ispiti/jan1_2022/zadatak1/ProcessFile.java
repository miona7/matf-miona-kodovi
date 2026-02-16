package jan1_2022.zadatak1;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.file.Path;

public class ProcessFile extends Thread {
    private Path file;

    ProcessFile(Path path) {
        this.file = path;
    }

    @Override
    public void run() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(this.file.toString())))) {
            String line;

            StringBuffer sb = new StringBuffer();
            sb.append(this.file + "\n");

            int numofUrls = 0;
            int lineNumber = 1;

            while ((line =  br.readLine()) != null) {
                StringBuilder tmp = new StringBuilder();
                for (int i = line.length() - 1; i >= 0; i--) {
                    tmp.append(line.charAt(i));
                }
                String tmp1 =  tmp.toString();

                try {
                    URL url = new URL(tmp1);
                    String protocol = url.getProtocol();
                    numofUrls += 1;

                    sb.append(lineNumber + " : " + protocol);

                    if (protocol.equals("https")) {
                        sb.append(" : " + url.getPort());
                    }

                    sb.append("\n");
                } catch (MalformedURLException e) {
                }

                lineNumber++;
            }

            sb.append(numofUrls + "\n");
            System.out.println(sb);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
