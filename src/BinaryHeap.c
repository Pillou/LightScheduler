/** \file BinaryHeap.c
 *  \brief Binary heap use to implement a priority queue
 * This is a min-heap : meaning the value of each node it greater or equal to the value of
 * its parents.
 *
 * TODO : make automatic tests
 */
#include "BinaryHeap.h"

#ifdef HEAP_TEST
#include <stdio.h>
#include <assert.h>
#endif // HEAP_TEST

// static functions
static void _Swap(Heap_t * heap, uint32_t a, uint32_t b);
static void _HeapSwim( Heap_t * heap, uint32_t index );
static void _HeapSink( Heap_t * heap, uint32_t index );



/** \brief InitHeap
 * Initialize the heap structure
 * \param Heap_t * heap
 * \return Heap_state_t     HEAP_OK if ok
 */
Heap_state_t InitHeap( Heap_t * heap ){
    uint32_t i=0;
    for(i=0; i<HEAP_MAX_SIZE; i++){
        heap->array[i].data = NULL;
        heap->array[i].value = 0;
    }
    heap->size = 0;
    return HEAP_OK;
}

/** \brief HeapGetSize
 * Return the number of element in the heap
 * \param Heap_t * heap
 * \return uint32_t
 */
uint32_t HeapGetSize(Heap_t* heap){
    return heap->size;
}

/** \brief static void _Swap(Heap_t * heap, uint32_t a, uint32_t b)
 * local function which swap the value of index a and index b in the array
 * \param Heap_t * heap
 * \param uint32_t a
 * \param uint32_t b
 * \return void
 */
static void _Swap(Heap_t * heap, uint32_t a, uint32_t b){
    Node_t buffer;
    buffer = heap->array[a];
    heap->array[a] = heap->array[b];
    heap->array[b] = buffer;
}

/** \brief static void _HeapSwim( Heap_t * heap, uint32_t index )
 * local function which swim up the element starting at position index
 * \param Heap_t * heap
 * \param uint32_t index
 * \return void
 */
static void _HeapSwim( Heap_t * heap, uint32_t index ){
    while(index > 1 && heap->array[index].value < heap->array[index/2].value){
        _Swap(heap, index, index/2);
        index = index / 2;
    }
}

/** \brief Heap_state_t HeapInsert( Heap_t * heap, Node_t data)
 *
 * \param Heap_t * heap
 * \param Node_t data
 * \return Heap_state_t
 */
Heap_state_t HeapInsert( Heap_t * heap, Node_t data){
    if( heap->size >= HEAP_MAX_SIZE-1 )     return HEAP_ERROR;
    heap->size++;
    heap->array[heap->size] = data;
    _HeapSwim(heap, heap->size);
    if( heap->size >= HEAP_MAX_SIZE-1 )     return HEAP_FULL;
    return HEAP_OK;
}

/** \brief static void _HeapSink( Heap_t * heap, uint32_t index )
 *
 * \param Heap_t * heap
 * \param uint32_t index
 * \return void
 */
static void _HeapSink( Heap_t * heap, uint32_t index ){
    while(2*index <= heap->size){
        uint32_t j = 2*index;
        if( j+1 <= heap->size && heap->array[j].value > heap->array[j+1].value){
            j++;
        }
        if( heap->array[j].value > heap->array[index].value){
            break;
        }
        _Swap(heap, index, j);
        index = j;
    }
}

/** \brief Heap_state_t HeapGetMin(Heap_t * heap, Node_t *data )
 *
 * \param Heap_t * heap
 * \param Node_t *data
 * \return Heap_state_t
 */
Heap_state_t HeapGetMin(Heap_t * heap, Node_t *data ){
    if( heap->size == 0)    return HEAP_EMPTY;
    *data = heap->array[1];
    _Swap(heap, 1, heap->size);
    heap->size--;
    _HeapSink(heap, 1);
    return HEAP_OK;
}



#ifdef HEAP_TEST
static const char *_StateName( Heap_state_t t )
{
    switch(t) {
        case HEAP_OK:       return "HEAP_OK";
        case HEAP_EMPTY:    return "HEAP_EMPTY";
        case HEAP_FULL:     return "HEAP_FULL";
        case HEAP_ERROR:    return "HEAP_ERROR";
        default:            return "BAD STATE";
    }
}

void PrintHeap( const Heap_t * heap ){
    unsigned int i, j;
    printf("Size = %d\n", heap->size);

    printf("0: -\n");
    for(i = 1; i <= heap->size; i*=2){
        for(j = 0; i+j <= heap->size && j<i; j++){
            printf("%d: value %d, data pt %p ", i+j, heap->array[i+j].value, (void *)heap->array[i+j].data);
        }
        printf("\n");
    }
}

void TestPrintHeap(void){
    Heap_t heap_1 = {
        .array = {{0, NULL}, {1, NULL},{2, NULL},{3, NULL},{4, NULL},\
        {5, NULL},{6,NULL},{7,NULL},{8,NULL},{9,NULL},{10,NULL}},
        .size = 11
    };

    Heap_t heap_2 = {
        .array = {{0, NULL}, {1, NULL},{2, NULL},{3, NULL},{4, NULL},\
        {5, NULL},{6,NULL},{7,NULL},{8,NULL},{9,NULL},{10,NULL}},
        .size = 0
    };

    Heap_t heap_3 = {
        .array = {{0, NULL}, {1, NULL},{2, NULL},{3, NULL},{4, NULL},\
        {5, NULL},{6,NULL},{7,NULL},{8,NULL},{9,NULL},{10,NULL}},
        .size = 1
    };

    printf("\nStart testing TestPrintHeap:\n");
    PrintHeap(&heap_1);
    PrintHeap(&heap_2);
    PrintHeap(&heap_3);
}

void TestHeapInsertGetMin(void){
    Node_t unsorted[] = {{14, NULL}, {12, NULL},{25, NULL},{3, NULL},{45, NULL},\
                        {1, NULL},{165,NULL},{3,NULL},{88,NULL},{123,NULL},{170,NULL}};
    int i;


    printf("\nStart testing Insert and GetMin:\n");
    Heap_t h;
    InitHeap(&h);

    PrintHeap(&h);
    for(i=0; i<sizeof(unsorted)/sizeof(Node_t); i++){
        HeapInsert(&h, unsorted[i]);
        PrintHeap(&h);
    }
    for(i=0; i<sizeof(unsorted)/sizeof(Node_t); i++){
        Node_t node;
        HeapGetMin(&h, &node);
        printf("(value: %d, data: %p)", node.value, node.data);
    }
    PrintHeap(&h);

}


#endif // HEAP_TEST
