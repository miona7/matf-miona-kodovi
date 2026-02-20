package jan1_2021.zadatak1;

import java.io.IOException;
import java.nio.file.Path;
import java.util.Scanner;

public class PoetryThread extends Thread {
    private final String word;
    private final Path file;
    private int longestLineLength;
    private String longestLine;
    private int number;

    PoetryThread(String word, Path file) {
        this.word = word;
        this.file = file;
        this.longestLineLength = 0;
        this.longestLine = "";
        this.number = 0;
    }

    @Override
    public void run() {
        try (Scanner scanner = new Scanner(file)) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (line.length() > longestLineLength) {
                    longestLineLength = line.length();
                    longestLine = line;
                }

                String[] words = line.split(" ");
                for (String w : words) {
                    if (w.equalsIgnoreCase(word)) {
                        number++;
                    }
                }
            }

            String[] tmp = file.getFileName().toString().split("\\.");
            System.out.print(tmp[0] + "\n" + longestLine + "\n" + number + "\n");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
