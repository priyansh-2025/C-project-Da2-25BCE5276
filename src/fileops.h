#ifndef FILEOPS_H
#define FILEOPS_H

#include "product.h"

// Function prototypes for file operations
int save_inventory(const char* filename);
int load_inventory(const char* filename);

#endif // FILEOPS_H