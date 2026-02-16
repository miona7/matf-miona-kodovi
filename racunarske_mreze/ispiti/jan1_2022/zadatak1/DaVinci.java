package jan1_2022.zadatak1;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class DaVinci {
    public static void main(String[] args) {
        Path dir = Path.of("/home/miona/IdeaProjects/ispiti/src/jan1_2022/zadatak1/tests");

        try (DirectoryStream<Path> stream = Files.newDirectoryStream(dir)) {
            for (Path path : stream) {
                ProcessFile pf = new ProcessFile(path);
                pf.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
