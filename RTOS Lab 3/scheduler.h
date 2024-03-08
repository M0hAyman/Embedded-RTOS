#ifndef scheduler_h
#define scheduler_h
#include "types.h"
#define NUM_OF_TASKS 3

static char pos=0;
extern char flag;
extern char counter;
/*Creating a Thread Control Block*/
typedef struct{
    void (*sp)(); //Pointer to function
    uint32 periodicity;   
}osThread;


void create_task (void (*Task)(), uint32 ms_periodicity );
void Tasks_Scheduler  (void);

#endif