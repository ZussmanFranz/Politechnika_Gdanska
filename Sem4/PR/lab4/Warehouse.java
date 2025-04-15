import java.util.*;

public class Warehouse {
    private final int capacity;
    private final List<Product> storage = new ArrayList<>();

    // ANSII codes
    public static final String ANSI_GREEN = "\u001B[32m";

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public synchronized boolean addProduct(Product p) {
        if (storage.size() >= capacity) return false;
        storage.add(p);
        System.out.println("Produced: " + p);
        return true;
    }

    public synchronized boolean consumeProduct(String type, int quantity) {
        int total = 0;
        Iterator<Product> it = storage.iterator();

        while (it.hasNext() && total < quantity) {
            Product p = it.next();
            if (p.type.equals(type)) {
                total += p.quantity;
                it.remove();
            }
        }

        if (total >= quantity) {
            System.out.println("Consumed: " + type + " (" + quantity + ")");
            return true;
        } else {
            System.out.println("Failed to consume: " + type + " (" + quantity + ")");
            return false;
        }
    }

    public synchronized void printStatus() {
        System.out.println("\nCurrent warehouse: " + storage + "\n");
    }
}
