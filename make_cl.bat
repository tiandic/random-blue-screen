@echo off

if not exist build mkdir build
cl /source-charset:utf-8 .\src\main.c /Fe:RandomBlueScreenMain.exe user32.lib advapi32.lib /Fo.\build\
mt.exe -manifest .\src\uac.manifest -outputresource:RandomBlueScreenMain.exe;1
cl /source-charset:utf-8 .\src\blueScreen.c /Fe:blueScreen.exe user32.lib advapi32.lib gdi32.lib winmm.lib /Fo.\build\
cl /source-charset:utf-8 .\src\install.c /Fe:install.exe user32.lib advapi32.lib /Fo.\build\
cl /source-charset:utf-8 .\src\un2.c /Fe:un2.exe user32.lib advapi32.lib /Fo.\build\
cl /source-charset:utf-8 .\src\create_real.c /Fe:create_real.exe /Fo.\build\
rmdir /s /q build