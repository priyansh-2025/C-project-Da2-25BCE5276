#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"

#define LOW_STOCK_THRESHOLD 5

void updateStock(Product inventory[], int count);
void lowStockReport(Product inventory[], int count);
void showTotalValue(Product inventory[], int count);

#endif
