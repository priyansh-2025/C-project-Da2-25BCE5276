#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "../include/inventory.h"
#include "../include/validation.h"
#include "../include/browser_io.h"

void updateStock(Product inventory[], int count) {
    int id, change;
    terminal_prompt_int("Enter Product ID to update: ", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].productID == id) {
            terminal_print("Current Quantity of '%s': %d\n", inventory[i].name, inventory[i].quantity);
            terminal_prompt_int("Enter quantity to add (use negative for sale): ", &change);
            
            if (inventory[i].quantity + change < 0) {
                terminal_print("Error: Insufficient stock for sale. Transaction cancelled.\n");
            } else {
                inventory[i].quantity += change;
                terminal_print(">> Stock updated correctly. New Quantity: %d\n", inventory[i].quantity);
            }
            return;
        }
    }
    terminal_print(">> Product ID not found.\n");
}

void lowStockReport(Product inventory[], int count) {
    printf("\n--- Low Stock Report (Threshold: %d) ---\n", LOW_STOCK_THRESHOLD);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (inventory[i].quantity < LOW_STOCK_THRESHOLD) {
            printf("ID: %d | Name: %s | Qty: %d\n",
                   inventory[i].productID, inventory[i].name, inventory[i].quantity);
            fflush(stdout);
            found = 1;
        }
    }
    if (!found) {
        printf("All products are well stocked.\n");
    }
    fflush(stdout);
}

void showTotalValue(Product inventory[], int count) {
    float total = 0.0f;
    for (int i = 0; i < count; i++) {
        total += (inventory[i].price * inventory[i].quantity);
    }
    printf("\n>> Total Inventory Value: $%.2f\n", total);
    fflush(stdout);
}