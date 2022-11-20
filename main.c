#include <stdio.h>

int main()
{
    printf("hello world");
}

void attente(int temps) // attend temps secondes/1000
{
    clock_t hdeb;
    hdeb=clock();
    while (clock()-hdeb<=temps*CLOCKS_PER_SEC/1000);
    return;
}