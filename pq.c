/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Anthony Pham
 * Email: phamanth@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq_elem {
    void* data;
    int priority;
};

struct pq {
    struct pq_elem* elems;
    int size;
    int capacity;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
    struct pq* new_pq = malloc(sizeof(struct pq));
    if (!new_pq) exit(1);
  
    new_pq->size = 0;
    new_pq->capacity = 8;
    new_pq->elems = malloc(new_pq->capacity * sizeof(struct pq_elem));
  
    if (!new_pq->elems) exit(1);
  
    return new_pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
    free(pq->elems);
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
int pq_isempty(struct pq* pq) {
    return (pq->size == 0);
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
void pq_insert(struct pq* pq, void* data, int priority) {
    if (pq->size == pq->capacity) {
        int new_capacity = pq->capacity * 2;
        struct pq_elem* new_elems = realloc(pq->elems, new_capacity * sizeof(struct pq_elem));
        if (!new_elems) exit(1);
        pq->elems = new_elems;
        pq->capacity = new_capacity;
    }
  
    int idx = pq->size;
    pq->elems[idx].data = data;
    pq->elems[idx].priority = priority;
    pq->size++;
  
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (pq->elems[idx].priority > pq->elems[parent].priority) {
            struct pq_elem temp = pq->elems[idx];
            pq->elems[idx] = pq->elems[parent];
            pq->elems[parent] = temp;
            idx = parent;
        } else {
            break;
        }
    }
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
void* pq_max(struct pq* pq) {
    return pq->elems[0].data;
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
int pq_max_priority(struct pq* pq) {
    return pq->elems[0].priority;
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
void* pq_max_dequeue(struct pq* pq) {
    void* max_data = pq->elems[0].data;
    pq->size--;
    pq->elems[0] = pq->elems[pq->size];
    int idx = 0;
  
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int swap_idx = idx;
      
        if (left < pq->size && pq->elems[left].priority > pq->elems[swap_idx].priority)
            swap_idx = left;
        if (right < pq->size && pq->elems[right].priority > pq->elems[swap_idx].priority)
            swap_idx = right;
        if (swap_idx == idx)
            break;
      
        struct pq_elem temp = pq->elems[idx];
        pq->elems[idx] = pq->elems[swap_idx];
        pq->elems[swap_idx] = temp;
        idx = swap_idx;
    }
    return max_data;
}
