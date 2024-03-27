#include "DIO.h"

uint8 DIO_Init(uint8 PORT)
{
  switch (PORT)
  {
  case PORT_A:
    SYSCTL_RCGCGPIO_R=0X00000001;
    while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
    GPIO_PORTA_LOCK_R=0X4C4F434B;
    GPIO_PORTA_CR_R=0XFF;
    GPIO_PORTA_DEN_R = 0xFF;
  case 'B':
    SYSCTL_RCGCGPIO_R=0X00000002;
    while((SYSCTL_PRGPIO_R&0x00000002) == 0){};
    GPIO_PORTB_LOCK_R=0X4C4F434B;
    GPIO_PORTB_CR_R=0XFF;
    GPIO_PORTB_DEN_R = 0xFF;
  case 'C':
    SYSCTL_RCGCGPIO_R=0X00000004;
    while((SYSCTL_PRGPIO_R&0x00000004) == 0){};
    GPIO_PORTC_LOCK_R=0X4C4F434B;
    GPIO_PORTC_CR_R=0XFF;
    GPIO_PORTC_DEN_R = 0xFF;
  case 'D':
    SYSCTL_RCGCGPIO_R=0X00000008;
    while((SYSCTL_PRGPIO_R&0x00000008) == 0){};
    GPIO_PORTD_LOCK_R=0X4C4F434B;
    GPIO_PORTD_CR_R=0XFF;
    GPIO_PORTD_DEN_R = 0xFF;
  case 'E':
    SYSCTL_RCGCGPIO_R=0X00000010;
    while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
    GPIO_PORTE_LOCK_R=0X4C4F434B;
    GPIO_PORTE_CR_R=0XFF;
    GPIO_PORTE_DEN_R = 0xFF;
  case 'F':
    SYSCTL_RCGCGPIO_R=0X00000020;
    while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
    GPIO_PORTF_LOCK_R=0X4C4F434B;
    GPIO_PORTF_CR_R=0XFF;
    GPIO_PORTF_DEN_R = 0xFF;
    
  default:
    return -1;
  }
  return 0;
}

uint8 DIO_SetupDirection(uint8 PORT,uint8 direction,uint8 pin){
 
 if(pin < 0 || pin > NUM_PINS){
  return -1;
 }
 switch (PORT)
 {
 case PORT_A:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTA_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTA_DIR_R,pin);
          Set_Bit(GPIO_PORTA_PUR_R,pin);
      }
   }
   break;
 case PORT_B:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTB_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTB_DIR_R,pin);
          Set_Bit(GPIO_PORTB_PUR_R,pin);
      }
   }
   break;
 case PORT_C:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTC_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTC_DIR_R,pin);
          Set_Bit(GPIO_PORTC_PUR_R,pin);
      }
   }
   break;
 case PORT_D:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTD_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTD_DIR_R,pin);
          Set_Bit(GPIO_PORTD_PUR_R,pin);
      }
   }
   break;
 case PORT_E:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTE_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTE_DIR_R,pin);
          Set_Bit(GPIO_PORTE_PUR_R,pin);
      }
   }
   break;
 case PORT_F:
   {
      if(direction == OUT){
          Set_Bit(GPIO_PORTF_DIR_R,pin);
      }
      else if(direction == IN){
          Clear_Bit(GPIO_PORTF_DIR_R,pin);
          Set_Bit(GPIO_PORTF_PUR_R,pin);
      }
   }
   break;
 default:
    return -1;
 }    
return 0;
}

uint8 DIO_WritePort(uint8 PORT,uint8 VALUE)
 {
 switch (PORT)
 {
 case PORT_A:
   GPIO_PORTA_DATA_R = VALUE;
   break;
 case PORT_B:
   GPIO_PORTB_DATA_R = VALUE;
   break;
 case PORT_C:
   GPIO_PORTC_DATA_R = VALUE;
   break;
 case PORT_D:
   GPIO_PORTD_DATA_R = VALUE;
   break;
 case PORT_E:
   GPIO_PORTE_DATA_R = VALUE;
   break;
 case PORT_F:
   GPIO_PORTF_DATA_R = VALUE;
   break;
 default:
    return -1;
 }
 
 return 0;
 }
  
uint8 DIO_WritePin(uint8 port,uint8 value,uint8 pin){


 switch (port)
 {
 case PORT_A:
   {
     if(value)
       Set_Bit(GPIO_PORTA_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTA_DATA_R,pin);
   }
   break;
 case PORT_B:
   {
     if(value)
       Set_Bit(GPIO_PORTB_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTB_DATA_R,pin);
   }
   break;
 case PORT_C:
   {
     if(value)
       Set_Bit(GPIO_PORTC_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTC_DATA_R,pin);
   }
   break;
 case PORT_D:
   {
     if(value)
       Set_Bit(GPIO_PORTD_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTD_DATA_R,pin);
   }
   break;
 case PORT_E:
   {
     if(value)
       Set_Bit(GPIO_PORTE_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTE_DATA_R,pin);
   }
   break;
 case PORT_F:
   {
     if(value)
       Set_Bit(GPIO_PORTF_DATA_R,pin);
     else
       Clear_Bit(GPIO_PORTF_DATA_R,pin);
   }
   break;
 default:
    return -1;
 }
 
 return 0;
 }

uint8 DIO_ReadPort(uint8 PORT){

  switch (PORT)
 {
 case PORT_A:
   return GPIO_PORTA_DATA_R;
 case PORT_B:
   return GPIO_PORTB_DATA_R;
 case PORT_C:
   return GPIO_PORTC_DATA_R;
 case PORT_D:
   return GPIO_PORTD_DATA_R;
 case PORT_E:
   return GPIO_PORTE_DATA_R;
 case PORT_F:
   return GPIO_PORTF_DATA_R;
 default:
    return -1;
 }
 


}


uint8 DIO_ReadPin(uint8 PORT,uint8 pin){
  switch (PORT)
 {
 case PORT_A:
   return Get_Bit(GPIO_PORTA_DATA_R,pin);
 case PORT_B:
   return Get_Bit(GPIO_PORTB_DATA_R,pin);
 case PORT_C:
   return Get_Bit(GPIO_PORTC_DATA_R,pin);
 case PORT_D:
   return Get_Bit(GPIO_PORTD_DATA_R,pin);
 case PORT_E:
   return Get_Bit(GPIO_PORTE_DATA_R,pin);
 case PORT_F:
   return Get_Bit(GPIO_PORTF_DATA_R,pin);
 default:
    return -1;
 }
}