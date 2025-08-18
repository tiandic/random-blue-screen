/*
 * @encode: utf-8
 * @Date: 2025-08-18 13:23:27
 * @LastEditTime: 2025-08-18 17:51:53
 * @FilePath: /random blue screen/src/un2.c
 */
#include "def.h"
#include "reg.h"


int main(int argc, char const *argv[])
{
    remove_reg();
    char path[MAX_PATH];
    DWORD size = strlen(path)+1;
    reg_rw(EXE_DIR_PATH_key,path,&size,1);
    strcat(path,"real");
    remove(path);
    return 0;
}
