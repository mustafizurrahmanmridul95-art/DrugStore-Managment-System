
import java.util.ArrayList;
import java.util.Scanner;

abstract class Product {
    private String productId;
    private String name;
    protected double price;

    public Product(String productId, String name, double price) {
        this.productId = productId;
        this.name = name;
        this.price = price;
    }

    public String getProductId() { return productId; }
    public String getName() { return name; }
    public double getPrice() { return price; }

    public abstract void displayDetails();
    public abstract boolean sell(int quantity);

    public double calculateTotal(int quantity) {
        return price * quantity;
    }
}

class Medicine extends Product {
    private int stockQuantity;
    private String expiryDate;
    private String manufacturer;

    public Medicine(String productId, String name, double price,
                    int stockQuantity, String expiryDate, String manufacturer) {
        super(productId, name, price);
        this.stockQuantity = stockQuantity;
        this.expiryDate = expiryDate;
        this.manufacturer = manufacturer;
    }

    public int getStockQuantity() { return stockQuantity; }

    public void displayDetails() {
        System.out.println("Product ID   : " + getProductId());
        System.out.println("Name         : " + getName());
        System.out.println("Price        : " + getPrice() + " BDT");
        System.out.println("Stock        : " + stockQuantity);
        System.out.println("Expiry Date  : " + expiryDate);
        System.out.println("Manufacturer : " + manufacturer);
    }

    @Override
    public boolean sell(int quantity) {
        if (stockQuantity >= quantity && quantity > 0) {
            stockQuantity -= quantity;
            return true;
        }
        return false;
    }
}

class TabletMedicine extends Medicine {
    private int tabletsPerStrip;

    public TabletMedicine(String productId, String name, double price,
                          int stockQuantity, String expiryDate, String manufacturer,
                          int tabletsPerStrip) {
        super(productId, name, price, stockQuantity, expiryDate, manufacturer);
        this.tabletsPerStrip = tabletsPerStrip;
    }

    public void displayDetails() {
        super.displayDetails();
        System.out.println("Type         : Tablet");
        System.out.println("Tablets/Strip: " + tabletsPerStrip);
        System.out.println("-----------------------------------");
    }
}

// ==================== SyrupMedicine.java ====================
class SyrupMedicine extends Medicine {
    private double volumeMl;

    public SyrupMedicine(String productId, String name, double price,
                         int stockQuantity, String expiryDate, String manufacturer,
                         double volumeMl) {
        super(productId, name, price, stockQuantity, expiryDate, manufacturer);
        this.volumeMl = volumeMl;
    }


    public void displayDetails() {
        super.displayDetails();
        System.out.println("Type         : Syrup");
        System.out.println("Volume       : " + volumeMl + " ml");
        System.out.println("-----------------------------------");
    }
}

class Pharmacy {
    private ArrayList<Product> inventory = new ArrayList<>();

    public void addProduct(Product product) {
        inventory.add(product);
        System.out.println("OK " + product.getName() + " added successfully!");
    }

    public void displayInventory() {
        if (inventory.isEmpty()) {
            System.out.println("No medicines in stock.");
            return;
        }
        System.out.println("\n=== CURRENT INVENTORY ===");
        for (Product p : inventory) {
            p.displayDetails();
        }
    }

    public void sellProduct(String productId, int quantity) {
        for (Product p : inventory) {
            if (p.getProductId().equalsIgnoreCase(productId)) {
                if (p.sell(quantity)) {
                    System.out.println("\n✅ Sale Successful!");
                    System.out.println("Medicine: " + p.getName() + " | Total: " + p.calculateTotal(quantity) + " BDT");
                } else {
                    System.out.println("❌ Insufficient stock!");
                }
                return;
            }
        }
        System.out.println("❌ Product not found!");
    }
}

// ==================== PharmacyApp.java ====================
// This is the main class. Ensure your file is named PharmacyApp.java
public class PharmacyApp {
    public static void main(String[] args) {
        Pharmacy pharmacy = new Pharmacy();
        Scanner scanner = new Scanner(System.in);

        // Sample Data
        pharmacy.addProduct(new TabletMedicine("T01", "Napa", 10, 100, "2026-01-01", "Beximco", 10));

        while (true) {
            System.out.println("\n1. Add Medicine\n2. View Inventory\n3. Sell\n4. Exit");
            System.out.print("Choice: ");
            String choice = scanner.nextLine();

            if (choice.equals("1")) {
                System.out.print("Type (Tablet/Syrup): "); String type = scanner.nextLine();
                System.out.print("ID: "); String id = scanner.nextLine();
                System.out.print("Name: "); String name = scanner.nextLine();
                System.out.print("Price: "); double pr = Double.parseDouble(scanner.nextLine());
                System.out.print("Stock: "); int st = Integer.parseInt(scanner.nextLine());

                if (type.equalsIgnoreCase("Tablet")) {
                    pharmacy.addProduct(new TabletMedicine(id, name, pr, st, "2027-01-01", "Unknown", 10));
                } else {
                    pharmacy.addProduct(new SyrupMedicine(id, name, pr, st, "2027-01-01", "Unknown", 100));
                }
            } else if (choice.equals("2")) {
                pharmacy.displayInventory();
            } else if (choice.equals("3")) {
                System.out.print("ID: "); String sid = scanner.nextLine();
                System.out.print("Qty: "); int sq = Integer.parseInt(scanner.nextLine());
                pharmacy.sellProduct(sid, sq);
            } else if (choice.equals("4")) {
                break;
            }
        }
        scanner.close();
    }
}

