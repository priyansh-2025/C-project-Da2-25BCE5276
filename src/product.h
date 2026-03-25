#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Product structure definition
typedef struct {
    int id;           // Unique product identifier (1-99999)
    char name[51];    // Product name (max 50 characters + null)
    float price;      // Product price (positive float, 2 decimal precision)
    int quantity;     // Current stock level (non-negative integer)
} Product;

// Global constants
#define MAX_PRODUCTS 1000
#define LOW_STOCK_THRESHOLD 5
#define MAX_NAME_LENGTH 50

// Global inventory array and counter
extern Product inventory[MAX_PRODUCTS];
extern int product_count;

// Function prototypes
int add_product(int id, const char* name, float price, int quantity);
int update_product(int id, const char* name, float price);
int delete_product(int id);
int find_product(int id);
void display_products(void);

#endif // PRODUCT_H