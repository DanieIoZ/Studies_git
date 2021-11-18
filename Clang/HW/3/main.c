#include <stdio.h>

int main()
{
    // FOR SENDER: READING FILE
    FILE* f = fopen("homework-t.txt", "r");
    char str[255];
    while (!feof(f))
    {
        fgets(str, 255, f);
        for (int i = 1; i < 255; i++)
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] += 32;
            }
            
            else if (str[i] == '.')
            {
                printf("%s", str);
                break;
            }
        }
    }
    
    //


    return 0;
}