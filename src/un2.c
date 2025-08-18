#include "def.h"
#include "reg.h"

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
