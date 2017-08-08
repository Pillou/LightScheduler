#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "scheduler.h"

int32_t task1(void * data);
int32_t task2(void * data);
int32_t task3(void * data);
int32_t task4(void * data);
int32_t task5(void * data);
int32_t task6(void * data);
int32_t task7(void * data);
int32_t task8(void * data);
void sleep_function(void);
void error_handler(int32_t error_id);

 const Task_t tasks[] = { {task1, "task 1"}, {task2, "task 2"}, {task3, "task 3"}, {task4, "task 4"}, \
                          {task5, "task 5"}, {task6, "task 6"}, {task7, "task 7"}, {task8, "task 8"} };

int main()
{
    int32_t i = 0;
    assert(SchedulerInit(sleep_function, error_handler) == 0);

    for(i=0; i<sizeof(tasks)/sizeof(tasks[0]); i++){
        assert(SchedulerAddTask(i, &tasks[i]) == 0);
    }

    SchedulerRunLoop();
    return 0;
}

void sleep_function(void){
    static int32_t count = 0;
    printf("\nenter sleep function (%d)\n", count);
    switch (count){
    case 0:
        printf("add task 6 (prio 10)\n");
        SchedulerAddTask(10, &tasks[5]);
        printf("add task 7 (prio 8)\n");
        SchedulerAddTask(8, &tasks[6]);
        printf("add task 8 (prio 9)\n");
        SchedulerAddTask(9, &tasks[7]);
        printf("add task 6 (prio 2)\n");
        SchedulerAddTask(2, &tasks[5]);
        printf("add task 2 (prio 6)\n");
        SchedulerAddTask(6, &tasks[1]);
        break;
    case 1:
        printf("add task 5 (prio 159)\n");
        SchedulerAddTask(159, &tasks[4]);
        printf("add task 7 (prio 158)\n");
        SchedulerAddTask(158, &tasks[6]);
        printf("add task 8 (prio 160)\n");
        SchedulerAddTask(160, &tasks[7]);
        printf("add task 6 (prio 300)\n");
        SchedulerAddTask(300, &tasks[5]);
        printf("add task 2 (prio 200)\n");
        SchedulerAddTask(200, &tasks[1]);
        break;
    default:
        printf("end of example\n");
        exit(0);
        break;
    }

    count ++;
}
void error_handler(int32_t error_id){
    if( error_id != 0){
        printf("error %d: detected\n", error_id);
    }
}

int32_t task1(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
int32_t task2(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
int32_t task3(void * data){
    printf("entering task %s\n", (char *) data);
    return 1;
}
int32_t task4(void * data){
    printf("entering task %s\n", (char *) data);
    return -1;
}
int32_t task5(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
int32_t task6(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
int32_t task7(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
int32_t task8(void * data){
    printf("entering task %s\n", (char *) data);
    return 0;
}
