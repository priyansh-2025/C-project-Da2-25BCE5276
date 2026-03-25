#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define FILE_NAME "inventory.txt"

// 1. Minimum 1 Struct Required
typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Product;

Product inventory[MAX_PRODUCTS];
int productCount = 0;

// Function Prototypes (More than 5 User-Defined Functions)
void loadFromFile();
void saveToFile();
void addProduct();
void updateStock();
void deleteProduct();
void searchProduct();
void lowStockReport();
void showTotalValue();
int findProductIndex(int id);
void clearBuffer();

int main() {
    int choice;
    loadFromFile();

    // Menu-driven program
    do {
        printf("\n========== INVENTORY MANAGEMENT ==========\n");
        printf("1. Add Product\n");
        printf("2. Update Stock\n");
        printf("3. Delete Product\n");
        printf("4. Search Product\n");
        printf("5. Low-Stock Report\n");
        printf("6. Show Total Inventory Value\n");
        printf("7. Save & Exit\n");
        printf("==========================================\n");
        printf("Enter your choice: ");
        
        // Input validation for menu choice
        if (scanf("%d", &choice) != 1) {
            printf("Error: Please enter a valid number.\n");
            clearBuffer();
            continue;
        }

        // Switch/case logic
        switch (choice) {
            case 1: addProduct(); break;
            case 2: updateStock(); break;
            case 3: deleteProduct(); break;
            case 4: searchProduct(); break;
            case 5: lowStockReport(); break;
            case 6: showTotalValue(); break;
            case 7: 
                saveToFile(); 
                printf("Exiting program...\n");
                break;
            default: 
                printf("Invalid choice. Please select 1-7.\n");
        }
    } while (choice != 7);

    return 0;
}

// Helper function to clear input buffer
void clearBuffer() {
    while (getchar() != '\n');
}

// Helper function to find a product by ID
int findProductIndex(int id) {
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full!\n");
        return;
    }

    Product p;
    printf("Enter Product ID: ");
    scanf("%d", &p.id);

    if (findProductIndex(p.id) != -1) {
        printf("Error: Product ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    clearBuffer();
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0; // Remove trailing newline

    printf("Enter Price: ");
    scanf("%f", &p.price);
    
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    // Input Validation
    if (p.price < 0 || p.quantity < 0) {
        printf("Error: Price and Quantity cannot be negative.\n");
        return;
    }

    inventory[productCount] = p;
    productCount++;
    printf("Product added successfully!\n");
}

void updateStock() {
    int id, qty, index;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    index = findProductIndex(id);
    if (index == -1) {
        printf("Error: Product not found.\n");
        return;
    }

    printf("Enter quantity to add (use negative number for sales): ");
    scanf("%d", &qty);

    if (inventory[index].quantity + qty < 0) {
        printf("Error: Insufficient stock for this sale.\n");
    } else {
        inventory[index].quantity += qty;
        printf("Stock updated successfully. New quantity: %d\n", inventory[index].quantity);
    }
}

void deleteProduct() {
    int id, index;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    index = findProductIndex(id);
    if (index == -1) {
        printf("Error: Product not found.\n");
        return;
    }

    for (int i = index; i < productCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    productCount--;
    printf("Product deleted successfully.\n");
}

void searchProduct() {
    int id, index;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    index = findProductIndex(id);
    if (index == -1) {
        printf("Product not found.\n");
    } else {
        printf("ID: %d | Name: %s | Price: $%.2f | Qty: %d\n", 
               inventory[index].id, inventory[index].name, 
               inventory[index].price, inventory[index].quantity);
    }
}

void lowStockReport() {
    int threshold;
    int found = 0;
    printf("Enter low-stock threshold: ");
    scanf("%d", &threshold);

    printf("\n--- Low Stock Items (Below %d) ---\n", threshold);
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].quantity < threshold) {
            printf("ID: %d | Name: %s | Qty: %d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("No items are currently below this threshold.\n");
    }
}

void showTotalValue() {
    float totalValue = 0;
    // Calculates total inventory value = SUM(price * quantity)
    for (int i = 0; i < productCount; i++) {
        totalValue += (inventory[i].price * inventory[i].quantity);
    }
    printf("Total Inventory Value: $%.2f\n", totalValue);
}

// File Handling Requirements
void saveToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d;%s;%.2f;%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    fclose(file);
    printf("Data saved to %s.\n", FILE_NAME);
}

void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        // File doesn't exist yet, which is fine on first run.
        return; 
    }
    
    productCount = 0;
    while (fscanf(file, "%d;%49[^;];%f;%d\n", &inventory[productCount].id, 
                  inventory[productCount].name, &inventory[productCount].price, 
                  &inventory[productCount].quantity) == 4) {
        productCount++;
        if (productCount >= MAX_PRODUCTS) break;
    }
    fclose(file);
}