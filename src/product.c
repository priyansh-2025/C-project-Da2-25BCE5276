#include <stdio.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "../include/product.h"
#include "../include/validation.h"
#include "../include/browser_io.h"

void addProduct(Product inventory[], int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    Product newProduct;

    terminal_prompt_int("Enter Product ID: ", &newProduct.productID);

    for (int i = 0; i < *count; i++) {
        if (inventory[i].productID == newProduct.productID) {
            printf("Product with ID %d already exists.\n", newProduct.productID);
            return;
        }
    }

    terminal_prompt_string("Enter Product Name: ", newProduct.name, sizeof(newProduct.name));

    terminal_prompt_float("Enter Price: ", &newProduct.price);

    terminal_prompt_int("Enter Quantity: ", &newProduct.quantity);

    inventory[*count] = newProduct;
    (*count)++;
    printf(">> Product added successfully.\n");
    fflush(stdout);
}

void deleteProduct(Product inventory[], int *count) {
    int id;
    terminal_prompt_int("Enter Product ID to delete: ", &id);

    for (int i = 0; i < *count; i++) {
        if (inventory[i].productID == id) {
            for (int j = i; j < (*count) - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            printf(">> Product deleted successfully.\n");
            return;
        }
    }
    terminal_print(">> Product ID %d not found.\n", id);
    terminal_yield();
}

void showAllProducts(Product inventory[], int count) {
    if (count == 0) {
        terminal_print("\n>> Inventory is empty.\n");
        terminal_yield();
        return;
    }

    terminal_print("\n--- Current Inventory ---\n");
    terminal_print("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Qty");
    terminal_print("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        terminal_print("%-10d %-20s $%-9.2f %-10d\n", 
               inventory[i].productID, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
    terminal_print("--------------------------------------------------\n");
    terminal_print("Count: %d\n", count);
    terminal_yield();
}

void searchProduct(Product inventory[], int count) {
    int id;
    terminal_prompt_int("Enter Product ID to search: ", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].productID == id) {
            printf("\n--- Product Found ---\n");
            printf("ID: %d\nName: %s\nPrice: $%.2f\nQuantity: %d\n",
                   inventory[i].productID, inventory[i].name, inventory[i].price, inventory[i].quantity);
            return;
        }
    }
    printf(">> Product ID %d not found.\n", id);
}