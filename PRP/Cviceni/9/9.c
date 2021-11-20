#include <stdio.h>
#include <math.h>

int strlen_my(char txt[], int length)
{
    if (txt[length] != '\0')
    {
      return strlen_my(txt, length + 1);
    }
    return length-1;
}


#define BOARD_SIZE 4
int board[BOARD_SIZE] = {}

int main()
{
    int digits[] = {1,2,3,4};
    gen_nums(digits, 2);
}