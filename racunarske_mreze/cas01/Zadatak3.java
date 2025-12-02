import java.io.*;

public class Zadatak3 {
    public static void main(String[] args) {

        // od strima pravimo citac, mozemo i da mu podesimo kodiranje, pa ga onda baferisemo, isto i za pisanje

        try(BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("/home/miona/IdeaProjects/cas1/src/test.txt")));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("res.txt")))) {

            String line;

            while((line = br.readLine()) != null) {
                bw.write(line);
                bw.newLine();
            }

        } catch (IOException e) {
            System.err.println("Greska");
        }
    }
}
