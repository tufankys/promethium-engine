@echo off

g++ ..\src\main.cpp ..\src\app.cpp ..\src\event.cpp ..\src\render.cpp -o ..\src\main.exe ^
    -I "..\lib" ^
    -I "D:\Programlar\SDL\x86_64-w64-mingw32\include" ^
    -L "D:\Programlar\SDL\x86_64-w64-mingw32\lib" ^
    -DSDL_MAIN_HANDLED ^
    -lSDL3

..\src\main.exe
del ..\src\main.exe
pause