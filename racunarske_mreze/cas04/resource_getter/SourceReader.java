package resource_getter;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;

public class SourceReader {

    private static final String URL_STRING = "https://matf.ristovic.net/courses/rm/";

    public static void main(String[] args) {
        try {
            URL url = (new URI(URL_STRING)).toURL();

            BufferedReader br = new BufferedReader(new InputStreamReader(url.openStream()));
            String line;
            while((line = br.readLine()) != null) {
                System.out.println(line);
            }
            br.close();

            URLConnection urlConnection = url.openConnection();
            String encoding = urlConnection.getContentEncoding();
            if(encoding == null) {
                encoding = "UTF-8";
            }

            System.out.println("-------------------------------------------------------------------------------");

            br = new BufferedReader(new InputStreamReader(urlConnection.getInputStream(), encoding));
            while((line = br.readLine()) != null) {
                System.out.println(line);
            }
            br.close();

        } catch (MalformedURLException e) {
            throw new RuntimeException(e);
        } catch (URISyntaxException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
