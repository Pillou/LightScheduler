/** \file BinaryHeap.c
 *  \brief
 * TODO : make automatic tests
 * TODO : switch from unsigned int to arbritary type
 * TODO : finish documentation
 */
#include "BinaryHeap.h"

#ifdef HEAP_TEST
#include <stdio.h>
#endif // HEAP_TEST

/** \brief void InitHeap( Heap_t * heap )
 * Initialize the heap structure
 * \param Heap_t * heap
 * \return void
 */
void InitHeap( Heap_t * heap ){
    heap->size = 0;
}

/** \brief static void _Swap(task_t *array, unsigned int a, unsigned int b)
 * local function which swap the value of of index a and index b in the array
 * \param task_t *array
 * \param unsigned int a
 * \param unsigned int b
 * \return void
 */
static void _Swap(task_t *array, unsigned int a, unsigned int b){
    task_t buffer;
    buffer = array[a];
    array[a] = array[b];
    array[b] = buffer;
}

/** \brief static void _HeapSwim( Heap_t * heap, unsigned int index )
 * local function which swim up the element starting at position index
 * \param Heap_t * heap
 * \param unsigned int index
 * \return void
 */
static void _HeapSwim( Heap_t * heap, unsigned int index ){
    while(index > 1 && heap->array[index].priority < heap->array[index/2].priority){
        _Swap(heap->array, index, index/2);
        index = index / 2;
    }
}

/** \brief Heap_state_t HeapInsert( Heap_t * heap, unsigned int data)
 *
 * \param Heap_t * heap
 * \param unsigned int data
 * \return Heap_state_t
 */
Heap_state_t HeapInsert( Heap_t * heap, task_t data){
    if( heap->size >= HEAP_MAX_SIZE-1 )     return HEAP_ERROR;
    heap->size++;
    heap->array[heap->size] = data;
    _HeapSwim(heap, heap->size);
    if( heap->size >= HEAP_MAX_SIZE-1 )     return HEAP_FULL;
    return HEAP_OK;
}

/** \brief static void _HeapSink( Heap_t * heap, unsigned int index )
 *
 * \param Heap_t * heap
 * \param unsigned int index
 * \return void
 */
static void _HeapSink( Heap_t * heap, unsigned int index ){
    while(2*index <= heap->size){
        unsigned int j = 2*index;
        if( j+1 <= heap->size && heap->array[j].priority > heap->array[j+1].priority){
            j++;
        }
        if( heap->array[j].priority > heap->array[index].priority){
            break;
        }
        _Swap(heap->array, index, j);
        index = j;
    }
}

/** \brief Heap_state_t HeapGetMin(Heap_t * heap, unsigned int *data )
 *
 * \param Heap_t * heap
 * \param unsigned int *data
 * \return Heap_state_t
 */
Heap_state_t HeapGetMin(Heap_t * heap, task_t *data ){
    if( heap->size == 0)    return HEAP_ERROR;
    *data = heap->array[1];
    _Swap(heap->array, 1, heap->size);
    heap->size--;
    _HeapSink(heap, 1);
    if( heap->size == 0)    return HEAP_EMPTY;
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
            printf("%d: prio %d, cb %p", i+j, heap->array[i+j].priority, (void *)heap->array[i+j].cb);
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
    task_t unsorted[] = {{14, NULL}, {12, NULL},{25, NULL},{3, NULL},{45, NULL},\
                        {1, NULL},{165,NULL},{3,NULL},{88,NULL},{123,NULL},{170,NULL}};
    task_t sorted[sizeof(unsorted)/sizeof(task_t)];
    int i;


    printf("\nStart testing Insert and GetMin:\n");
    Heap_t h;
    InitHeap(&h);

    PrintHeap(&h);
    for(i=0; i<sizeof(unsorted)/sizeof(task_t); i++){
        HeapInsert(&h, unsorted[i]);
        PrintHeap(&h);
    }
    for(i=0; i<sizeof(unsorted)/sizeof(task_t); i++){
        task_t task;
        HeapGetMin(&h, &task);
        printf("(prio: %d, cb: %p)", task.priority, task.cb);
    }
    PrintHeap(&h);

}


#endif // HEAP_TEST
