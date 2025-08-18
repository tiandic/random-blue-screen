@echo off

gcc -mwindows -O2 .\src\main.c -o RandomBlueScreenMain.exe
gcc -mwindows -O2 .\src\blueScreen.c app.res -o blueScreen.exe
gcc -mwindows -O2 .\src\install.c -o install.exe
gcc -mwindows -O2 .\src\un2.c -o un2.exe
gcc .\src\create_real.c -o create_real.exe