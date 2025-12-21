package queue;

import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.BlockingQueue;

public class FileTreeWalkingRunnable implements Runnable {

    // specijalna putanja koja oznacava da smo dosli do kraja obilaska
    public static final Path END_OF_WORK = Paths.get("");

    private final BlockingQueue<Path> queue;
    private final Path startingDir;

    FileTreeWalkingRunnable(BlockingQueue<Path> queue, Path startingDir) {
        this.queue = queue;
        this.startingDir = startingDir;
    }

    @Override
    public void run() {
        try {
            walk(startingDir);
            this.queue.put(END_OF_WORK);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void walk(Path startingDir) {
        // otvaramo strim nad direktorijumom
        try (DirectoryStream<Path> ds = Files.newDirectoryStream(startingDir)) {
            // daje nam strim fajlova koji se nalaze u datom direktorijumu
            for (Path path : ds) {
                if (Files.isDirectory(path)) {
                    walk(path);
                } else {
                    this.queue.put(path); // blokira ako je red pun
                }
            }
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }
}
