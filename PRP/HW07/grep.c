#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100

#define COLOR   "\033[1;31m"
#define RESET "\033[0m"

int str_equal(char * str1, char * str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int analyze_line(char str[], char * pattern, int opt_e, int opt_color)
{
    int starts[20];
    int ends[20];
    int curr_startend = 0;

    int contains = 0;


    int curr_char = 0;

    int pt_length = 0;
    while (str[curr_char+1] != '\0')
    {
        curr_char++;
    }
    while (pattern[pt_length+1] != '\0')
    {
        pt_length++;
    }
    int str_length = curr_char;
    int pt_current = pt_length;

    while (curr_char >= 0)
    {
        if (str[curr_char] == pattern[pt_current])
        {
            if (!contains)
                ends[curr_startend] = curr_char+1;
            pt_current--;
            curr_char--;
            contains = 1;
        }
        else
        {
            if (opt_e)
            {
                if (pattern[pt_current] == '?')
                {
                    if (str[curr_char] == pattern[pt_current-1])
                    {
                        curr_char--;
                    }
                    pt_current -= 2;
                }
                else if (pattern[pt_current] == '*')
                {
                    while (str[curr_char] == pattern[pt_current-1])
                    {
                        curr_char--;
                    }
                    pt_current -= 2;
                }
                else if (pattern[pt_current] == '+')
                {
                    if (str[curr_char] == pattern[pt_current-1])
                    {
                        while (str[curr_char] == pattern[pt_current-1])
                        {
                            curr_char--;
                        }
                        pt_current -= 2;
                    }
                    else
                    {
                        pt_current--;
                    }
                }
                else
                {
                    contains = 0;
                    pt_current = pt_length;
                    curr_char--;
                }
            }
            else
            {
                contains = 0;
                pt_current = pt_length;
                curr_char--;
            }
        }
        if (contains && pt_current < 0)
        {
            if (opt_color)
            {
                starts[curr_startend] = curr_char + 1;

                curr_startend++;
                contains = 0;
                pt_current = pt_length;
            }
            else
            {
                printf("%s", str);
                return 1;
            }
        }
    }
    if (curr_startend-- > 0)
    {
        for (size_t i = 0; i <= str_length; i++)
        {
            if (i == ends[curr_startend])
            {
                printf(RESET);
                curr_startend--;
            }
            if (i == starts[curr_startend])
            {
                printf(COLOR);
            }
            printf("%c", str[i]);
        }
        return 1;
    }
    return 0;
}

int main(int argc, char * argv[])
{
    int opt_e = 0;
    int opt_color = 0;
    char * pattern;
    char * file_name;

    char text[MAX_LENGTH] = "";

    int result = 1;

    for (int i = 1; i < argc-1; i++)
    {
        if (str_equal(argv[i], "-E"))
            opt_e = 1;
        else if (str_equal(argv[i], "--color=always"))
            opt_color = 1;
    }
    
    pattern = argv[1 + opt_e + opt_color];
    if (argc < 3 + opt_e + opt_color)
    {
        file_name = NULL;
    }
    else
    {
        file_name = argv[argc-1];
    }

    if (file_name == NULL)
    {
        char * line = NULL;
        size_t size = 0;
        while (getline(&line, &size, stdin) > 0)
        {
            if (analyze_line(line, pattern, opt_e, opt_color))
            {
                result = 0;
            }
            free(line);
        }
    }
    else
    {
        FILE* f = fopen(file_name, "r");
        while (!feof(f))
        {
            fgets(text, MAX_LENGTH, f);
            if (analyze_line(text, pattern, opt_e, opt_color))
            {
                result = 0;
            }
        }
        fclose(f);
    }
    return result;
}