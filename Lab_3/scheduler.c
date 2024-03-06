#include "scheduler.h"
osThread TCB_arr[NUM_OF_TASKS];

void create_task (void (*Task)(), uint32 ms_periodicity )
{ 
		TCB_arr[pos].sp=Task;
		TCB_arr[pos].periodicity=ms_periodicity;
	  
	  pos++;
}


void Tasks_Scheduler  (void){
	 if(flag== 1){
	    flag =0;
		 for(int i = 0; i < NUM_OF_TASKS ; i++){
		  if((counter*5)%TCB_arr[i].periodicity==0){
				TCB_arr[i].sp();
			}
		 }
	 }
	 if(counter==4)
		 counter=0;
}