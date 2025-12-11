public class Zadatak1 {

    // 1. nacin - nasledimo klasu Thread
    private static class MyThread extends Thread {
        @Override
        public void run() {
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println(Thread.currentThread());
        }
    }

    // 2. nacin - implementiramo interfejs Runnable
    private static class MyRunnable implements Runnable {
        @Override
        public void run() {
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println(Thread.currentThread());
        }
    }
    // posto nemamo visestruko nasledjivanje a zelim da nasa klasa bude i nit i da nasledjuje neku drugu klasu onda implementiramo interfejs

    public static void main(String[] args) {
        System.out.println(Thread.currentThread());

        Thread t1 = new MyThread();
        t1.start();

        Thread t2 = new Thread(new MyRunnable());
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println("main thread end");
    }
}
