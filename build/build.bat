@echo off

set INCLUDE=-I "..\lib" -I "D:\Programlar\SDL\x86_64-w64-mingw32\include"
set LIBS=-L "D:\Programlar\SDL\x86_64-w64-mingw32\lib" -lSDL3

g++ -c ..\src\main.cpp -o .\o\main.o %INCLUDE%
g++ -c ..\src\app.cpp -o .\o\app.o %INCLUDE%
g++ -c ..\src\event.cpp -o .\o\event.o %INCLUDE%
g++ -c ..\src\render.cpp -o .\o\render.o %INCLUDE%

g++ .\o\main.o .\o\app.o .\o\event.o .\o\render.o -o main.exe %LIBS%

.\main.exe
del .\main.exe
pause