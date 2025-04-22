import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        int numProducers = 3;
        int numConsumers = 3;
        int capacity = 10;

        final int print_interval = 1000;

        Warehouse warehouse = new Warehouse(capacity);
        Controller controller = new Controller();
        ExecutorService pool = Executors.newFixedThreadPool(numProducers + numConsumers);

        for (int i = 0; i < numProducers; i++) {
            pool.submit(new Producer(warehouse, controller));
        }

        for (int i = 0; i < numConsumers; i++) {
            pool.submit(new Consumer(warehouse, controller));
        }

        // Thread that prints warehouse status periodically
        Thread statusPrinter = new Thread(() -> {
            while (!controller.stopRequested) {
                warehouse.printStatus();
                try {
                    Thread.sleep(print_interval);
                } catch (InterruptedException ignored) {}
            }
        });
        statusPrinter.start();

        // Wait for user to press ENTER
        System.out.println("Press ENTER to stop...");
        try (Scanner scanner = new Scanner(System.in)) {
            scanner.nextLine();
        }

        controller.stopRequested = true;
        pool.shutdown();

        System.out.println("All threads requested to stop.");
    }
}
