import java.io.*;

public class Zadatak2 {
    public static void main(String[] args) {
        // skinemo sliku

        // try with resources
        try(BufferedInputStream bis = new BufferedInputStream(new FileInputStream("in.png"));
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("out2.png"))) {

            byte[] bytes = new byte[1024];
            int b;

            // automatski vrsi pomeranje
            // sami smo birali koliko ce da procita i upise, pa ne moramo da radimo flas
            while((b = bis.read(bytes, 0, bytes.length)) != -1) {
                bos.write(bytes, 0, b);
            }

            // radi sigurnosti
            bos.flush();

        } catch (IOException e) {
            System.err.println("Greska");
            // throw new RuntimeException(e);
        }
    }
}
