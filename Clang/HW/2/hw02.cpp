#include <stdio.h>
#include <conio.h>
#include<unistd.h>


int main()
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