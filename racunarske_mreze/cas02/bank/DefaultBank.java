package bank;

import java.util.Arrays;

public class DefaultBank implements IBank {

    private final int[] accounts;

    public DefaultBank(int accountsNum, int initialBalance) {
        this.accounts = new int[accountsNum];
        Arrays.fill(accounts, initialBalance);
    }

    @Override
    public void transfer(int from, int to, int amount) {
        if(this.accounts[from] < amount) {
            return;
        }
        System.out.println(Thread.currentThread());

        this.accounts[from] -= amount;
        this.accounts[to] += amount;
        System.out.println("transfer from " + from + " to " + to + " amount: " + amount);

        System.out.println("total balance: " + this.getTotalBalance());
    }

    @Override
    public int getTotalBalance() {
        return Arrays.stream(accounts).sum(); // otvorimo strim nad nizom i prosumiramo vrednosti
    }

    @Override
    public int count() {
        return accounts.length;
    }
}
