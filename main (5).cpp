#include <iostream> // Required for input/output operations
#include <string>   // Required for string handling
#include <limits>   // Required for numeric limits

using namespace std;

// Constants for maximum inventory items
const int MAX_ITEMS = 100;
#define Max_Prod 100

// Product struct to hold product details
struct Product {
	string name;
	int quantity;
	double price;
};
// Function to add a new product to the catalog
// Parameters:
// - productCount: reference to the current count of products in the catalog (updated in this function)
// - nextID: reference to the next product ID (not used directly but could track product IDs in future expansions)
// - catalog: array of Product structures that holds the inventory items
void addProduct(int &productCount, int &nextID, Product catalog[]);

// Function to display all products currently in the catalog
// Parameters:
// - productCount: current number of products in the catalog
// - catalog: array of Product structures representing the inventory
void viewProducts(int productCount, Product catalog[]);

// Function to edit an existing product's details in the catalog
// Parameters:
// - productCount: current number of products in the catalog
// - catalog: array of Product structures representing the inventory
void editProduct(int productCount, Product catalog[]);

// Function to delete a product from the catalog
// Parameters:
// - productCount: reference to the current count of products in the catalog (updated in this function)
// - catalog: array of Product structures representing the inventory
void deleteProduct(int &productCount, Product catalog[]);

// Function to validate numeric input from the user
// This function returns true if the input is valid and false if it's invalid
bool isValidInput();

// Function to display the available products in the catalog (used for point-of-sale operations)
// Parameters:
// - catalog: constant array of Product structures representing the inventory
// - size: the number of products in the catalog
void displayProducts(const Product catalog[], int size);

// Function to display the receipt for purchased items
// Parameters:
// - purchasedItems: array of Product structures representing the items bought by the customer
// - itemCount: the number of items in the purchasedItems array
void displayReceipt(const Product purchasedItems[], int itemCount);


int main() {
	Product catalog[Max_Prod];       // Array to hold inventory of products
	Product purchasedItems[MAX_ITEMS]; // Array to hold purchased items

	int productCount = 0; // Tracks number of products in the inventory
	int nextID = 1;       // ID tracker for each product (not used in current version)
	int itemCount = 0;    // Count of items purchased in POS system
	int choice;           // Holds user choice from menu

	do {
		system("clear"); // Clear the console screen
		cout << "\nSystem Menu\n"; //print "System Menu"
		cout << "1. Inventory Management\n"; //print "Inventory Management"
		cout << "2. Point of Sale (POS)\n"; //print "Point of Sale"
		cout << "3. Exit\n"; //print "Exit"
		cout << "Enter your choice: "; //print "Enter your choice"

		// Validate input for menu choice
		if (!isValidInput()) { //if the input is not valid, display the following
			cout << "Invalid input! Please enter a number.\n"; //print "Invalid input! Please enter a number" if the input is not a number
			continue; // Restart loop if input is invalid
		}

		cin >> choice; // store the input in the variable choice

		switch (choice) { //check what the stored value of choice is
		case 1: { // Inventory Management Menu
			int inventoryChoice; // create a variable to store the value of the user input 
			do { 
				system("clear"); // Clear the console screen
				cout << "\nInventory Management System\n"; // print "Inventory Management System"
				cout << "1. Add Product\n"; // print "Add Product"
				cout << "2. View Products\n"; // print "View Product"
				cout << "3. Edit Product\n"; // print "Edit Product"
				cout << "4. Delete Product\n"; // print "Delete Product"
				cout << "5. Back to Main Menu\n"; // print "Back to Main Menu"
				cout << "Enter your choice: "; // print "Enter your choice"

				// Validate input for inventory choice
				if (!isValidInput()) { // if 
					cout << "Invalid input! Please enter a number.\n";
					continue; // Restart loop if input is invalid
				}

				cin >> inventoryChoice;

				// Execute appropriate function based on inventory choice
				switch (inventoryChoice) {
				case 1:
					addProduct(productCount, nextID, catalog);
					break;
				case 2:
					viewProducts(productCount, catalog);
					break;
				case 3:
					editProduct(productCount, catalog);
					break;
				case 4:
					deleteProduct(productCount, catalog);
					break;
				case 5:
					cout << "Returning to Main Menu...\n";
					break;
				default:
					cout << "Invalid choice! Please enter a valid option.\n";
					break;
				}
			} while (inventoryChoice != 5); // Loop until user chooses to go back
			break;
		}
		case 2: { // POS System
			system("clear");
			char continueShopping;
			cout << "Welcome to the POS system!\n";

			do {
				// Display the product catalog for selection
				displayProducts(catalog, productCount);

				// Prompt user to select a product by entering its number
				int productIndex;
				cout << "Enter the number of the item to purchase: ";
				cin >> productIndex;

				// Check if selected product is within valid range
				if (productIndex >= 1 && productIndex <= productCount) {
					Product &selectedProduct = catalog[productIndex - 1];
					if (selectedProduct.quantity > 0) {
						int quantity;
						cout << "Enter quantity to purchase: ";
						cin >> quantity;

						// Check if requested quantity is available
						if (quantity > 0 && quantity <= selectedProduct.quantity) {
							selectedProduct.quantity -= quantity; // Deduct from stock

							// Add each item to purchased items array based on quantity
							for (int i = 0; i < quantity; ++i) {
								purchasedItems[itemCount++] = selectedProduct;
							}

							cout << quantity << " " << selectedProduct.name << "(s) added to the cart.\n";
						} else {
							cout << "Insufficient stock for " << selectedProduct.name << ".\n";
						}
					} else {
						cout << "Sorry, " << selectedProduct.name << " is out of stock.\n";
					}
				} else {
					cout << "Invalid choice, please select a valid product.\n";
				}

				// Ask if user wants to purchase another item
				cout << "Do you want to purchase another item? (y/n): ";
				cin >> continueShopping;
			} while ((continueShopping == 'y' || continueShopping == 'Y') && itemCount < MAX_ITEMS);

			// After shopping, display the receipt
			displayReceipt(purchasedItems, itemCount);
			cout << "Thank you for shopping with us!\n";
			break;
		}
		case 3:
			cout << "Exiting the system...\n";
			break;
		default:
			cout << "Invalid choice! Please enter a valid option.\n";
			break;
		}
	} while (choice != 3); // Loop until user exits
	
	return 0;
}

// Function to add a product to the inventory
void addProduct(int &productCount, int &nextID, Product catalog[]) {
	if (productCount < Max_Prod) {
		Product newProduct;
		cout << "Enter product name: ";
		cin.ignore();
		getline(cin, newProduct.name);

		cout << "Enter quantity: ";
		cin >> newProduct.quantity;

		cout << "Enter price: ";
		cin >> newProduct.price;

		catalog[productCount++] = newProduct; // Add product to catalog
		cout << "Product added successfully!\n";
	} else {
		cout << "Inventory is full! Cannot add more products.\n";
	}
}

// Function to display all products in the inventory
void viewProducts(int productCount, Product catalog[]) {
	if (productCount == 0) {
		cout << "No products in the inventory.\n";
	} else {
		cout << "\nInventory List:\n";
		for (int i = 0; i < productCount; i++) {
			cout << i + 1 << ". Name: " << catalog[i].name
			     << ", Quantity: " << catalog[i].quantity
			     << ", Price: ₱" << catalog[i].price << endl;
		}
	}

	// Wait for the user to press Enter to clear the screen
	cout << "\nPress Enter to return to the inventory menu...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
	cin.get(); // Wait for Enter key
	system("clear"); // Clear screen
}

// Function to edit an existing product in the inventory
void editProduct(int productCount, Product catalog[]) {
	int productIndex;
	cout << "Enter the product number to edit: ";
	cin >> productIndex;

	if (productIndex > 0 && productIndex <= productCount) {
		Product &product = catalog[productIndex - 1];
		cout << "Enter new name (current: " << product.name << "): ";
		cin.ignore();
		getline(cin, product.name);

		cout << "Enter new quantity (current: " << product.quantity << "): ";
		cin >> product.quantity;

		cout << "Enter new price (current: $" << product.price << "): ";
		cin >> product.price;

		cout << "Product updated successfully!\n";
	} else {
		cout << "Invalid product number!\n";
	}
}

// Function to delete a product from the inventory
void deleteProduct(int &productCount, Product catalog[]) {
	int productIndex;
	cout << "Enter the product number to delete: ";
	cin >> productIndex;

	if (productIndex > 0 && productIndex <= productCount) {
		// Shift all items after deleted item to fill the gap
		for (int i = productIndex - 1; i < productCount - 1; i++) {
			catalog[i] = catalog[i + 1];
		}
		productCount--; // Decrement product count
		cout << "Product deleted successfully!\n";
	} else {
		cout << "Invalid product number!\n";
	}
}

// Function to display products for POS
void displayProducts(const Product catalog[], int size) {
	cout << "Available Products:\n";
	for (int i = 0; i < size; ++i) {
		cout << i + 1 << ". " << catalog[i].name
		     << " - ₱" << catalog[i].price
		     << " (Stock: " << catalog[i].quantity << ")\n";
	}
}

// Function to display receipt with purchased items and calculate change
void displayReceipt(const Product purchasedItems[], int itemCount) {
	double subtotal = 0.0;

	cout << "\nReceipt:\n";
	for (int i = 0; i < itemCount; ++i) {
		cout << purchasedItems[i].name << " - ₱" << purchasedItems[i].price << endl;
		subtotal += purchasedItems[i].price; // Add item price to subtotal
	}

	cout << "\nSubtotal: ₱" << subtotal;

	double payment;
	cout << "\nEnter payment amount: ₱";
	cin >> payment;

	if (payment < subtotal) {
		cout << "Insufficient payment. Transaction cannot be completed.\n";
	} else {
		double change = payment - subtotal;
		cout << "Total: ₱" << subtotal << endl;
		cout << "Payment: ₱" << payment << endl;
		cout << "Change: ₱" << change << endl;
	}

	// Wait for user confirmation before clearing the receipt
	cout << "\nPress Enter to return to the main menu...";
	cin.ignore();
	cin.get(); // Wait for Enter key

	// Clear the screen after displaying the receipt
	system("clear");
}

// Function to validate numeric input and handle input errors
bool isValidInput() {
	if (cin.fail()) { // Check if previous input failed
		cin.clear(); // Clear the error flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
		return false; // Indicate invalid input
	}
	return true; // Indicate valid input
}
