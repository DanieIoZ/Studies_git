#include <stdio.h>

int str_cmp(char str1[], char str2[])
{
    int sum = 0;
    int i = 0;
    while (sum == 0 ||)
    {
        sum = str1[i] - str2[i];
        i++;
    }
    return sum;
}

void main()
{
    char str1[] = "Everybody";
    char str2[] = "Everybody";
    printf("%d\n", str_cmp(str1, str2));
    printf("%d\n", strcmp(str1, str2));
}