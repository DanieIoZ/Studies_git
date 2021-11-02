#include <stdio.h>

#define height_to_fence_diff 1
#define lower_range 3
#define upper_range 69

//Prints a line, made by array of chars and count of each of them
//{ {3, 'X' }, { 2, 'Y' }, { 3, 'X' } } will print "XXXYYXXX"
//var array_elements is used, because sizeof() function was returning me something wrong, so it's used to get a length of first dimension in this 2D array
void fill_by_char(int data[][2], int array_elements, int new_line)
{
    for (int i = 0; i  < array_elements; i++)
        for (int j = 0; j < data[i][0]; j++)
        {
            printf("%c", data[i][1]);
        }
    if (new_line)
        printf("\n");
}

void fill_house(int width, int odd, int new_line)
{
    printf("%c", 'X');
    for (int i = 0; i < width-2; i++)
    {
        printf("%c", (i+odd)&1 ? '*' : 'o');
    }
    printf("%c", 'X');
    if (new_line)
        printf("\n");
}

void build_fence(int size, int inside_part)
{
    for (int i = size; i > 0; i--)
    {
        if (inside_part)
            printf("%c", i&1 ? '|' : ' ');
        else
            printf("%c", i&1 ? '|' : '-');
    }
    printf("\n");
}

int in_range(int range[], int num)        
{        
    return (range[0] <= num && num <= range[1]);         
}   


int main()
{
    int width = 0;
    int height = 0;
    int fence = 0;

    int scan_num = scanf("%d %d", &width, &height);
    int scan_required = 2;
    if (width == height)
    {
        scan_num += scanf("%d", &fence);
        scan_required++;
    }
    //Scanning vars and handling errors
    if (scan_num < scan_required)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return 100;
    }
    if (!(in_range((int [2]){lower_range, upper_range}, width) & in_range((int [2]){lower_range, upper_range}, height)))
    {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return 101;
    }
    if (!(width&1))
    {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return 102;
    }
    if ((scan_required == 3) && ((fence + height_to_fence_diff > height) || (fence < 1)))
    {
        fprintf(stderr, "Error: Neplatna velikost plotu!\n");
        return 103;
    }
   
    //Building a roof
    int half_width = width / 2;
    fill_by_char((int [][2]) { { half_width, ' ' }, { 1, 'X' }}, 2, 1);

    for (int i = 1; i < half_width; i++)
    {
        fill_by_char((int [][2]) { { half_width - i, ' ' }, { 1, 'X' }, { i * 2 - 1, ' ' }, { 1, 'X' }}, 4, 1);
    }
    fill_by_char((int [][2]) {{ width, 'X' }}, 1, 1);
    //building a house inside and a fence
    if (scan_required == 3)
        for (int i = 0; i < height - 2; i++)
        {
            
            int fence_started = (height - i - 2) < fence;
            fill_house(width, i%2, !fence_started);

            //In the task was written, that the fence must be "much smaller" than the height. So as a "much smaller" i took just 3 blocks
            if (fence_started)
            {
                if (height - i - 1 == fence)
                    build_fence(fence, 0);
                else
                    build_fence(fence, 1);

            }
        }
    else
        for (int i = 0; i < height - 2; i++)
        {
            fill_by_char((int [][2]) { { 1, 'X' },{ width-2, ' ' }, { 1, 'X' }}, 3, 1);
        }

    fill_by_char((int [][2]) {{ width, 'X' }}, 1, scan_num == 3 ? 0 : 1);
    if (scan_num == 3)
      build_fence(fence, 0);

    return 0;
}
