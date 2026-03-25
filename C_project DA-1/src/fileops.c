#include <stdio.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "../include/fileops.h"
#include "../include/browser_io.h"


#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(void, js_sync_to_db, (), {
    if (typeof FS !== 'undefined') {
        console.log("Saving to IndexedDB...");
        await new Promise((resolve, reject) => {
            FS.syncfs(false, (err) => {
                if (err) {
                    console.error("IDBFS Sync Error:", err);
                    reject(err);
                } else {
                    console.log("Save complete.");
                    resolve();
                }
            });
        });
    }
});
#endif

void saveToFile(Product inventory[], int count) {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(inventory, sizeof(Product), count, file);
    fclose(file);
    terminal_print(">> Inventory saved to '%s' successfully.\n", FILENAME);

#ifdef __EMSCRIPTEN__
    js_sync_to_db();
#endif
}

void loadFromFile(Product inventory[], int *count) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf(">> No existing database found. Starting fresh.\n");
        *count = 0;
        return;
    }
    if (fread(count, sizeof(int), 1, file) != 1) {
        *count = 0;
    } else {
        fread(inventory, sizeof(Product), *count, file);
        printf(">> Loaded %d products from existing database.\n", *count);
    }
    fclose(file);
}