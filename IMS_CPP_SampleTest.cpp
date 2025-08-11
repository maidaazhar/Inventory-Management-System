#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_CATEGORIES = 20;

// Declare global arrays
string productNames[MAX_PRODUCTS];
string productCategories[MAX_PRODUCTS];
int productQuantities[MAX_PRODUCTS];
double productPrices[MAX_PRODUCTS];
double originalPrices[MAX_PRODUCTS];
int productCount = 0; // Global product count
string categories[MAX_CATEGORIES];
int categoryCount = 0; // Global category count

void addSampleData();

// Function prototypes
void addProduct(string names[], string categories[], int quantities[], double prices[], int& productCount);
void updateProduct(string names[], string categories[], int quantities[], double prices[], int productCount);
void removeProduct(string names[], string categories[], int quantities[], double prices[], int& productCount);
void ProductManagement();
void manageCategories(string categories[], int& categoryCount);
void filterByCategory(string names[], string categories[], int quantities[], double prices[], int productCount, string categoryFilter);
void lowStockAlert(string names[], int quantities[], int productCount, int threshold);
void applyDiscount(double discount);
void undoDiscount(string names[], double prices[], double originalPrices[], int productCount);
void displayProducts();
void InventoryTracking();
void reportanalysis(string names[], string categories[], int quantities[], double prices[], int productCount);
void calculateInventoryValue(string names[], int quantities[], double prices[], int productCount);
void calculateInventoryValueByCategory(string names[], string categories[], int quantities[], double prices[], int productCount, const string& categoryFilter);
void forecastRevenue(string names[], double prices[], int quantities[], int productCount, const string& season, double seasonalityAdjustment);

// Main function
int main() {
    // Add sample data
    addSampleData();
    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Product Management\n";
        cout << "2. Inventory Tracking\n";
        cout << "3. Reporting & Analysis\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ProductManagement();  // Product management tasks
            break;
        case 2:
            InventoryTracking();  // Inventory tracking tasks
            break;
        case 3:
            reportanalysis(productNames, productCategories, productQuantities, productPrices, productCount);
            break;
        case 0:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

void addSampleData() {
    productNames[0] = "Laptop";
    productCategories[0] = "Electronics";
    productQuantities[0] = 10;
    productPrices[0] = 999.99;

    productNames[1] = "Headphones";
    productCategories[1] = "Electronics";
    productQuantities[1] = 30;
    productPrices[1] = 49.99;

    productNames[2] = "Mouse";
    productCategories[2] = "Electronics";
    productQuantities[2] = 20;
    productPrices[2] = 19.99;

    productCount = 3;
}

void addProduct(string names[], string categories[], int quantities[], double prices[], int& productCount) {
    // Check if inventory is full (can't add more products if full)
    if (productCount >= MAX_PRODUCTS) {
        cout << "Inventory full! Cannot add more products." << endl;
        return;
    }
    string newName, newCategory;
    int newQuantity;
    double newPrice;
    // Ask for the product name
    cout << "Enter product name: ";
    cin >> newName;
    // Check if the product already exists (no duplicates allowed)
    for (int i = 0; i < productCount; i++) {
        if (names[i] == newName) {
            cout << "Product already exists. Cannot add duplicate product." << endl;
            return;
        }
    }
    // Ask for the product category (e.g., electronics, groceries, etc.)
    cout << "Enter category (electronics, groceries, etc.): ";
    cin >> newCategory;
    // Ask for the quantity and make sure it's a positive number
    do {
        cout << "Enter quantity (positive number): ";
        cin >> newQuantity;
        if (newQuantity < 0) cout << "Quantity cannot be negative. Try again." << endl;
    } while (newQuantity < 0);  // Keep asking until valid quantity
    // Ask for the price and make sure it's a positive number
    do {
        cout << "Enter price (positive number): ";
        cin >> newPrice;
        if (newPrice < 0) cout << "Price cannot be negative. Try again." << endl;
    } while (newPrice < 0);  // Keep asking until valid price
    // Store the new product in arrays (lists)
    names[productCount] = newName;
    categories[productCount] = newCategory;
    quantities[productCount] = newQuantity;
    prices[productCount] = newPrice;
    productCount++;  // Increase the count of products
    // Let the user know the product was added successfully
    cout << "Product added successfully!" << endl;
}
// Function to update product information (price or quantity)
void updateProduct(string names[], string categories[], int quantities[], double prices[], int productCount) {
    string productName;
    cout << "Enter product name to update: ";
    cin >> productName;
    bool found = false;  // Flag to check if the product is found
    for (int i = 0; i < productCount; i++) {
        if (names[i] == productName) {
            found = true;  // We found the product, now let's update it!
            int choice;
            cout << "What do you want to update? 1. Price  2. Quantity" << endl;
            cin >> choice;
            // If user chooses to update the price
            if (choice == 1) {
                cout << "Enter new price: ";
                cin >> prices[i];
                if (prices[i] < 0) {
                    cout << "Price cannot be negative. Update failed." << endl;
                    prices[i] = 0;  // Reset price if invalid
                }
                else {
                    cout << "Price updated successfully!" << endl;
                }
            }
            // If user chooses to update the quantity
            else if (choice == 2) {
                cout << "Enter new quantity: ";
                cin >> quantities[i];
                if (quantities[i] < 0) {
                    cout << "Quantity cannot be negative. Update failed." << endl;
                    quantities[i] = 0;  // Reset quantity if invalid
                }
                else {
                    cout << "Quantity updated successfully!" << endl;
                }
            }
            else {
                cout << "Oops! Invalid choice!" << endl;  // If user enters anything else
            }
            break;  // Break out of the loop once the product is found
        }
    }
    // If the product wasn't found, tell the user
    if (!found) {
        cout << "Product not found!" << endl;
    }
}
// Function to remove a product
void removeProduct(string names[], string categories[], int quantities[], double prices[], int& productCount) {
    string productName;
    cout << "Enter product name to remove: ";
    cin >> productName;
    bool found = false;  // Flag to check if the product is found
    for (int i = 0; i < productCount; i++) {
        if (names[i] == productName) {
            found = true;  // We found the product, now let's remove it!
            char confirm;
            cout << "Are you sure you want to delete this product? (Y/N): ";
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                // Shift all the products after the deleted one to the left
                for (int j = i; j < productCount - 1; j++) {
                    names[j] = names[j + 1];
                    categories[j] = categories[j + 1];
                    quantities[j] = quantities[j + 1];
                    prices[j] = prices[j + 1];
                }
                productCount--;  // Reduce the count of products
                cout << "Product removed successfully!" << endl;
            }
            break;  // Exit the loop after removal
        }
    }
    // If the product wasn't found, tell the user
    if (!found) {
        cout << "Product not found!" << endl;
    }
}
// Menu function for product management tasks
void ProductManagement() {
    int choice;
    do {
        cout << "\nProduct Management Menu:" << endl;
        cout << "1. Add New Product" << endl;
        cout << "2. Update Product Information" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Display All Product" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct(productNames, productCategories, productQuantities, productPrices, productCount);
            break;
        case 2:
            updateProduct(productNames, productCategories, productQuantities, productPrices, productCount);
            break;
        case 3:
            removeProduct(productNames, productCategories, productQuantities, productPrices, productCount);
            break;
        case 4:
            displayProducts();
            break;
        case 0:
            cout << "Exiting Product Management. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}
// Function to create and manage categories
void manageCategories(string categories[], int& categoryCount) {
    string newCategory;
    // Ask the user to input a new category
    cout << "Enter new category name: ";
    cin >> newCategory;
    // Check if category already exists
    for (int i = 0; i < categoryCount; i++) {
        if (categories[i] == newCategory) {
            cout << "Category already exists! Try a different name." << endl;
            return;
        }
    }
    // If there's space, add the new category to the list
    if (categoryCount < MAX_CATEGORIES) {
        categories[categoryCount] = newCategory;
        categoryCount++; // Increase category count
        cout << "Category added successfully!" << endl;
    }
    else {
        cout << "Maximum category limit reached!" << endl;
    }
}
// Function to display products by category
void filterByCategory(string names[], string categories[], int quantities[], double prices[], int productCount, string categoryFilter) {
    cout << "Products in category: " << categoryFilter << endl;
    bool found = false;
    for (int i = 0; i < productCount; i++) {
        if (categories[i] == categoryFilter) {
            cout << "Product: " << names[i] << " | Quantity: " << quantities[i] << " | Price: " << prices[i] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No products found in this category!" << endl;
    }
}
// Function to handle low stock alerts
void lowStockAlert(string names[], int quantities[], int productCount, int threshold) {
    cout << "Low stock products (threshold: " << threshold << "):" << endl;
    bool foundLowStock = false;
    for (int i = 0; i < productCount; i++) {
        if (quantities[i] < threshold) {
            cout << "Product: " << names[i] << " | Quantity: " << quantities[i] << " - Low stock!" << endl;
            foundLowStock = true;
        }
    }
    if (!foundLowStock) {
        cout << "No products are below the low stock threshold." << endl;
    }
}
// Function to apply discount to all products
void applyDiscount(double discount) {
    // Save the original prices before applying the discount
    for (int i = 0; i < productCount; i++) {
        originalPrices[i] = productPrices[i];  // Store the original prices
    }

    cout << "Applying " << discount * 100 << "% discount to products." << endl;
    for (int i = 0; i < productCount; i++) {
        productPrices[i] -= productPrices[i] * discount;  // Apply discount
    }

    // Display updated prices after discount
    displayProducts();
}

// Function to undo discount (revert to original prices)
void undoDiscount(string names[], double prices[], double originalPrices[], int productCount) {
    cout << "Undoing discount. Reverting to original prices." << endl;
    for (int i = 0; i < productCount; i++) {
        prices[i] = originalPrices[i];  // Revert the price back to original
        cout << "Product: " << names[i] << " | Reverted Price: " << prices[i] << endl;
    }
}


// Function to display all products
void displayProducts() {
    // If there are no products, show a message
    if (productCount == 0) {
        cout << "No products available." << endl;
        return;
    }

    // Print the header for the product list
    cout << "\nProduct List:\n";
    cout << "-------------------------------------------------\n";
    cout << "Name\tCategory\tQuantity\tPrice\n";
    cout << "-------------------------------------------------\n";

    // Loop through and display each product's details
    for (int i = 0; i < productCount; i++) {
        cout << productNames[i] << "\t"
            << productCategories[i] << "\t"
            << productQuantities[i] << "\t"
            << productPrices[i] << endl;
    }

    // End of the product list display
    cout << "-------------------------------------------------\n";
}

// Menu function for inventory tracking tasks
void InventoryTracking() {
    int choice;
    do {
        cout << "\nInventory Tracking Menu:" << endl;
        cout << "1. Manage Categories" << endl;
        cout << "2. Filter Products by Category" << endl;
        cout << "3. Set Low Stock Alert" << endl;
        cout << "4. Apply Discount to Products" << endl;
        cout << "5. Undo Discount" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            manageCategories(categories, categoryCount);
            break;
        case 2: {
            string categoryFilter;
            cout << "Enter category to filter by: ";
            cin >> categoryFilter;
            filterByCategory(productNames, productCategories, productQuantities, productPrices, productCount, categoryFilter);
            break;
        }
        case 3: {
            int threshold;
            cout << "Enter low stock threshold: ";
            cin >> threshold;
            if (threshold < 0) {
                cout << "Threshold cannot be negative!" << endl;
            }
            else {
                lowStockAlert(productNames, productQuantities, productCount, threshold);
            }
            break;
        }
        case 4: {
            double discountPercentage;
            cout << "Enter discount percentage (0-100): ";
            cin >> discountPercentage;
            if (discountPercentage >= 0 && discountPercentage <= 100) {
                applyDiscount(discountPercentage / 100);  // Apply the discount as a percentage
            }
            else {
                cout << "Invalid discount percentage!" << endl;
            }
            break;
        }
        case 5:
            undoDiscount(productNames, productPrices, originalPrices, productCount);
            break;
        case 0:
            cout << "Exiting Inventory Tracking. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}
// Reporting & Analysis Functions
void calculateInventoryValueByCategory(string names[], string categories[], int quantities[], double prices[], int productCount, const string& categoryFilter) {
    double totalValue = 0.0;
    for (int i = 0; i < productCount; i++) {
        if (categories[i] == categoryFilter) {
            totalValue += quantities[i] * prices[i];
        }
    }
    cout << "Total inventory value for category '" << categoryFilter << "': " << totalValue << endl;
}

// Function to generate the Low Stock Report
void lowStockReport(string names[], string categories[], int quantities[], double prices[], int productCount, int threshold) {
    cout << "Low Stock Report (Threshold: " << threshold << "):" << endl;
    bool foundLowStock = false;
    for (int i = 0; i < productCount; ++i) {
        if (quantities[i] < threshold) {
            cout << "Product: " << names[i] << " | Quantity: " << quantities[i]
                << " | Category: " << categories[i] << endl;
            foundLowStock = true;
        }
    }
    if (!foundLowStock) {
        cout << "No products are below the low stock threshold." << endl;
    }
}

void forecastRevenue(string names[], double prices[], int quantities[], int productCount, const string& season, double seasonalityAdjustment) {
    double revenueForecast = 0.0;
    for (int i = 0; i < productCount; i++) {
        revenueForecast += prices[i] * quantities[i] * seasonalityAdjustment;
    }
    cout << "Revenue forecast for season '" << season << "': " << revenueForecast << endl;
}

void calculateInventoryValue(string names[], int quantities[], double prices[], int productCount) {
    double totalValue = 0.0;
    for (int i = 0; i < productCount; i++) {
        totalValue += quantities[i] * prices[i];
    }
    cout << "Total inventory value: " << totalValue << endl;
}

void reportanalysis(string names[], string categories[], int quantities[], double prices[], int productCount) {
    int choice;

    do {
        cout << "\nReporting & Analysis Menu:" << endl;
        cout << "1. Generate Low Stock Report" << endl;
        cout << "2. Calculate Total Inventory Value" << endl;
        cout << "3. Calculate Inventory Value by Category" << endl;
        cout << "4. Forecast Revenue Based on Seasonality" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: { // Generate Low Stock Report
            int threshold;
            cout << "Enter low stock threshold: ";
            cin >> threshold;
            if (threshold < 0) {
                cout << "Threshold cannot be negative!" << endl;
            }
            else {
                lowStockReport(names, categories, quantities, prices, productCount, threshold);
            }
            break;
        }
        case 2:
            calculateInventoryValue(names, quantities, prices, productCount); // Corrected arguments
            break;
        case 3: {
            string category;
            cout << "Enter category to filter by: ";
            cin >> category;
            calculateInventoryValueByCategory(names, categories, quantities, prices, productCount, category);
            break;
        }
        case 4: {
            string season;
            double seasonality;
            cout << "Enter season (e.g., Holiday, Off-Season): ";
            cin >> season;
            cout << "Enter seasonality adjustment (-100 to 100): ";
            cin >> seasonality;
            forecastRevenue(names, prices, quantities, productCount, season, seasonality); // Corrected arguments
            break;
        }
        case 0:
            cout << "Exiting Reporting & Analysis. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}
