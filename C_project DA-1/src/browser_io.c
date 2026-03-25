#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "../include/browser_io.h"

// Define the JS helper to wait for input
#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(char*, js_get_input, (), {
  const result = await Module.waitForBrowserInput();
  // Standard Emscripten string allocation for returning to C
  var lengthBytes = lengthBytesUTF8(result) + 1;
  var stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(result, stringOnWasmHeap, lengthBytes);
  return stringOnWasmHeap;
});
#endif

void terminal_print(const char* format, ...) {
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
#ifdef __EMSCRIPTEN__
    // Direct call to our custom print function to bypass stdout buffering
    EM_ASM({
        if (Module.printNoNewline) {
            Module.printNoNewline(UTF8ToString($0));
        } else {
            console.log(UTF8ToString($0));
        }
    }, buffer);
#else
    printf("%s", buffer);
    fflush(stdout);
#endif
}

void terminal_yield() {
#ifdef __EMSCRIPTEN__
    emscripten_sleep(10); 
#endif
}

void terminal_get_line(char* buffer, int size) {
#ifdef __EMSCRIPTEN__
    char* input = js_get_input();
    strncpy(buffer, input, size);
    buffer[size-1] = '\0';
    free(input);
#else
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
#endif
}

void terminal_prompt_int(const char* prompt, int* val) {
    char buf[64];
    terminal_print(prompt);
    terminal_get_line(buf, sizeof(buf));
    *val = atoi(buf);
}

void terminal_prompt_float(const char* prompt, float* val) {
    char buf[64];
    terminal_print(prompt);
    terminal_get_line(buf, sizeof(buf));
    *val = (float)atof(buf);
}

void terminal_prompt_string(const char* prompt, char* buffer, int size) {
    terminal_print(prompt);
    terminal_get_line(buffer, size);
}
