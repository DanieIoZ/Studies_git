#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

void print_stat(queue_t * q)
{
    printf("ACT_SIZE: %d | ", q->act_size);
    printf("SIZE: %d | ", q->size);
    printf("HEAD: %d | ", q->head);
    printf("TAIL: %d\n", q->tail);
}

int main(int argc, char * argv[])
{
    int cap = 0;
    scanf("%d", &cap);
    queue_t * q = create_queue(cap);

    int opt;
    if (argc > 1 && strcmp(argv[1], "-prp-optional") == 0)
        opt = 1;
    else
        opt = 0;

    char req;
        
    while (scanf("%c", &req) == 1 && req != EOF)
    {
        if (req == ' ' || req == '\n')
            continue;
        if (req == 'a')
        {
            int * inf;
            scanf("%d", &inf);
            if (opt)
                q = check_size(q, true);
            push_to_queue(q, inf);
            
        }
        else if (req == 'r')
        {
            void * res = pop_from_queue(q);
            if (opt)
                q = check_size(q, false);
            if (res == NULL)
                printf("NULL\n");
            else
                printf("%d\n", res);
        }
        else if (req == 'g')
        {
            int idx = 0;
            scanf("%d", &idx);
            void * res = get_from_queue(q, idx);
            if (res == NULL)
                printf("NULL\n");
            else
                printf("%d\n", res);
        }
    }
    delete_queue(q);
}
