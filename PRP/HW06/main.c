#include <stdio.h>
#include <stdlib.h>

#define MAX_OPERATIONS 50

typedef struct matrix
{
    int ** data;
    int size[2];
} matrix;


void mt_print(matrix * mat)
{
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        printf("%d", mat->data[i][0]);
        for (size_t j = 1; j < mat->size[1]; j++)
        {
            printf(" %d", mat->data[i][j]);
        }
        printf("\n");
    }
    
}

matrix * mt_read()
{
    matrix * mat = malloc(sizeof(struct matrix));
    if (scanf("%d %d", &mat->size[0], &mat->size[1]) < 2 )
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }

    mat->data = malloc(mat->size[0] * sizeof(int*));
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        mat->data[i] = malloc(mat->size[1] * sizeof(int));
        for (size_t j = 0; j < mat->size[1]; j++)
        {
            if (scanf("%d", &mat->data[i][j]) < 1)
            {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(100);
            }
        }
    }
    return mat;
}

matrix * mt_create(int rows, int cols)
{
    matrix * mat = malloc(sizeof(struct matrix));
    
    mat->size[0] = rows;
    mat->size[1] = cols;

    mat->data = malloc(mat->size[0] * sizeof(int*));
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        mat->data[i] = malloc(mat->size[1] * sizeof(int));
    }
    return mat;
}

void mt_free(matrix * mat)
{
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
    mat = NULL;
}

int mt_mul_cell(matrix * mt_destination, matrix * mt_multiplier, int row, int col)
{
    int sum = 0;
    for (size_t i = 0; i < mt_destination->size[1]; i++)
    {
        sum += mt_destination->data[row][i] * mt_multiplier->data[i][col];
    }
    return sum;
}

void mt_compsize(matrix * mt_1, matrix * mt_2)
{
    if (mt_1->size[0] != mt_2->size[0] || mt_1->size[1] != mt_2->size[1])
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

void  mt_comp_for_mul(matrix * mt_1, matrix * mt_2)
{
    if (mt_1->size[1] != mt_2->size[0])
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(100);
    }
}

void mt_plus(matrix * mt_destination, matrix * mt_add)
{
    mt_compsize(mt_destination, mt_add);

    for (size_t i = 0; i < mt_destination->size[0]; i++)
    {
        for (size_t j = 0; j < mt_destination->size[1]; j++)
        {
            mt_destination->data[i][j] += mt_add->data[i][j];
        }
    }
}

void mt_minus(matrix * mt_destination, matrix * mt_minus)
{
    mt_compsize(mt_destination, mt_minus);

    for (size_t i = 0; i < mt_destination->size[0]; i++)
    {
        for (size_t j = 0; j < mt_destination->size[1]; j++)
        {
            mt_destination->data[i][j] -= mt_minus->data[i][j];
        }
    }
}

void mt_mul(matrix * mt_destination, matrix * mt_multiplier)
{
    matrix * result = mt_create(mt_destination->size[0], mt_multiplier->size[1]);
    for (size_t i = 0; i < mt_destination->size[0]; i++)
    {
        for (size_t j = 0; j < mt_multiplier->size[1]; j++)
        {
            result->data[i][j] = mt_mul_cell(mt_destination, mt_multiplier, i, j);
        }
    }
    mt_free(mt_destination);
    *mt_destination = *result;
}

int main()
{
    matrix ** mats = malloc(sizeof(matrix *));
    char operations[MAX_OPERATIONS];

    int last = 0;
    mats[last] = mt_read();
    int scanning = 1;
    while (scanning)
    {
        if (scanf("\n%c", &operations[last]) == EOF || operations[last] == '\n')
        {
            scanning = 0;
        }
        else
        {
            if (operations[last] != '-' && operations[last] != '+' && operations[last] != '*')
            {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(100);
            }
            mats = realloc(mats, sizeof(matrix *) * (++last + 1));
            mats[last] = mt_read();
        }
    }

    int mt_mul_last = 0;
    while (mt_mul_last < last)
    {
        if (operations[mt_mul_last] == '*')
        {
            int mt_tmp = mt_mul_last;
            while (operations[mt_mul_last] == '*')
            {
                mt_mul(mats[mt_tmp], mats[++mt_mul_last]);
            }
        }
        mt_mul_last++;
    }

    for (size_t i = 0; i < last; i++)
    {
        if (operations[i] == '+')
        {
            mt_plus(mats[0], mats[i+1]);
        }
        if (operations[i] == '-')
        {
            mt_minus(mats[0], mats[i+1]);
        }
    }
    printf("%d %d\n", mats[0]->size[0], mats[0]->size[1]);
    mt_print(mats[0]);
    
    for (size_t i = 0; i <= last; i++)
    {
        mt_free(mats[i]);
    }
    free(mats);
}
