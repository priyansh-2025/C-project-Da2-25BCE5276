#include <stdio.h>
#include "../include/ui.h"

void displayMenu() {
    printf("\n==================================\n");
    printf("1. Add Product\n");
    printf("2. Update Stock (Purchase/Sale)\n");
    printf("3. Delete Product\n");
    printf("4. Search by ProductID\n");
    printf("5. Low-stock Report\n");
    printf("6. Show Total Inventory Value\n");
    printf("7. Show All Products\n");
    printf("8. Save and Exit\n");
    printf("==================================\n");
    fflush(stdout);
}