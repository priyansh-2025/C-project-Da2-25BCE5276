#ifndef FILEOPS_H
#define FILEOPS_H

#include "product.h"

#ifdef __EMSCRIPTEN__
#define FILENAME "/data/inventory.dat"
#else
#define FILENAME "inventory.dat"
#endif

void saveToFile(Product inventory[], int count);
void loadFromFile(Product inventory[], int *count);

#endif
