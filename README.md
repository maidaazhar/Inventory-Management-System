# Inventory Management System

A modular C++ console-based Inventory Management System that allows users to manage products, track inventory, and generate reports.  
Features include product addition, updates, deletion, category management, low-stock alerts, discounts, inventory valuation, and seasonal revenue forecasting.

---

## Features
- **Product Management**: Add, view, update, and delete products.
- **Category Management**: Create and filter by product categories.
- **Low Stock Alerts**: Get notified when stock is running low.
- **Discount Handling**: Apply and undo discounts across products.
- **Inventory Valuation**: Calculate total value or value by category.
- **Revenue Forecasting**: Estimate seasonal revenue changes.
- **Sample Data Function**: `addSampleData()` for quick testing without manual entry.

---

## Sample Data Function
The `addSampleData()` function automatically populates the inventory with:
- Laptop – Qty: 10 – Price: 999.99
- Headphones – Qty: 30 – Price: 49.99
- Mouse – Qty: 20 – Price: 19.99

This is useful for testing and demo purposes.

### Example Code:
// Prototype
void addSampleData();

// Function
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

// Call in main
int main() {
    // Add sample data
    addSampleData();
}
