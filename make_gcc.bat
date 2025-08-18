@echo off

gcc -mwindows .\src\main.c -o RandomBlueScreenMain.exe
gcc -mwindows .\src\blueScreen.c app.res -o blueScreen.exe
gcc -mwindows .\src\install.c -o install.exe
gcc -mwindows .\src\un2.c -o un2.exe
gcc .\src\create_real.c -o create_real.exe