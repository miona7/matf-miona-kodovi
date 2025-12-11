package bank;

public class BankTest {
    private static final int ACCOUNTS = 5;
    private static final int INITBALANCE = 1000;

    public static void main(String[] args) {
        IBank bank = new DefaultBank(ACCOUNTS,  INITBALANCE);
        // IBank bank = new LockedBank(ACCOUNTS,  INITBALANCE);
        // IBank bank = new SinhronizedBank(ACCOUNTS,  INITBALANCE);

        for (int i = 0; i < ACCOUNTS; i++) {
            TransferRunnable r1 = new TransferRunnable(bank, i, 10);
            Thread t1 = new Thread(r1);
            t1.start();
        }
    }
}
