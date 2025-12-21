package queue;

import java.io.IOException;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.concurrent.BlockingQueue;

public class SearchFileRunnable implements Runnable {

    private final BlockingQueue<Path> queue;
    private final String keyword;

    SearchFileRunnable(BlockingQueue<Path> queue, String keyword) {
        this.queue = queue;
        this.keyword = keyword;
    }

    @Override
    public void run() {
        try {
            while (true) {
                Path path = queue.take(); // blokira ako je red prazan
                if(path == FileTreeWalkingRunnable.END_OF_WORK) {
                    this.queue.put(path);
                    break;
                }
                this.search(path);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void search(Path path) {
        try (Scanner scanner = new Scanner(path)) {
            for(int i = 0; scanner.hasNextLine(); i++) {
                String line = scanner.nextLine();
                if(line.contains(keyword)) {
                    System.out.printf("%s: %d\n", path.getFileName(), i);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
