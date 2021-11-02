#include <stdio.h>
#include <stdlib.h>

int InRange(int Range[], int Num)        
{        
    return (Range[0] <= Num && Num <= Range[1]);         
}   


/*  
    Kdyz jsem psal tuto ulohu, nevedel jsem, ze muzu pro hexadecimal pouzivat literaly, tak napsal jsem tuto funkce. 
    Pak uz jsem dozvedel jak se to dela. Ale necham tuto funkce tady
*/
char * DecToHex(int Num, int NumSize)
{
    if (Num == 0)
    {
        char *result = malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    int Nums[NumSize];
    int i = 0;
    while (Num != 0)
    {
        Nums[i++] = Num % 16;
        Num /= 16;
    }

    char Hex_Str[] = "0123456789ABCDEF";
    char *result = malloc(i+1);
    for (int j = 0; j < i; j++)
    { 
        result[j] = Hex_Str[Nums[i-1-j]];
    }

    result[i] = '\0';
    return result;
}


int main()
{
    int Range_declare[2] = { -10000, 10000 };
    int a,b = 666;
    scanf("%d %d", &a, &b);

    if (!(InRange(Range_declare, a) && InRange(Range_declare, b)))
    {
        printf("Vstup je mimo interval!\n");
        return 0;
    }
    
    printf("Desitkova soustava: %d %d\n", a, b);
    printf("Sestnactkova soustava: %x %x\n", a, b); /* printf("Sestnactkova soustava: %s %s\n", DecToHex(a, 5), DecToHex(b, 5)); */  
    printf("Soucet: %d + %d = %d\n", a, b, a+b);
    printf("Rozdil: %d - %d = %d\n", a, b, a-b);
    printf("Soucin: %d * %d = %d\n", a, b, a*b);
    if (b == 0)
        printf("Nedefinovany vysledek!\n");
    else
        printf("Podil: %d / %d = %d\n", a, b, a/b);
    printf("Prumer: %.1f\n", (float)(a + b) / 2);

    return 0;
}