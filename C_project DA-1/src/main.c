#include <stdio.h>
#include <stdlib.h>
#include "../include/product.h"
#include "../include/inventory.h"
#include "../include/fileops.h"
#include "../include/ui.h"
#include "../include/validation.h"
#include "../include/browser_io.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(void, js_init_fs, (), {
    if (typeof FS !== 'undefined') {
        if (!FS.analyzePath('/data').exists) {
            FS.mkdir('/data');
        }
        FS.mount(IDBFS, {}, '/data');
        console.log("Loading from IndexedDB...");
        await new Promise((resolve, reject) => {
            FS.syncfs(true, (err) => {
                if (err) {
                    console.error("IDBFS Load Error:", err);
                    resolve(); // Continue even if empty
                } else {
                    console.log("Load complete.");
                    resolve();
                }
            });
        });
    }
});
#endif

int main() {
#ifdef __EMSCRIPTEN__
    js_init_fs();
#endif

    Product inventory[MAX_PRODUCTS];
    int count = 0;
    int choice;

    terminal_print("--- Inventory Management System ---\n");
    
    // Load existing data at startup
    loadFromFile(inventory, &count);

    while (1) {
        displayMenu();
        terminal_prompt_int("Enter your choice: ", &choice); 

        if (choice == 8) {
            saveToFile(inventory, count);
            terminal_print("\n>> Exiting program. Goodbye!\n");
            terminal_yield();
#ifdef __EMSCRIPTEN__
            emscripten_sleep(100); // Guard for final render
#endif
            break;
        }

        switch (choice) {
            case 1: addProduct(inventory, &count); break;
            case 2: updateStock(inventory, count); break;
            case 3: deleteProduct(inventory, &count); break;
            case 4: searchProduct(inventory, count); break;
            case 5: lowStockReport(inventory, count); break;
            case 6: showTotalValue(inventory, count); break;
            case 7: showAllProducts(inventory, count); break;
            default:
                terminal_print("Invalid choice. Please select between 1 and 8.\n");
        }
    }

    return 0;
}
