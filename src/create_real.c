#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *f=fopen("real","w");
    fclose(f);
    return 0;
}
