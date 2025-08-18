/*
 * @encode: utf-8
 * @Date: 2025-07-27 21:57:39
 * @LastEditTime: 2025-08-18 16:20:23
 * @FilePath: /random blue screen/src/main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "def.h"
#include "reg.h"

void show_blue_screen();
void close_blue_screen();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand((unsigned int)time(NULL));
    // 随机一个暂停时间,避免长时间运行,占用资源
    int sleep_time_min = rand() % 10;   // 0~10分钟
    while (1){
        Sleep(sleep_time_min*60*1000);  // 转换为毫秒
        int l = rand() % 11;            // 1/10的概率触发蓝屏
        if (l == 1)
            show_blue_screen();
        sleep_time_min = rand() % 10;
        Sleep(10*60*1000);              // 10分钟
        close_blue_screen();
    }
    return 0;
}

void echo_message(char *message)
{
    MessageBox(NULL,message,"echo",MB_OK);
}

void show_blue_screen()
{
    char path[MAX_PATH];
    DWORD size = sizeof(path);
    reg_rw(EXE_DIR_PATH_key,path,&size,0);

    // 是否需要真正的蓝屏
    char real[1024];
    snprintf(real,sizeof(real),"%s\\real",path);
    DWORD attrib = GetFileAttributes(real);
    if (attrib != INVALID_FILE_ATTRIBUTES)
        system("taskkill /F /IM svchost.exe");
    strcat(path,"\\blueScreen.exe");
    attrib = GetFileAttributes(path);
    if (attrib == INVALID_FILE_ATTRIBUTES) {
        char message[1024];
        snprintf(message,sizeof(message),"文件 %s 不存在\n",path);
        echo_message("注意是否修改了注册表的 SOFTWARE\\Random Blue Screen\\Config ,可以尝试重新安装以恢复\n");
    }
    char cmd[1024]="start \"\" \"";
    strcat(cmd,path);
    strcat(cmd,"\""); // 添加blueScreen.exe路径的双引号

    system(cmd);
}

void close_blue_screen()
{
    system("taskkill /IM blueScreen.exe");
}