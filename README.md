# Supermarket Billing System (C++)

**Student Name:** Sartaj Singh  
**Student UID:** 25BCA20026  
**Project:** Supermarket Billing System  
**Subject:** Object-Oriented Programming (OOP)

## Project Description

The Supermarket Billing System is a menu-driven C++ console application developed using Object-Oriented Programming concepts. It helps a supermarket manage a sample product catalogue, add products to a shopping cart, calculate item totals, apply a discount and GST, and generate a customer bill.

This is an academic demonstration project. Product prices, stock quantities, discount rules, and the GST rate are sample values that can be changed in the source code.

## Features

- Displays a product catalogue with product IDs, prices, and available stock.
- Adds products and quantities to a shopping cart.
- Updates the cart when the same product is selected again.
- Checks product IDs, quantities, and available stock.
- Displays the shopping cart and subtotal.
- Removes products from the cart and restores their stock.
- Applies a 5% discount when the subtotal is ₹2,000 or more.
- Calculates 5% GST on the amount after discount.
- Generates a formatted invoice with customer name, date, item details, and grand total.
- Uses a simple menu-driven interface.

## OOP Concepts Used

| OOP Concept | Implementation |
|---|---|
| Classes and Objects | `Product`, `CartItem`, and `Supermarket` classes |
| Encapsulation | Data members are private and accessed through public methods |
| Constructors | Initialize products and cart items |
| Abstraction | Billing and inventory operations are handled through class methods |
| Composition / Association | `Supermarket` manages products and cart items; each cart item refers to a product |

## Technologies Used

- C++
- Standard Template Library (STL): `vector`, `string`
- Object-Oriented Programming
- Console Input / Output

## Project Structure

```text
Supermarket-Billing-System/
│
├── Supermarket_Billing_System.cpp
├── README.md
└── LICENSE
```

## Requirements

- A C++ compiler that supports **C++11 or later** (C++17 recommended).
- Code::Blocks, Visual Studio Code, Visual Studio, or any compatible C++ IDE.

## How to Compile and Run

### Using g++

1. Open a terminal in the project folder.
2. Compile the program:

```bash
g++ -std=c++17 Supermarket_Billing_System.cpp -o supermarket
```

3. Run it:

**Windows**
```bash
supermarket.exe
```

**Linux / macOS**
```bash
./supermarket
```

### Using Code::Blocks

1. Open Code::Blocks.
2. Create a new Console Application in C++ or open the `.cpp` file.
3. Paste or add the source code.
4. Build and Run the project.

## Billing Rules

- **Subtotal:** Sum of price × quantity for all cart items.
- **Discount:** 5% of subtotal when subtotal is ₹2,000 or more; otherwise ₹0.
- **GST:** 5% of the amount after discount.
- **Grand Total:** Subtotal − Discount + GST.

These are sample academic billing rules, not a representation of any particular store's actual tax policy.

## Author

**Sartaj Singh**  
**UID:** 25BCA20026

---

Made as an Object-Oriented Programming project using C++.
