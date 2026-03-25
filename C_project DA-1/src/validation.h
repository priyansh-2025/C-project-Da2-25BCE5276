#ifndef VALIDATION_H
#define VALIDATION_H

// Function prototypes for input validation
int validate_numeric_input(const char* prompt, int* value, int min, int max);
int validate_float_input(const char* prompt, float* value, float min, float max);
int validate_string_input(const char* prompt, char* buffer, int max_length);
int validate_product_id(int id);
int validate_quantity(int quantity);

#endif // VALIDATION_H