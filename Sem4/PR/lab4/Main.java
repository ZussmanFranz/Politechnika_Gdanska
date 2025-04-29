import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        // Parameters
        final int numProducers = 3;
        final int numConsumers = 3;
        
        final int capacity = 10;
        final int sleepTime = 300;

        final int print_interval = 500;

        Warehouse warehouse = new Warehouse(capacity);
        Controller controller = new Controller();
        ExecutorService pool = Executors.newFixedThreadPool(numProducers + numConsumers);

        for (int i = 0; i < numProducers; ++i) {
            pool.submit(new Producer(warehouse, controller, capacity/2, sleepTime));
        }

        for (int i = 0; i < numConsumers; ++i) {
            pool.submit(new Consumer(warehouse, controller, capacity/2, sleepTime));
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
