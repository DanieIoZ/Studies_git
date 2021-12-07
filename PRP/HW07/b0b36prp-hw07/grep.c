#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 5000

#define COLOR   "\033[01;31m\033[K"
#define RESET "\033[m\033[K"

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
    int starts[MAX_LENGTH];
    int ends[MAX_LENGTH];
    int curr_startend = 0;

    int contains = 0;

    int curr_char = 0;
    int pt_current = 0;
    
    int E_num = 0;

    while (str[curr_char+1] != '\n' && str[curr_char+1] != '\0')
    {
        curr_char++;
    }
    while (pattern[pt_current+1] != '\n' && pattern[pt_current+1] != '\0')
    {
        if (pattern[pt_current] == '?' || pattern[pt_current] == '*' || pattern[pt_current] == '+')
            E_num++;
        if (E_num > 1)
            return 0;
        pt_current++;
    }
    int str_length = curr_char;
    int pt_length = pt_current;
    while (curr_char > -1)
    {
        if ((curr_char >= 0) && (pt_current >= 0) &&  str[curr_char] == pattern[pt_current])
        {
            if (!contains)
                ends[curr_startend] = curr_char+1;
            pt_current--;
            curr_char--;
            contains = 1;
        }
        else
        {
            if (opt_e && pt_current > 0)
            {
                if (pattern[pt_current] == '?')
                {
                    pt_current--;
                    if (str[curr_char] == pattern[pt_current])
                    {
                        if (!contains) 
                        {
                            contains = 1;
                            ends[curr_startend] = curr_char+1;
                        }
                        curr_char--;
                    }
                    pt_current--;
                }
                else if (pattern[pt_current] == '*')
                {
                  if ((str[curr_char] == pattern[pt_current-1]) && !contains)
                  {
                        ends[curr_startend] = curr_char+1;
                      contains = 1;
                  }
                    while ((curr_char >= 0) && (pt_current - 1 >= 0) && (str[curr_char] == pattern[pt_current-1]))
                    {
                        curr_char--;

                    }
                    pt_current -= 2;

                }
                else if (pattern[pt_current] == '+')
                {
                    if (str[curr_char] == pattern[pt_current-1])
                    {
                        if (!contains)
                        {
                            ends[curr_startend] = curr_char+1;
                            contains = 1;
                        }
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
                      if (contains)
                      {
                        contains = 0;
                      }
                      else
                      {
                        curr_char--;
                      }
                    
                    pt_current = pt_length;
                }
            }
            else
            {
              if (contains)
              {
                contains = 0;
              }
              else
              {
                curr_char--;
              }
              pt_current = pt_length;
            }
        }
        if (contains && (pt_current < 0))
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
                str[str_length+1] = '\0';
                printf("%s\n", str);
                return 1;
            }
        }
    }
    curr_startend--;
    if (curr_startend >= 0)
    {
        for (size_t i = 0; i <= str_length; i++)
        {
            if (curr_startend >= 0)
            {
                if (i == ends[curr_startend])
                {
                    printf(RESET);
                    curr_startend--;
                }
                if (curr_startend >= 0 && i == starts[curr_startend])
                {
                    printf(COLOR);
                }
            }
            if (str_length > 0 && str[i] != '\n')
                printf("%c", str[i]);
        }
        printf("\n");

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
        int i = 0;
        char res[MAX_LENGTH];
        while (scanf("%c", &res[i]) > 0 && res[i] != EOF)
        {
            if ((res[i] == '\n' || res[i] == '\0') && (res[0] != '\n' && res[0] != '\0') && i>0)
            {
                
                if (analyze_line(res, pattern, opt_e, opt_color))
                {
                    result = 0;
                }
                i = 0;
            }
            else
            {
                res[++i] = '\0';
            }
        }
    }
    else
    {
        char text[MAX_LENGTH];

        FILE* f = fopen(file_name, "r");
        if (f == NULL)
        {
          result = 1;
        }
        else
          {
            while (fgets(text, MAX_LENGTH, f) != NULL)
            {
                if (text[0] != '\n' && text[0] != '\0')
                    if (analyze_line(text, pattern, opt_e, opt_color))
                    {
                        result = 0;
                    }
            }
           fclose(f);
          }

    }
    return result;
}