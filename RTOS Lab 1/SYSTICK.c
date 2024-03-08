#include "SYSTICK.h"
uint32 test;


void SYSTICK_Enable(void){
  Set_Bit(NVIC_ST_CTRL_R,0);
  Set_Bit(NVIC_ST_CTRL_R,1);
  Set_Bit(NVIC_ST_CTRL_R,2);
}

void SYSTICK_Disable(void){
 Clear_Bit(NVIC_ST_CTRL_R,0);
}

uint32 SYSTICK_PeriodGet(void){

  uint32 counterPreloadValue;
  counterPreloadValue = NVIC_ST_RELOAD_R;
  counterPreloadValue &= 0x00FFFFFF;
  return (counterPreloadValue / FREQ)*1000;
}

void SYSTICK_PeriodSet(uint32 ui32Period){
NVIC_ST_RELOAD_R = num_ticks(ui32Period);
}

uint32 SYSTICK_valueGet(void){
  
   uint32 counterCurrentValue;
  counterCurrentValue = NVIC_ST_CURRENT_R;
  counterCurrentValue &= 0x00FFFFFF;
  return (counterCurrentValue / FREQ)*1000;
}

uint8 SYSTICK_Is_time_out(void){
  return Get_Bit(NVIC_ST_CTRL_R,16);
}