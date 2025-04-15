import java.util.Random;

public class Producer implements Runnable {
    private final Warehouse warehouse;
    private static final String[] TYPES = {"A", "B", "C"};
    private final Random rand = new Random();
    private final Controller controller;

    public Producer(Warehouse warehouse, Controller controller) {
        this.warehouse = warehouse;
        this.controller = controller;
    }

    @Override
    public void run() {
        while (!controller.stopRequested) {
            String type = TYPES[rand.nextInt(TYPES.length)];
            int quantity = rand.nextInt(5) + 1;
            Product p = new Product(type, quantity);
            warehouse.addProduct(p);
            try {
                Thread.sleep(rand.nextInt(300));
            } catch (InterruptedException ignored) {}
        }
    }
}
