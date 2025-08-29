@echo off

windres app.rc -o app_res.o
gcc -mwindows -O2 .\src\main.c -o RandomBlueScreenMain.exe
gcc -mwindows -O2 .\src\blueScreen.c app_res.o -o blueScreen.exe
gcc -mwindows -O2 .\src\install.c -o install.exe
gcc -mwindows -O2 .\src\un2.c -o un2.exe
gcc .\src\create_real.c -o create_real.exe
del app_res.o