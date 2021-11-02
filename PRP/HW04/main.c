#include <stdio.h>

#define biggest_prime_number 1000000

/*
For this task it's enough to take 100000 primes, 
but if the max. value wasn't 1 million, 
it could be enough to take biggest_prime_number/4 size 
for any possible number of primes.
*/
#define primes_count 100000

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
        long long number = -1;
        if (scanf("%lli", &number) == 0 || number < 0)
        {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return 100;
        }

        if (number == 0)
        {
            break;
        }

        if (number == 1)
        {
            printf("Prvociselny rozklad cisla 1 je:\n1\n");
        }
        else
        {
            printf("Prvociselny rozklad cisla %lli je:\n", number);
            int divider = 0;
            while (1)
            {
                if (number % sieve[divider] == 0)
                {
                    int divider_repeating = 0;
                    while (number % sieve[divider] == 0)
                    {
                        divider_repeating++;
                        number /= sieve[divider];
                    }
                    
                    if (divider_repeating == 1)
                    {
                        printf("%d", sieve[divider]);
                    }
                    else
                    {
                        printf("%d^%d", sieve[divider], divider_repeating);
                    }
                    
                    if (number != 1)
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
