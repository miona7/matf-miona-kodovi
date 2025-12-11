package bank;

import java.util.Arrays;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LockedBank implements IBank {

    private final int[] accounts;
    // interfejs
    private Lock lock;
    // specijalni uslovi koji se vezuju za lock
    private Condition insufficientFunds;

    LockedBank(int accountsNum, int initialBalance) {
        this.accounts = new int[accountsNum];
        Arrays.fill(accounts, initialBalance);
        this.lock = new ReentrantLock();
        this.insufficientFunds = this.lock.newCondition();
    }

    @Override
    public void transfer(int from, int to, int amount) {
        int total;
        this.lock.lock();
        try {
            while (this.accounts[from] < amount) {
                try {
                    // cekamo ako nemamo dovoljno sredstava
                    this.insufficientFunds.await();
                    // ne blokira, odnosno otkljucava lock dok ne dobije sredstava i samim tim ne blokira ostale niti
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            System.out.println(Thread.currentThread());
            this.accounts[from] -= amount;
            this.accounts[to] += amount;
            total = this.getTotalBalance();

            // transfer je obavljen i sve niti koje cekaju na nasem lock-u mogu opet da provere sredstva opet
            this.insufficientFunds.signalAll();
        } finally {
            this.lock.unlock();
        }
        System.out.println("transfer from " + from + " to " + to + " amount: " + amount);
        System.out.println("total balance: " + total);
    }

    @Override
    public int getTotalBalance() {
        return Arrays.stream(accounts).sum();
    }

    @Override
    public int count() {
        return accounts.length;
    }
}
