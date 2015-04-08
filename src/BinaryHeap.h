/** \file BinaryHeap.h
 *  \brief
 */

#ifndef BINARYHEAP_H_INCLUDED
#define BINARYHEAP_H_INCLUDED

#include "task.h"

#define HEAP_MAX_SIZE           (20U)   /**< Configure the size of the tree */
#define HEAP_TEST               (1)     /**< activate the test functions */

/**< Binary heap state type */
typedef enum {
    HEAP_OK,
    HEAP_FULL,
    HEAP_EMPTY,
    HEAP_ERROR
} Heap_state_t;

/**< Binary heap structure */
typedef struct {
    unsigned int size;
    task_t array[HEAP_MAX_SIZE];
} Heap_t;

void InitHeap(Heap_t * heap);
Heap_state_t GetHeapState(const Heap_t * heap);

Heap_state_t HeapInsert(Heap_t * heap, task_t data);
Heap_state_t HeapGetMin(Heap_t * heap, task_t *data);

#ifdef HEAP_TEST
void PrintHeap(const Heap_t * heap);

void TestPrintHeap(void);
void TestHeapInsertGetMin(void);

#endif //HEAP_TEST

#endif // BINARYHEAP_H_INCLUDED
