#include <stdio.h>

#define Array_Len 100
#define Range_declare_max 10000
#define Range_declare_min -10000

int InRange(int Range_min, int Range_max, int Number)        
{        
    return (Range_min <= Number && Number <= Range_max);         
}   

int main()
{
    printf("Enter variables in the range of [-10000,10000]\n");

    int Numbers;
    int List[Array_Len];

    while (scanf("%d",&List[Numbers]) > 0)
    {
        Numbers++;
    }
    
    for (int i = 0; i < Numbers; i++)
    {
        if (!InRange(Range_declare_min, Range_declare_max, List[i])) 
        {
            //Using \b to remove last comma
            printf("\b\b \nError:  Vstup je mimo interval!");
            return 100; 
        }
        printf("%d, ", List[i]);
    }
    printf("\b\b ");

    int Positive, Negative = 0;
    int Odd, Summ = 0;
    int Min, Max = List[0];

    for (int i = 0; i < Numbers; i++)
    {
        Positive += List[i] > 0;
        Negative += List[i] < 0;
        Odd += List[i] & 1;
        if (List[i] > Max)
            Max = List[i];
        else if (List[i] < Min)
            Min = List[i];
        Summ += List[i];
    }

    printf("\nPocet cisel: %d", Numbers);
    printf("\nPocet kladnych: %d", Positive);
    printf("\nPocet zapornych: %d", Negative);
    printf("\nProcento kladnych: %.2f", (float)100/Numbers * Positive);
    printf("\nProcento kladnych: %.2f", (float)100/Numbers * Negative);
    printf("\nPocet sudych: %d", Numbers-Odd);
    printf("\nPocet lichych: %d", Odd);    
    printf("\nProcento sudych: %.2f", (float)100/Numbers * (Numbers-Odd));
    printf("\nProcento lichych: %.2f", (float)100/Numbers * Odd);
    printf("\nPrumer: %.2f", (float)Summ/Numbers);
    printf("\nMaximum: %d", Max);
    printf("\nMinimum: %d", Min);
    
    return 0;
}