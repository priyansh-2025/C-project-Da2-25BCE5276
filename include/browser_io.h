#ifndef BROWSER_IO_H
#define BROWSER_IO_H

#include <stdio.h>

void terminal_print(const char* format, ...);
void terminal_yield();
void terminal_get_line(char* buffer, int size);

// Helper for formatted input prompts
void terminal_prompt_int(const char* prompt, int* val);
void terminal_prompt_float(const char* prompt, float* val);
void terminal_prompt_string(const char* prompt, char* buffer, int size);

#endif
