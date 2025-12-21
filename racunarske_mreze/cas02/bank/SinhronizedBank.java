package bank;

import java.util.Arrays;

public class SinhronizedBank implements IBank {
    private final int[] accounts;

    SinhronizedBank(int accountsNum, int initialBalance) {
        this.accounts = new int[accountsNum];
        Arrays.fill(accounts, initialBalance);
    }

    // cela funkcija moze biti sinhtonizovana, kao i klasa, kao i blok
    @Override
    public synchronized void transfer(int from, int to, int amount) {
        while (this.accounts[from] < amount) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        System.out.println(Thread.currentThread());

        this.accounts[from] -= amount;
        this.accounts[to] += amount;
        System.out.println("transfer from " + from + " to " + to + " amount: " + amount);
        System.out.println("total balance: " + this.getTotalBalance());
    }

    public void transferAlternate(int from, int to, int amount) {
        synchronized (this) {
            while (this.accounts[from] < amount) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            System.out.println(Thread.currentThread());
            this.accounts[from] -= amount;
            this.accounts[to] += amount;
            this.notifyAll();
        }

        System.out.println("transfer from " + from + " to " + to + " amount: " + amount);
        System.out.println("total balance: " + this.getTotalBalance());
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
