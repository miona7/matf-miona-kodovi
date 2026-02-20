package jan1_2021.zadatak1;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

public class Poetry {
    private static final Path dir = Path.of("/home/miona/Desktop/matf-miona-kodovi/racunarske_mreze/ispiti/jan1_2021/zadatak1/tests");

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {

            while(sc.hasNextLine()) {
                String word = sc.nextLine();
                walk(dir, word);
            }
        }
    }

    private static void walk(Path dir, String word) {
        try (DirectoryStream<Path> directoryStream = Files.newDirectoryStream(dir)) {
            for (Path path : directoryStream) {
                if (Files.isDirectory(path)) {
                    walk(path, word);
                } else if (Files.isRegularFile(path)) {
                    PoetryThread poetryThread = new PoetryThread(word, path);
                    poetryThread.start();
                } else {
                    System.err.println("Error " + path.getFileName());
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}