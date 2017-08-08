/** \file BinaryHeap.h
 *  \brief Binary heap use to implement a priority queue
 * This is a min-heap : meaning the value of each node it greater or equal to the value of
 * its parents.
 *
 */

#ifndef BINARYHEAP_H_INCLUDED
#define BINARYHEAP_H_INCLUDED

#include <stdint.h>

#define HEAP_MAX_SIZE           (20U)   /**< Configure the size of the tree */
#define HEAP_TEST               (0)     /**< activate the test functions */

/**< Binary heap state type */
typedef enum {
    HEAP_OK,
    HEAP_FULL,
    HEAP_EMPTY,
    HEAP_ERROR
} Heap_state_t;

/**< Binary heap node structure */
typedef struct {
    int32_t value;
    void * data;
} Node_t;

/**< Binary heap structure */
typedef struct {
    uint32_t size;
    Node_t array[HEAP_MAX_SIZE];
} Heap_t;



Heap_state_t InitHeap(Heap_t* heap);
Heap_state_t HeapInsert(Heap_t* heap, Node_t data);
Heap_state_t HeapGetMin(Heap_t* heap, Node_t *data);
uint32_t HeapGetSize(Heap_t* heap);


#ifdef HEAP_TEST
void PrintHeap(const Heap_t * heap);
void TestPrintHeap(void);
void TestHeapInsertGetMin(void);

#endif //HEAP_TEST

#endif // BINARYHEAP_H_INCLUDED
