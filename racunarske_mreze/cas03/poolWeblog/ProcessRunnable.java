package poolWeblog;

import java.io.IOException;
import java.net.InetAddress;

public class ProcessRunnable extends Thread {
    private final PoolWeblog poolWeblog;

    ProcessRunnable(PoolWeblog poolWeblog) {
        this.poolWeblog = poolWeblog;
    }

    @Override
    public void run() {

        while (true) {
            String line;

            synchronized (poolWeblog.getEntries()) {
                while (poolWeblog.getEntries().isEmpty()) {
                    if (poolWeblog.isFinished()) {
                        return;
                    }
                    try {
                        poolWeblog.getEntries().wait();
                        // cekamo dok ne stigne nova linija
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }

                // uzimamo prvu liniju i brisemo je
                line = poolWeblog.getEntries().remove(0);

                // nesto mi ne sljaka tuuu :)
            }

            try {
                log(line);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    private void log(String line) throws IOException {
        String addressString = line.split(" ")[0];
        InetAddress address = InetAddress.getByName(addressString);
        poolWeblog.getOut().write(address.getHostName());
        poolWeblog.getOut().newLine();
        poolWeblog.getOut().flush();
    }
}
