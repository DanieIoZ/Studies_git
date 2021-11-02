#include <stdio.h>

#define Array_Len 80
#define Range_declare_max 10000
#define Range_declare_min -10000

int InRange(int Range_min, int Range_max, int Number)        
{        
    return (Range_min <= Number && Number <= Range_max);         
}   

int main()
{
    int Numbers = 0;
    int List[Array_Len];

    while (scanf("%d",&List[Numbers]) > 0)
    {
        Numbers++;
    }
    
    for (int i = 0; i < Numbers; i++)
    {
        if (!InRange(Range_declare_min, Range_declare_max, List[i])) 
        {
            printf("\nError: Vstup je mimo interval!\n");
            return 100; 
        }
        if (i != 0)
            printf(", ");
        printf("%d", List[i]);
        
    }

    int Positive = 0;
    int Negative = 0;
    int Even = 0; 
    int Summ = 0;
    int Min = List[0];
    int Max = List[0];

    for (int i = 0; i < Numbers; i++)
    {
        Positive += List[i] > 0;
        Negative += List[i] < 0;
        Even += List[i] & 1;
        if (List[i] > Max)
            Max = List[i];
        else if (List[i] < Min)
            Min = List[i];
        Summ += List[i];
    }
    float Percents = 100/(float)Numbers;
    printf("\nPocet cisel: %d", Numbers);
    printf("\nPocet kladnych: %d", Positive);
    printf("\nPocet zapornych: %d", Negative);
    printf("\nProcento kladnych: %.2f", Percents * Positive);
    printf("\nProcento zapornych: %.2f", Percents * Negative);
    printf("\nPocet sudych: %d", Numbers-Even);
    printf("\nPocet lichych: %d", Even);    
    printf("\nProcento sudych: %.2f", Percents * (Numbers-Even));
    printf("\nProcento lichych: %.2f", Percents * Even);
    printf("\nPrumer: %.2f", (float)Summ/Numbers);
    printf("\nMaximum: %d", Max);
    printf("\nMinimum: %d\n", Min);
    return 0;
}
