import java.util.*;

public class Warehouse {
    private final int capacity;
    private final List<Product> storage = new ArrayList<>();

    // ANSII codes
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_RESET = "\u001B[0m";

    public Warehouse(int capacity) {
        this.capacity = capacity;
    }

    public synchronized boolean addProduct(Product p) {
        if (storage.size() >= capacity) {
            System.out.println(ANSI_RED + "Failed to accept: " + p.type + " (" + p.quantity + ")" + ANSI_RESET);
            
            return false;
        } 
        storage.add(p);
        System.out.println(ANSI_GREEN + "Produced: " + p + ANSI_RESET);
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
            System.out.println(ANSI_YELLOW + "Consumed: " + type + " (" + quantity + ")" + ANSI_RESET);
            return true;
        } else {
            System.out.println(ANSI_RED + "Failed to consume: " + type + " (" + quantity + ")" + ANSI_RESET);
            return false;
        }
    }

    public synchronized void printStatus() {
        System.out.println(ANSI_PURPLE + "\nCurrent warehouse: " + storage + "\n" + ANSI_RESET);
    }
}
