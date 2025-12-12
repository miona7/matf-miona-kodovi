package resource_getter;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.*;

public class BinaryFileDownloader {
    public static void main(String[] args) {
        try {
            URL url = (new URI("https://www.matf.bg.ac.rs/wp-content/uploads/fallback-matf-final1-1024x1024.webp")).toURL();
            URLConnection urlConnection = url.openConnection(); // neophodno nam je da otvorimo konekciju nad url-om kako bi mogli da vrsimo komunikaciju

            String contentType = urlConnection.getContentType();
            int contentLength = urlConnection.getContentLength();
            if(contentLength == -1 || contentType.startsWith("text")) {
                throw new IOException("content is not binary file");
            }

            BufferedInputStream bi = new BufferedInputStream(urlConnection.getInputStream());
            String fileName = url.getFile();
            fileName = fileName.substring(fileName.lastIndexOf("/") + 1);
            System.out.println(fileName);

            try (BufferedOutputStream bo = new BufferedOutputStream(new FileOutputStream("/home/miona/IdeaProjects/cas4/src/resource_getter/" + fileName))) {
                for (int i = 0; i < contentLength; i++) {
                    int b = bi.read();
                    bo.write(b);
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } catch (URISyntaxException e) {
            throw new RuntimeException(e);
        }
    }
}
