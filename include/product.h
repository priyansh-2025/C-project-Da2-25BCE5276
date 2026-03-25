#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100

typedef struct {
    int productID;
    char name[50];
    float price;
    int quantity;
} Product;

void addProduct(Product inventory[], int *count);
void deleteProduct(Product inventory[], int *count);
void searchProduct(Product inventory[], int count);
void showAllProducts(Product inventory[], int count);

#endif
