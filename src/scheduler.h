/** \file scheduler.c
 *  \brief Simple non-preemptive, priority based scheduler.
 * The priority queue is based on a binary heap.
 *
 */


#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include "BinaryHeap.h"

/**< Task function type */
typedef int32_t (*TaskFct_t)(void *data);

/**< Task type */
typedef struct {
    TaskFct_t task_fct;
    void *data;
} Task_t;

/**< Sleep function type */
typedef void (*SleepFct_t)(void);
/**< Error handler function type */
typedef void (*ErrorFct_t)(int32_t ret);


int SchedulerAddTask(int32_t priority, const Task_t *task);
int SchedulerInit(SleepFct_t sleep_fct, ErrorFct_t error_fct);
void SchedulerRunLoop(void);



#endif // SCHEDULER_H_INCLUDED
