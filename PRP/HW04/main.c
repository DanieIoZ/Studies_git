#include <stdio.h>
#include <string.h>

#define biggest_prime_number 1000000

#define primes_count 100000


void copy_to(char * src, char * result)
{
    int i = 0;
    while (src[i] != '\0')
    {
        result[i] = src[i];
        i++;
    }
    result[i] = '\0';
}

int divide(char * number, int divider, int copy)
{
    char division_result[100];
    // Getting the smallest number, which can be divided by the divider
    // - '0'    is needed, because digits in ASCII are not represented as 0..9 in integers
    int num_size = 0;
    while (number[num_size] != '\0')
    {
        num_size++;
    }

    int curr_digit = 0;
    int mod = number[curr_digit++] - '0';
    while (mod < divider && curr_digit < num_size)
    {
        mod = mod * 10 + (number[curr_digit++] - '0');

    }
    int division_modulo = 0;
    if (mod < divider)
    {
        division_result[0] = '0';
        division_result[1] = '\0';
        division_modulo = mod;
    }
    else
    {
        //length of the result of the division
        int length = 0;
        //length of the original number

        while (num_size >= curr_digit) 
        {
            division_result[length++] = (mod / divider) + '0';
            

            mod = (mod % divider) * 10 + number[curr_digit++] - '0';
            
            division_modulo = mod;
            if (mod < 0)
                division_modulo = mod + '0';
        }
        division_result[length] = '\0';
    }
    
    if (copy)
        copy_to(division_result, number);
    return division_modulo;
}

int* get_sieve()
{
    static short numbers_in_sieve[biggest_prime_number];
    
    for (int i = 2; i < biggest_prime_number; i++)
    {
        numbers_in_sieve[i] = 1;
    }

    int result_counter = 0;
    static int result[primes_count];
    for (int i = 2; i < biggest_prime_number; i++)
    {
        if (numbers_in_sieve[i])
        {
            result[result_counter++] = i;
            for (int j = 0; j < biggest_prime_number; j+=i)
            {
                numbers_in_sieve[j] = 0;
            }
        }
    }

    return result;
}

int main()
{
    int *sieve = get_sieve();
    while (1)
    {
        char number[100];
        if (scanf("%s", number) == 0)
        {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return 100;
        }
        int i = 0;
        while (number[i] != '\0')
        {
            if (number[i] < '0' || number[i] > '9')
            {
                fprintf(stderr, "Error: Chybny vstup!\n");
                return 100;
            }
            i++;
        }

        if (strcmp(number, "0") == 0)
        {
            break;
        }

        if (strcmp(number, "1") == 0)
        {
            printf("Prvociselny rozklad cisla 1 je:\n1\n");
        }
        else
        {
            printf("Prvociselny rozklad cisla %s je:\n", number);
            int divider = 0;
            while (1)
            {
                char tmp_number[100];
                copy_to(number, tmp_number);
                int division_modulo = divide(tmp_number, sieve[divider], 1);
                if (division_modulo == 0)
                {
                    int divider_repeating = 0;
                    while (division_modulo == 0)
                    {
                        divider_repeating++;
                        copy_to(tmp_number, number);
                        division_modulo = divide(tmp_number, sieve[divider], 1);
                    }
                    
                    if (divider_repeating == 1)
                    {
                        printf("%d", sieve[divider]);
                    }
                    else
                    {
                        printf("%d^%d", sieve[divider], divider_repeating);
                    }
                    if (division_modulo != 1)
                    {
                        printf(" x ");
                    }
                    else
                    {
                        break;
                    }
                }
                divider++;
            }
            printf("\n");
        }
    }
    return 0;
}
