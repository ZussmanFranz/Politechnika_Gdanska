import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    public static void main(String[] args) {
        int numProducers = 3;
        int numConsumers = 3;
        int capacity = 10;

        final int print_interval = 3000;
        long from_last_print = System.currentTimeMillis(); // gets start time
        

        Warehouse warehouse = new Warehouse(capacity);
        Controller controller = new Controller();
        ExecutorService pool = Executors.newFixedThreadPool(numProducers + numConsumers);

        for (int i = 0; i < numProducers; i++) {
            pool.submit(new Producer(warehouse, controller));
        }

        for (int i = 0; i < numConsumers; i++) {
            pool.submit(new Consumer(warehouse, controller));
        }

        if (System.currentTimeMillis() - from_last_print >= print_interval) {
            warehouse.printStatus();
            from_last_print = System.currentTimeMillis();
        }


        System.out.println("Press ENTER to stop...");
        new Scanner(System.in).nextLine();

        controller.stopRequested = true;
        pool.shutdown();

        System.out.println("All threads requested to stop.");
    }
}
