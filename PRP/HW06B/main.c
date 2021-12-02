#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 30
#define ERROR_INVALID_INPUT 100

typedef struct matrix
{
    char name;
    int ** data;
    int size[2];
} matrix;


//These vars are global to free() them easier
matrix ** mats;
matrix ** mats_originals;
int last;
int last_in_sequence;

void mt_free(matrix ** mat)
{
    if ((*mat)->data != NULL)
    {
        for (size_t i = 0; i < (*mat)->size[0]; i++)
        {
            if ((*mat)->data[i] != NULL)
            {
                free((*mat)->data[i]);
            }
        }

        free((*mat)->data);
    }
    free(*mat);
    *mat = NULL;
}

void mt_free_all()
{
    for (size_t i = 0; i < last_in_sequence+1; i++)
    {
        mt_free(&mats[i]);
    }
    free(mats);
    for (size_t i = 0; i < last; i++)
    {
        mt_free(&mats_originals[i]);
    }
    free(mats_originals);
}

void mt_print(matrix * mat)
{
    printf("[");
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        printf("%d", mat->data[i][0]);
        for (size_t j = 1; j < mat->size[1]; j++)
        {
            printf(" %d", mat->data[i][j]);
        }
        if(i != (mat->size[0]) - 1)
            printf("; ");
    }
    printf("]\n");
}

void mt_error_inv_input()
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    mt_free_all();
    exit(ERROR_INVALID_INPUT);
}

int mt_read(matrix ** mat)
{
    *mat = (matrix *)malloc(sizeof(struct matrix));
    (*mat)->data = NULL;
    (*mat)->size[0] = 0;
    (*mat)->size[1] = 0;
    if (scanf("%c", &(*mat)->name) < 1 && (*mat)->name < 'A' && (*mat)->name > 'Z')
    {
        mt_error_inv_input();
    }
    else if ((*mat)->name == '\n')
    {
        free(*mat);
        *mat = NULL;
        return 0;
    }
    //skipping '=[' in 'A=[...]' string  
    getchar();
    getchar();

    char buffer[BUFFER_SIZE];
    int buffer_length = 0;

    int tmp_cols = 0;
    while (scanf("%c", &buffer[buffer_length]) == 1 && buffer[buffer_length] != ']')
    {
        if ((*mat)->size[1] == 0 && buffer_length == 0)
        {
            if ((*mat)->size[0] == 0)
            {
                (*mat)->data = malloc(sizeof(int *));
            }
            else
            {
                (*mat)->data = realloc((*mat)->data, sizeof(int *) * (((*mat)->size[0]) + 1));
            }
            (*mat)->data[(*mat)->size[0]] = malloc(sizeof(int));
        }
        //' ' in stdin means, that buffer contains a number, so we need to convert it and reset buffer last index pointer (buffer_length)
        if (buffer[buffer_length] == ' ' && buffer_length > 0)
        {
            buffer[buffer_length] = '\0';
            (*mat)->data[(*mat)->size[0]][(*mat)->size[1]++] = atoi(buffer);
            buffer_length = 0;
            (*mat)->data[(*mat)->size[0]] = realloc((*mat)->data[(*mat)->size[0]], sizeof(int) * ((*mat)->size[1] + 1));
        }
        //';' means, that we need to add new line in the matrix and reset buffer
        else if (buffer[buffer_length] == ';')
        {
            getchar();
            buffer[buffer_length] = '\0';

            if ((*mat)->size[0] == 0)
            {
                tmp_cols = (*mat)->size[1];
            }
            else if ((*mat)->size[1] != tmp_cols)
            {
                mt_error_inv_input();
            }

            (*mat)->data[(*mat)->size[0]++][(*mat)->size[1]] = atoi(buffer);
            (*mat)->size[1] = 0;
            buffer_length = 0;
        }
        //if the buffer's last char == '\n', so it's the end of the matrix input and something is wrong, because reading didn't finish yet.
        //if it's != '\n', so everything's okay.
        else if (buffer[buffer_length] != '\n')
        {
            buffer_length++;
        }
        //if the buffer's char not in '0'..'9' and '-', so something is wrong
        else if (buffer[buffer_length] < '0' || buffer[buffer_length] > '9' || buffer[buffer_length] != '-')
        {
            mt_error_inv_input();
        }
    }
    buffer[buffer_length] = '\0';
    (*mat)->data[(*mat)->size[0]++][(*mat)->size[1]++] = atoi(buffer);
    //skip a '\n' symbol in the end of reading matrix
    getchar();
    //if reading matrix is successful, return 1
    return 1;
}

//creating empty matrix of [rows x cols] size, filled with 0
matrix * mt_create(char name, int rows, int cols)
{
    matrix * mat = (matrix *)malloc(sizeof(struct matrix));
    mat->name = name;
    mat->size[0] = rows;
    mat->size[1] = cols;

    mat->data = malloc(mat->size[0] * sizeof(int*));
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        mat->data[i] = malloc(mat->size[1] * sizeof(int));
        for (size_t j = 0; j < mat->size[1]; j++)
        {
            mat->data[i][j] = 0;
        }
        
    }
    return mat;
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
        mt_error_inv_input();
    }
}

void  mt_comp_for_mul(matrix * mt_1, matrix * mt_2)
{
    if (mt_1->size[1] != mt_2->size[0])
    {
        mt_error_inv_input();
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
//I used matrix ** to free() it there
void mt_mul(matrix ** mt_destination, matrix * mt_multiplier)
{
    mt_comp_for_mul(*mt_destination, mt_multiplier);
    matrix *result = mt_create((*mt_destination)->name ,(*mt_destination)->size[0], mt_multiplier->size[1]);
    for (size_t i = 0; i < (*mt_destination)->size[0]; i++)
    {
        for (size_t j = 0; j < mt_multiplier->size[1]; j++)
        {
            result->data[i][j] = mt_mul_cell((*mt_destination), mt_multiplier, i, j);
        }
    }
    //deleting old data
    mt_free(&(*mt_destination));

    //replacing old data with new
    *mt_destination = result;
}

int mt_get_number_by_name(char name)
{
    int index = 0;
    while (mats_originals[index]->name != name)
    {
        index++;
    }
    return index;
}

//copy matrix
matrix * mt_cpy(matrix * mat)
{
    matrix * new_mat = mt_create(mat->name + 32, mat->size[0], mat->size[1]);
    for (size_t i = 0; i < mat->size[0]; i++)
    {
        for (size_t j = 0; j < mat->size[1]; j++)
        {
            new_mat->data[i][j] = mat->data[i][j];
        }
        
    }
    return new_mat;
}

int main()
{
    mats = malloc(sizeof(matrix *));
    mats_originals = malloc(sizeof(matrix *));

    last = 0;
    char * operations = malloc(1);
    while (mt_read(&mats_originals[last]) == 1)
    {
        mats_originals = realloc(mats_originals, sizeof(matrix *) * (++last + 1));
    }

    char read_buff = ' ';
    last_in_sequence = 0;
    while (scanf("%c", &read_buff) == 1 && read_buff != EOF && read_buff != '\n')
    {
        if (read_buff >= 'A' && read_buff <= 'Z')
        {
            mats[last_in_sequence] = mt_cpy(mats_originals[mt_get_number_by_name(read_buff)]);
        }
        else if (read_buff == '-' || read_buff == '+' || read_buff == '*')
        {
            operations[last_in_sequence++] = read_buff;
            operations = realloc(operations, last_in_sequence+1);
            mats = realloc(mats, sizeof(matrix *) * (last_in_sequence + 1));
        }
        else
        {
            mt_error_inv_input();
        }
    }

    int mt_mul_last = 0;
    int mt_tmp = 0;
    while (mt_mul_last < last_in_sequence)
    {
        if (operations[mt_mul_last] == '*')
        {
            mt_mul(&mats[mt_tmp], mats[++mt_mul_last]);
        }
        else
        {
            mt_tmp = ++mt_mul_last;
        }
    }

    for (size_t i = 0; i < last_in_sequence; i++)
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
    free(operations);
    mt_print(mats[0]);

    mt_free_all();
}
