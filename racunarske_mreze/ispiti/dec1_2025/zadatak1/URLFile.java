package dec1_2025.zadatak1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.Scanner;

public class URLFile {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            String file = sc.nextLine();

            String name = null;

            if (file.startsWith("/")) {
                name = "file://" + file;
            } else {
                System.err.println("Nevalidna adresa");
            }

            System.out.println(name);

            URL url = (new URI(name)).toURL();
            URLConnection urlConnection = url.openConnection();

            BufferedReader br = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }

            br.close();

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (URISyntaxException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
    }
}
