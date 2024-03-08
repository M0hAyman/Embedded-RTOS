#include "types.h"
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include <stdbool.h>
#ifndef SYSTICK_H
#define SYSTICK_H

#define FREQ 16000000U
#define FREQ_BY_1000 16000
#define  num_ticks(delay) (((delay*FREQ_BY_1000)) - 1)
void SYSTICK_Enable(void);
void SYSTICK_Disable(void);
uint32 SYSTICK_PeriodGet(void); //function to get the period of timer in ticks
void SYSTICK_PeriodSet(uint32 ui32Period);
uint32 SYSTICK_valueGet(void);
uint8 SYSTICK_Is_time_out(void);






#endif