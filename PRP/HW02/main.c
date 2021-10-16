#include <stdio.h>



int InRange(int Range[], int Num)        
{        
    return (Range[0] <= Num && Num <= Range[1]);         
}   

int main()
{
    int Range_declare[2] = { -10000, 10000 };
    printf("Enter variables in the range of [-10000,10000]\n");

    int List[100];
    int num = 0;
    int input_length;

    int positive, odd;
    int min = Range_declare[1];
    int max = Range_declare[0];

    while (scanf("%d",&List[num]) > 0)
    {
        if (!(InRange(Range_declare, List[num])))
        {
            printf("\nError:  Vstup je mimo interval!");
            return 100;
        }
        printf("%d: %d\n", num, List[num]);
        num++;
    }
    
    
    printf("fin");

    return 0;
}