import java.io.*;
import java.util.Scanner;

public class Zadatak4 {
    public static void main(String[] args) {

        try( PrintStream ps = new PrintStream(new FileOutputStream("res1.txt"), true)) {
            ps.println("Caooo");
            ps.println(1);
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }

        try (Scanner sc = new Scanner(new FileInputStream("/home/miona/IdeaProjects/cas1/src/test.txt"))) {
            while(sc.hasNext()) {
                System.out.println(sc.next());
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
