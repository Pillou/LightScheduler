/** \file scheduler.c
 *  \brief Simple non-preemptive, priority based scheduler.
 * The priority queue is based on a binary heap.
 * The task with the lowest priority will be executed.
 */


#include "scheduler.h"
#include <stddef.h>

/**< Scheduler type */
typedef struct{
    Heap_t priority_queue;
    SleepFct_t sleep_fct;
    ErrorFct_t error_fct;
} Scheduler_t;


/**< Structure containing the scheduler data */
static Scheduler_t scheduler;


/** \brief SchedulerInit
 * Initialize the scheduler
 * \param SleepFct_t sleep_fct      call back called when no task in the queue
 * \param ErrorFct_t error_fct      call back handling tasks return code
 * \return int                      0 if ok
 */
int SchedulerInit(SleepFct_t sleep_fct, ErrorFct_t error_fct){
    scheduler.sleep_fct = sleep_fct;
    scheduler.error_fct = error_fct;
    return InitHeap(&scheduler.priority_queue);
}

/** \brief SchedulerAddTask
 * Add a task to the scheduler
 * \param int32_t priority          priority of the task to add
 * \param const Task_t *task        task to add
 * \return int                      0 if ok
 */
int SchedulerAddTask(int32_t priority, const Task_t *task){
    Node_t node;
    node.value = priority;
    node.data = (void*)task;
    return HeapInsert(&scheduler.priority_queue, node);
}

/** \brief SchedulerRunLoop
 * Run the scheduler.
 * \param void
 * \return void
 */
void SchedulerRunLoop(void){
    int32_t ret = 0;
    while(1){
        Node_t node;
        while(HeapGetMin(&scheduler.priority_queue, &node) != HEAP_EMPTY){
            Task_t *task = (Task_t *)node.data;
            ret = task->task_fct(task->data);   // run task
            if(scheduler.error_fct != NULL){
                scheduler.error_fct(ret);       // handle return code
            }
        }
        if(scheduler.sleep_fct != NULL){
            scheduler.sleep_fct();
        }
    }
}
