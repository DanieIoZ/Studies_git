#ifndef __QUEUE_H__
#define __QUEUE_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define MIN_SIZE 1
/* Queue structure which holds all necessary data */
typedef struct {
    int size;
    int act_size;
    void ** data;

    int head;
    int tail;
} queue_t;

queue_t * create_queue(int capacity)
{
    queue_t * new_queue = malloc(sizeof(queue_t));
    new_queue->data = malloc(sizeof(void *) * capacity);
    new_queue->size = capacity;
    new_queue->head = 0;
    new_queue->tail = 0;
    new_queue->act_size = 0;
    return new_queue;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue)
{
    free(queue->data);
    free(queue);
}
/* 
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data)
{
    if ((queue->tail == queue->head) && (queue->act_size != 0))
        return false;
    
    queue->data[(queue->tail)++] = data;
    
    if (queue->tail == queue->size)
        queue->tail = 0;

    queue->act_size++;
    return true;
}
/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue)
{
    if (queue->act_size == 0)
    {
        void * res = NULL;
        return res;
    }
    void * result = queue->data[queue->head];
    if (++(queue->head) == queue->size)
        queue->head = 0;
    
    queue->act_size--;
    return result;
}
/* 
 * gets idx-th element from the queue
 * returns the element that will be popped after idx calls of the pop_from_queue() 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx)
{
    if (idx >= queue->act_size || idx < 0)
        return NULL;
    else if (queue->head + idx >= queue->size)
        return queue->data[queue->head + idx - queue->size];
    return queue->data[queue->head + idx];
}

queue_t * check_size(queue_t * queue, bool add)
{
    queue_t * new_q;
    if ((queue->act_size == queue->size) && add)
    {
        new_q = create_queue(queue->size * 2);
    }
    else if ((queue->act_size < (queue->size / 2)) && (!add) && ((queue->size / 2) > MIN_SIZE))
    {
        new_q = create_queue(queue->size / 2);
    }
    else
    {
        return queue;
    }
    while (queue->act_size != 0)
    {
        void * tmp = pop_from_queue(queue);
        push_to_queue(new_q, tmp);
    }
    delete_queue(queue);
    
    return new_q;
}

/* gets number of stored elements */
int get_queue_size(queue_t *queue)
{
    return queue->act_size;

}
#endif /* __QUEUE_H__ */
