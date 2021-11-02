#include <stdio.h>
#include <conio.h>

void main()
{
    int i = 0;
    while(!kbhit())
    {
        i++;
        usleep(3000000);
        printf("%d",i);
    }
    printf("%d", i);
}