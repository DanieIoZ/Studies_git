#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_LENGTH 500

#define MAX_STRING_LENGTH 50001

#define MAX_DIST_MATRIX_SIZE 10

#define ERR_INVALID_INPUT -1

#define STRING_COUNT 2

int get_min(int int1, int int2, int int3)
{
    if (int1 < int2)
    {
        if (int1 < int3)
            return int1;
    }
    else
    {
        if (int2 < int3)
            return int2;
    }
    return int3;
}

int leven_dist(int length_str1, int length_str2, char * str1, char * str2)
{
    int * dist[length_str1 + 1];

    for (int i = 0; i <= length_str1; i++)
    {
        dist[i] = (int *)malloc((length_str2+1) * sizeof(int));
        dist[i][0] = i;
    }

    for (int i = 0; i <= length_str2; i++)
    {
        dist[0][i] = i;
    }
    
    for (int j = 1; j <= length_str2; j++)
    {
        for (int i = 1; i <= length_str1; i++)
        {
            int sub_cost = 1;
            if (str1[i-1] == str2[j-1])
            {
                sub_cost = 0;
            }

            dist[i][j] = get_min(dist[i-1][j] + 1, dist[i][j-1] + 1, dist[i-1][j-1] + sub_cost);
        }
    }
    int result = dist[length_str1][length_str2];
    for (size_t i = 0; i < length_str1 + 1; i++)
    {
        free(dist[i]);
    }
    

    return result;
}


int shift_char(char orig, int shift)
{
    orig -= orig > 'Z' ? 'A' + 6 : 'A';
    
    orig = (orig + shift) % 52;

    return orig > 25 ? orig % 26 + 'a' : orig + 'A';
}

void shift_string(char * str, int shift)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = shift_char(str[i], shift);
        i++;
    }
}

void get_smallest_distance(char * str_ciph, char * str_orig, int len_ciph, int len_orig)
{
    int min_dist = leven_dist(len_ciph, len_orig, str_ciph, str_orig);
    char * str_result = (char *) malloc(len_ciph+1);
    strcpy(str_result, str_ciph);
    for (size_t i = 1; i < 52; i++)
    {
        shift_string(str_result, 1);
        int new_dist = leven_dist(len_ciph, len_orig, str_result, str_orig);
        if (new_dist < min_dist)
        {
            min_dist = new_dist;
            strcpy(str_ciph, str_result);
        }
    }
    free(str_result);
}

int compare(char * str_ciph, char * str_orig)
{
    int i = 0;
    int diff = 0;
    while (str_ciph[i] != '\0')
    {
        if (str_ciph[i] != str_orig[i])
            diff++;
        i++;
    }  
    return diff;
}

void decrypt(char * str_ciph, char * str_orig, int length)
{
    char * str_result = (char *) malloc(length+1);
    strcpy(str_result, str_ciph);
    
    int min_diff = compare(str_result, str_orig);
    for (size_t i = 1; i < 52; i++)
    {
        shift_string(str_result, 1);    
        int diff = compare(str_result, str_orig);
        if (min_diff > diff)
        {
            min_diff = diff;
            strcpy(str_ciph, str_result);
        }
    }
    free(str_result);
}

void free_all(char * str1, char * str2)
{
    free(str1);
    free(str2);
}

int main(int argc, char * argv[])
{
    char * strings[STRING_COUNT];
    int length[STRING_COUNT];

    for (size_t i = 0; i < STRING_COUNT; i++)
    {
        strings[i] = malloc(BASE_LENGTH + 1);
        length[i] = 0;

        int max_length = BASE_LENGTH;
        while ((strings[i][length[i]] = getchar()) != '\n')
        {
            if (strings[i][length[i]] < 'A' || (strings[i][length[i]] > 'Z' && strings[i][length[i]] < 'a') || strings[i][length[i]] > 'z')
            {
                length[i] = ERR_INVALID_INPUT;
                break;
            }
            length[i]++;
            if (length[i] == max_length)
            {
                max_length *= 2;
                strings[i] = max_length >= MAX_STRING_LENGTH ? (char *)realloc(strings[i], MAX_STRING_LENGTH) : (char *)realloc(strings[i], max_length + 1);
            }
        }
        if (length[i] >= 0)
            strings[i][length[i]] = '\0';
        strings[i] = (char *) realloc(strings[i], length[i] + 1);
    }
    int ERR_INV_INPUT = length[0] == ERR_INVALID_INPUT || length[1] == ERR_INVALID_INPUT;
    if (ERR_INV_INPUT)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free_all(strings[0], strings[1]);
        return 100;
    }
    if (argc == 1 && length[0] != length[1])
    {
       
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        free_all(strings[0], strings[1]);
        return 101;
        
    }
    if (argc > 1)
    {
        get_smallest_distance(strings[0], strings[1], length[0], length[1]);
    }
    else
    {
        decrypt(strings[0], strings[1], length[0]);
    }
    int i = 0;
    while (strings[0][i] != '\0')
    {
        printf("%c", strings[0][i]);
        i++;
    }
    printf("\n");
    free_all(strings[0], strings[1]);
    return 0;
}
