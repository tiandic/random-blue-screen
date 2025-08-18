#include "def.h"
#include "reg.h"

bool get_dir(char *path,int path_size){
    // 获取当前程序的所在目录
    GetModuleFileNameA(NULL, path, path_size);

    // 提取目录部分
    for (int i = strlen(path) - 1; i >= 0; i--) {
        if (path[i] == '\\') {
            path[i + 1] = '\0'; // 截断到最后一个 '\'
            break;
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    remove_reg();
    char path[MAX_PATH];
    get_dir(path,sizeof(path));
    DWORD size = strlen(path)+1;
    reg_rw(EXE_DIR_PATH_key,path,&size,1);
    strcat(path,"real");
    remove(path);
    return 0;
}
