#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"

// Function prototypes for inventory operations
int purchase_stock(int id, int quantity);
int sale_stock(int id, int quantity);
void check_low_stock(void);
float calculate_total_value(void);

#endif // INVENTORY_H