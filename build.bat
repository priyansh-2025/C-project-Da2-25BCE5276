@echo off
echo --- Loading Emscripten SDK ---
call emsdk\emsdk_env.bat

echo --- Compiling Project to WebAssembly ---
emcc src\main.c src\product.c src\inventory.c src\fileops.c src\ui.c src\validation.c src\browser_io.c ^
     -I include ^
     --shell-file shell.html ^
     -o index.html ^
     -s ASYNCIFY ^
     -lidbfs.js ^
     -s EXIT_RUNTIME=1 ^
     -s "EXPORTED_FUNCTIONS=['_main','_malloc','_free']" ^
     -s "EXPORTED_RUNTIME_METHODS=['lengthBytesUTF8','stringToUTF8']" ^
     -s TOTAL_MEMORY=33554432

if %errorlevel% neq 0 (
    echo Compilation Failed!
    exit /b %errorlevel%
)

echo --- Compilation Successful ---
echo Output generated: index.html, index.js, index.wasm
