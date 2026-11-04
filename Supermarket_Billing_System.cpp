#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <ctime>
#include <algorithm>

using namespace std;

// Represents one product available in the supermarket.
class Product {
private:
    int id;
    string name;
    double price;
    int stock;

public:
    Product(int productId, const string& productName, double productPrice, int availableStock)
        : id(productId), name(productName), price(productPrice), stock(availableStock) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    bool reduceStock(int quantity) {
        if (quantity <= 0 || quantity > stock) {
            return false;
        }
        stock -= quantity;
        return true;
    }

    void addStock(int quantity) {
        if (quantity > 0) stock += quantity;
    }

    void display() const {
        cout << left << setw(8) << id
             << setw(22) << name
             << right << setw(12) << fixed << setprecision(2) << price
             << setw(12) << stock << '\n';
    }
};

// Represents a product and its selected quantity in the shopping cart.
class CartItem {
private:
    Product* product;
    int quantity;

public:
    CartItem(Product* selectedProduct, int selectedQuantity)
        : product(selectedProduct), quantity(selectedQuantity) {}

    Product* getProduct() const { return product; }
    int getQuantity() const { return quantity; }
    double getTotal() const { return product->getPrice() * quantity; }

    void increaseQuantity(int amount) { quantity += amount; }
};

// Handles the supermarket catalogue, cart, billing and receipt.
class Supermarket {
private:
    vector<Product> products;
    vector<CartItem> cart;
    string customerName;
    const double GST_RATE = 0.05;
    const double DISCOUNT_LIMIT = 2000.00;
    const double DISCOUNT_RATE = 0.05;

    Product* findProduct(int productId) {
        for (Product& product : products) {
            if (product.getId() == productId) {
                return &product;
            }
        }
        return nullptr;
    }

    double calculateSubtotal() const {
        double subtotal = 0.0;
        for (const CartItem& item : cart) {
            subtotal += item.getTotal();
        }
        return subtotal;
    }

    void printLine(char symbol = '-', int length = 64) const {
        cout << string(length, symbol) << '\n';
    }

public:
    Supermarket() {
        // Sample inventory and prices (in Indian Rupees).
        products.emplace_back(101, "Rice (1 kg)", 65.00, 50);
        products.emplace_back(102, "Wheat Flour (1 kg)", 42.00, 45);
        products.emplace_back(103, "Milk (1 litre)", 58.00, 40);
        products.emplace_back(104, "Cooking Oil (1 litre)", 145.00, 30);
        products.emplace_back(105, "Sugar (1 kg)", 48.00, 35);
        products.emplace_back(106, "Tea (250 g)", 120.00, 25);
        products.emplace_back(107, "Soap (1 piece)", 35.00, 60);
        products.emplace_back(108, "Biscuits (pack)", 25.00, 70);
        products.emplace_back(109, "Toothpaste", 95.00, 28);
        products.emplace_back(110, "Shampoo (bottle)", 180.00, 20);
    }

    void displayProducts() const {
        printLine('=');
        cout << "                         PRODUCT CATALOGUE\n";
        printLine('=');
        cout << left << setw(8) << "ID"
             << setw(22) << "Product"
             << right << setw(12) << "Price (Rs.)"
             << setw(12) << "Stock" << '\n';
        printLine();
        for (const Product& product : products) {
            product.display();
        }
        printLine('=');
    }

    void addToCart() {
        int id, quantity;
        cout << "\nEnter Product ID (0 to cancel): ";
        if (!(cin >> id)) {
            recoverInput();
            return;
        }
        if (id == 0) return;

        Product* selected = findProduct(id);
        if (selected == nullptr) {
            cout << "Invalid product ID. Please select an ID from the catalogue.\n";
            return;
        }

        cout << "Enter quantity: ";
        if (!(cin >> quantity)) {
            recoverInput();
            return;
        }
        if (quantity <= 0) {
            cout << "Quantity must be greater than zero.\n";
            return;
        }
        if (quantity > selected->getStock()) {
            cout << "Sorry, only " << selected->getStock() << " unit(s) are available.\n";
            return;
        }

        // If the product is already in the cart, update its quantity.
        for (CartItem& item : cart) {
            if (item.getProduct()->getId() == id) {
                item.increaseQuantity(quantity);
                selected->reduceStock(quantity);
                cout << quantity << " more unit(s) of " << selected->getName()
                     << " added to the cart.\n";
                return;
            }
        }

        selected->reduceStock(quantity);
        cart.emplace_back(selected, quantity);
        cout << selected->getName() << " added to the cart successfully.\n";
    }

    void viewCart() const {
        printLine('=');
        cout << "                           SHOPPING CART\n";
        printLine('=');
        if (cart.empty()) {
            cout << "Your cart is currently empty.\n";
            printLine('=');
            return;
        }

        cout << left << setw(22) << "Product"
             << right << setw(10) << "Price"
             << setw(10) << "Qty"
             << setw(14) << "Amount (Rs.)" << '\n';
        printLine();
        for (const CartItem& item : cart) {
            cout << left << setw(22) << item.getProduct()->getName()
                 << right << setw(10) << fixed << setprecision(2) << item.getProduct()->getPrice()
                 << setw(10) << item.getQuantity()
                 << setw(14) << item.getTotal() << '\n';
        }
        printLine();
        cout << right << setw(42) << "Subtotal: Rs. "
             << setw(14) << calculateSubtotal() << '\n';
        printLine('=');
    }

    void removeFromCart() {
        if (cart.empty()) {
            cout << "Your cart is empty. Nothing to remove.\n";
            return;
        }

        int id;
        cout << "Enter Product ID to remove from cart: ";
        if (!(cin >> id)) {
            recoverInput();
            return;
        }

        for (auto it = cart.begin(); it != cart.end(); ++it) {
            if (it->getProduct()->getId() == id) {
                // Return the removed quantity to inventory.
                Product* product = it->getProduct();
                int quantity = it->getQuantity();

                // Product stock is restored through a small helper operation below.
                // The current stock plus removed quantity is the available stock.
                // Product::addStock is used for this purpose.
                product->addStock(quantity);
                cout << product->getName() << " removed from the cart.\n";
                cart.erase(it);
                return;
            }
        }
        cout << "That product is not present in your cart.\n";
    }

    void checkout() {
        if (cart.empty()) {
            cout << "Your cart is empty. Add products before checkout.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter customer name: ";
        getline(cin, customerName);
        if (customerName.empty()) customerName = "Walk-in Customer";

        const double subtotal = calculateSubtotal();
        const double discount = (subtotal >= DISCOUNT_LIMIT) ? subtotal * DISCOUNT_RATE : 0.0;
        const double taxableAmount = subtotal - discount;
        const double gst = taxableAmount * GST_RATE;
        const double grandTotal = taxableAmount + gst;

        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        printLine('=');
        cout << "                     SUPERMARKET BILL / INVOICE\n";
        cout << "                   Thank you for shopping with us!\n";
        printLine('=');
        cout << "Customer : " << customerName << '\n';
        cout << "Date     : " << put_time(localTime, "%d-%m-%Y %H:%M:%S") << '\n';
        printLine();
        cout << left << setw(22) << "Product"
             << right << setw(10) << "Price"
             << setw(8) << "Qty"
             << setw(14) << "Amount (Rs.)" << '\n';
        printLine();
        for (const CartItem& item : cart) {
            cout << left << setw(22) << item.getProduct()->getName()
                 << right << setw(10) << fixed << setprecision(2) << item.getProduct()->getPrice()
                 << setw(8) << item.getQuantity()
                 << setw(14) << item.getTotal() << '\n';
        }
        printLine();
        cout << left << setw(40) << "Subtotal" << right << "Rs. " << setw(14) << subtotal << '\n';
        cout << left << setw(40) << "Discount" << right << "Rs. " << setw(14) << discount << '\n';
        cout << left << setw(40) << "GST (5%)" << right << "Rs. " << setw(14) << gst << '\n';
        printLine('=');
        cout << left << setw(40) << "GRAND TOTAL" << right << "Rs. "
             << setw(14) << grandTotal << '\n';
        printLine('=');
        cout << "                 Please visit again. Have a great day!\n";
        printLine('=');

        cart.clear();
    }

    void recoverInput() {
        cout << "Invalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void run() {
        int choice;
        cout << "\n";
        printLine('=');
        cout << "                 WELCOME TO SMART SUPERMARKET\n";
        cout << "                    SUPERMARKET BILLING SYSTEM\n";
        printLine('=');

        do {
            cout << "\n1. Display Products\n"
                 << "2. Add Product to Cart\n"
                 << "3. View Shopping Cart\n"
                 << "4. Remove Product from Cart\n"
                 << "5. Generate Bill / Checkout\n"
                 << "0. Exit\n";
            printLine();
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                recoverInput();
                continue;
            }

            switch (choice) {
                case 1: displayProducts(); break;
                case 2: displayProducts(); addToCart(); break;
                case 3: viewCart(); break;
                case 4: removeFromCart(); break;
                case 5: checkout(); break;
                case 0:
                    cout << "\nThank you for using Supermarket Billing System!\n";
                    break;
                default:
                    cout << "Invalid choice. Please select an option from the menu.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    Supermarket supermarket;
    supermarket.run();
    return 0;
}
