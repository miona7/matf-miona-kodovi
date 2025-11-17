import java.io.*;

public class Zadatak1 {
    public static void main(String[] args) {
        // skinemo sliku

        // try with resources
        try(FileInputStream fis = new FileInputStream("in.png");
            FileOutputStream fos = new FileOutputStream("out1.png")) {
            // read cita bajt po bajt - sporo
            while(fis.read() != -1) {
                fos.write(fis.read());
            }

            // fis.close();
            // fos.close();
        } catch (IOException e) {
            System.err.println("Greska");
            // throw new RuntimeException(e);
        }
    }
}
