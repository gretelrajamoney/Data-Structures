/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Gretel Rajamoney
 * Email: rajamong@oregonstate.edu
 */

#include <stdlib.h>
#include "dynarray.h"
#include "pq.h"

 /*
  * This is the structure that represents a priority queue.  You must define
  * this struct to contain the data needed to implement a priority queue.
  * in addition, you want to define an element struct with both data and priority,
  * corresponding to the elements of the priority queue.
  */
struct pq
{
    struct dynarray* priority;
    struct dynarray* values;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create()
{
    struct pq* pointer = malloc(sizeof(struct pq));
    pointer->priority = dynarray_create();
    pointer->values = dynarray_create();
    return pointer;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq)
{
    dynarray_free(pq->priority);
    dynarray_free(pq->values);
    free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq)
{
    if (dynarray_length(pq->priority) != 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority)
{
    int stop;
    stop = dynarray_length(pq->priority);
    int* before = malloc(sizeof(int));
    *before = priority;
    dynarray_insert(pq->priority, stop, before);
    dynarray_insert(pq->values, stop, data);
    percolate_up(pq, stop);
}


/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq)
{
    return dynarray_get(pq->values, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq)
{
    int x = *((int*)dynarray_get(pq->priority, 0));
    return x;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq)
{
    void* num;
    num = dynarray_get(pq->values, 0);
    int stop;
    stop = dynarray_length(pq->values) - 1;
    swap_numbers(pq, 0, stop);
    dynarray_remove(pq->values, stop);
    dynarray_remove(pq->priority, stop);
    if (dynarray_length(pq->values) > 0)
    {
        percolate_down(pq, 0);
    }
    return num;
}

void swap_numbers(struct pq* pq, int x1, int x2)
{
    void* y1 = dynarray_get(pq->priority, x1);
    void* y2 = dynarray_get(pq->values, x1);
    dynarray_set(pq->priority, x1, dynarray_get(pq->priority, x2));
    dynarray_set(pq->values, x1, dynarray_get(pq->values, x2));
    dynarray_set(pq->priority, x2, y1);
    dynarray_set(pq->values, x2, y2);
}

void percolate_up(struct pq* pq, int stop)
{
    if (stop > 0)
    {
        int percolate_parent = (stop - 1) / 2;
        int priority_stop = (*((int*)dynarray_get(pq->priority, stop)));
        int priority_parent = (*((int*)dynarray_get(pq->priority, percolate_parent)));
        if (priority_stop > priority_parent)
        {
            swap_numbers(pq, percolate_parent, stop);
            percolate_up(pq, percolate_parent);
        }
    }
}

void percolate_down(struct pq* pq, int stop)
{
    int left;
    int right;
    right = 2 * stop + 2;
    left = 2 * stop + 1;
    int largest;
    if (right < dynarray_length(pq->values))
    {
        int priority_right = *((int*)dynarray_get(pq->priority, right));
        int priority_left = *((int*)dynarray_get(pq->priority, left));
        if (priority_right > priority_left)
        {
            largest = right;
        }
        else
        {
            largest = left;
        }

    }
    else
    {
        if (right < dynarray_length(pq->values))
        {
            largest = left;
        }
        else
        {
            return;
        }
    }
    if ((*((int*)dynarray_get(pq->priority, stop))) < (*((int*)dynarray_get(pq->priority, largest))))
    {
        swap_numbers(pq, stop, largest);
        percolate_down(pq, largest);
    }
}
