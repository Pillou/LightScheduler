#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

typedef struct {
    unsigned int priority;
    void (*cb)(void);
} task_t;


#endif // TASK_H_INCLUDED
