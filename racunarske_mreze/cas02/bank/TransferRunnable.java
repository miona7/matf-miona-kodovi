package bank;

import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.ThreadPoolExecutor;

public class TransferRunnable implements Runnable {

    private final IBank bank;
    private final int from;
    private final int max;

    TransferRunnable(IBank bank, int from, int max) {
        this.bank = bank;
        this.from = from;
        this.max = max;
    }

    @Override
    public void run() {
        ThreadLocalRandom r = ThreadLocalRandom.current();
        try {
            while (true) {
                int to = r.nextInt(this.bank.count());
                int amount = r.nextInt(max);
                this.bank.transfer(from, to, amount);
                Thread.sleep(r.nextInt(2));
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
