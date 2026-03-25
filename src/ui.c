#include <stdio.h>
#include "../include/ui.h"

void displayMenu() {
    printf("\n==================================\n");
    printf("1. Add Product\n");
    printf("2. Modify Inventory Quantity\n");
    printf("3. Remopve Item\n");
    printf("4. Search by ProductID\n");
    printf("5. Low Inventory Alert\n");
    printf("6. Calculate Inventory Worth\n");
    printf("7. Display Inventory List\n");
    printf("8. Save Changes and Exit\n");
    printf("==================================\n");
    fflush(stdout);
}
