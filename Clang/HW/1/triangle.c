#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int src = atoi(argv[1]);
    int star_count = 0;
    for (int i = 0; i < src; i++)
    {
        for (int j = 0; j < src-i; j++)
        {
            printf("*");
            star_count++;
        }
        printf("\n");
    }
    return star_count;
}