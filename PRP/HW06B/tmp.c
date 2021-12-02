#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name;
    int data[20][20];
    int size[2];
    if (scanf("%c=[", &name) < 1 && name < 'A' && name > 'Z')
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    printf("CHaR: %c\n", name);

    char buffer[100];
    int buffer_length = 0;
    int data_rows = 0;
    int data_cols = 0;

    int data_cols_count = 0;

    while (scanf("%c", &buffer[buffer_length]) == 1 && buffer[buffer_length] != ']')
    {
        if (buffer[buffer_length] < '0' || buffer[buffer_length] > '9' || buffer[buffer_length] != '-')
        {
            printf("ERRORR EPORKJPEORJPER");
            /// ERROR ----------------------------- ERROR
        }

        if (buffer[buffer_length] == ' ' && buffer_length > 0)
        {
            buffer[buffer_length] = '\0';
            data[data_rows][data_cols++] = atoi(buffer);
            buffer_length = 0;
        }
        else if (buffer[buffer_length] == ';')
        {
            getchar();
            buffer[buffer_length] = '\0';

            if (data_rows == 0)
            {
                data_cols_count == data_cols;
            }
            else
            {
                if (data_cols_count != data_cols)
                {
                    printf("ERRORR EPORKJPEORJPER");
                    /// ERROR ----------------------------- ERROR
                }
            }

            data[data_rows++][data_cols] = atoi(buffer);
            
            data_cols = 0;
            buffer_length = 0;
        }
        else if (buffer[buffer_length] != '\n')
        {
            buffer_length++;
        }
    }
    buffer[buffer_length] = '\0';
    data[data_rows++][data_cols++] = atoi(buffer);

    for (size_t i = 0; i < data_rows; i++)
    {
        for (size_t j = 0; j < data_cols; j++)
        {
            
        }
    }
    
}