package poolWeblog;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class PoolWeblog {

    private final BufferedReader in;
    private final BufferedWriter out;
    // atomicne operacije su citanje i pisanje u sinhronizovanoj listi, iteriranje nije
    private final List<String> entries = Collections.synchronizedList(new LinkedList<>());
    private boolean finished;
    private final int numberOfThreads;
    private final List<Thread> threads;

    PoolWeblog(BufferedReader in, BufferedWriter out, int numberOfThreads) {
        this.in = in;
        this.out = out;
        this.finished = false;
        this.numberOfThreads = numberOfThreads;
        threads = new ArrayList<>(this.numberOfThreads);
    }

    public List<String> getEntries() {
        return entries;
    }

    public boolean isFinished() {
        return finished;
    }

    public BufferedWriter getOut() {
        return out;
    }

    public void processLog() throws IOException, InterruptedException {
        for (int i = 0; i < this.numberOfThreads; i++) {
            Thread thread = new ProcessRunnable(this);
            thread.start();
            threads.add(thread);
        }

        String line;
        while ((line = in.readLine()) != null) {
            synchronized (entries) {
                while (entries.size() > numberOfThreads) {
                    entries.wait(1000);
                }
                entries.add(line);
                entries.notifyAll();
            }
        }

        synchronized (entries) {
            finished = true;
            entries.notifyAll();
        }

        for (Thread t : threads) {
            t.join();
        }
    }
}
