#include "interrupt.h"


void interrupt_init(uint8 mode){
  switch(mode){
  case FALLING_EDGE:
    {
      Clear_Bit(GPIO_PORTF_IS_R , 0);
      Clear_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Clear_Bit(GPIO_PORTF_IEV_R, 0);
      Clear_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;
  case RISING_EDGE:
    {
      Clear_Bit(GPIO_PORTF_IS_R , 0);
      Clear_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Set_Bit(GPIO_PORTF_IEV_R, 0);
      Set_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;
  case HIGH_LEVEL:
    {
      Set_Bit(GPIO_PORTF_IS_R , 0);
      Set_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Set_Bit(GPIO_PORTF_IEV_R, 0);
      Set_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;
  case LOW_LEVEL:
    {
      Set_Bit(GPIO_PORTF_IS_R , 0);
      Set_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Clear_Bit(GPIO_PORTF_IEV_R, 0);
      Clear_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;    
  default:{
    
  }
    
  }  //end of switch
  
    //clear prior interrupts
    Set_Bit(GPIO_PORTF_ICR_R,0);
    Set_Bit(GPIO_PORTF_ICR_R,4);
    
    //set priority
    NVIC_PRI7_R |= 5 << 21; //To call FreeRtos APIS Priority can't be logically higher than free rtos configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
														//Here we used GPIO handler and used FreeRTOS functions in it so this is needed.
    
    //enable interrupt
    Set_Bit(NVIC_EN0_R,30);
} //end of function

void interrupt_enable_pin(uint8 pin_num){
  if(pin_num > 7){
  }
  
  Set_Bit(GPIO_PORTF_IM_R, pin_num);

}



