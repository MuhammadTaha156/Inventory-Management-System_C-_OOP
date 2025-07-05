#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Product class to represent individual items
class Product
{
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters
    void setPrice(double newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

    // Display product information
    void display() const
    {
        cout << "ID: " << id << "\tName: " << name
             << "\tPrice: PKR" << price << "\tQuantity: " << quantity << endl;
    }

    // Update quantity (add or remove)
    void updateQuantity(int amount)
    {
        quantity += amount;
        if (quantity < 0)
            quantity = 0;
    }
};

// Inventory class to manage collection of products
class Inventory
{
private:
    vector<Product> products;
    int nextId;

public:
    Inventory() : nextId(1) {}

    // Add a new product to inventory
    void addProduct(const string &name, double price, int quantity)
    {
        Product newProduct(nextId++, name, price, quantity);
        products.push_back(newProduct);
        cout << "Product added successfully!" << endl;
    }

    // Find product by ID (returns pointer or nullptr if not found)
    Product *findProduct(int id)
    {
        for (auto &product : products)
        {
            if (product.getId() == id)
            {
                return &product;
            }
        }
        return nullptr;
    }

    // Update product information
    void updateProduct(int id, double newPrice, int newQuantity)
    {
        Product *product = findProduct(id);
        if (product)
        {
            product->setPrice(newPrice);
            product->setQuantity(newQuantity);
            cout << "Product updated successfully!" << endl;
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }

    // Delete a product
    void deleteProduct(int id)
    {
        for (auto it = products.begin(); it != products.end(); ++it)
        {
            if (it->getId() == id)
            {
                products.erase(it);
                cout << "Product deleted successfully!" << endl;
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    // Display all products
    void listProducts() const
    {
        if (products.empty())
        {
            cout << "Inventory is empty." << endl;
            return;
        }

        cout << "\n===== Inventory List =====" << endl;
        for (const auto &product : products)
        {
            product.display();
        }
        cout << "=========================" << endl;
    }

    // Process sale (reduce quantity)
    void processSale(int id, int quantitySold)
    {
        Product *product = findProduct(id);
        if (product)
        {
            if (product->getQuantity() >= quantitySold)
            {
                product->updateQuantity(-quantitySold);
                double total = quantitySold * product->getPrice();
                cout << "Sale processed successfully!" << endl;
                cout << "Total: PKR " << total << endl;
            }
            else
            {
                cout << "Not enough quantity in stock!" << endl;
            }
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }

    // Process restock (increase quantity)
    void processRestock(int id, int quantityAdded)
    {
        Product *product = findProduct(id);
        if (product)
        {
            product->updateQuantity(quantityAdded);
            cout << "Restock processed successfully!" << endl;
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }
};

// Utility functions
void displayMenu()
{
    cout << "\n===== Inventory Management System =====" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Update Product" << endl;
    cout << "3. Delete Product" << endl;
    cout << "4. List All Products" << endl;
    cout << "5. Process Sale" << endl;
    cout << "6. Process Restock" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

int getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double getDoubleInput(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getStringInput(const string &prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int main()
{
    Inventory inventory;
    int choice;

    do
    {
        displayMenu();
        choice = getIntInput("");

        switch (choice)
        {
        case 1:
        {
            string name = getStringInput("Enter product name: ");
            double price = getDoubleInput("Enter product price: ");
            int quantity = getIntInput("Enter product quantity: ");
            inventory.addProduct(name, price, quantity);
            break;
        }
        case 2:
        {
            int id = getIntInput("Enter product ID to update: ");
            double newPrice = getDoubleInput("Enter new price: ");
            int newQuantity = getIntInput("Enter new quantity: ");
            inventory.updateProduct(id, newPrice, newQuantity);
            break;
        }
        case 3:
        {
            int id = getIntInput("Enter product ID to delete: ");
            inventory.deleteProduct(id);
            break;
        }
        case 4:
            inventory.listProducts();
            break;
        case 5:
        {
            int id = getIntInput("Enter product ID sold: ");
            int quantity = getIntInput("Enter quantity sold: ");
            inventory.processSale(id, quantity);
            break;
        }
        case 6:
        {
            int id = getIntInput("Enter product ID to restock: ");
            int quantity = getIntInput("Enter quantity to add: ");
            inventory.processRestock(id, quantity);
            break;
        }
        case 7:
            cout << "Exiting system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    system("pause");
    system("cls");
    return 0;
}