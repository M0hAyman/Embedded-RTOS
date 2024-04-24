#include "uart.h"



void UART0_init(void){
	SYSCTL_RCGCUART_R |= 1;

	while((SYSCTL_PRUART_R&0x00000001) == 0){};
  
  // UART Initialization
  UART0_CTL_R = 0;      // Stop the UART peripheral
  UART0_IBRD_R = 104;   // 16MHz/16 = 1 MHz , 1 MHz/104 = 9600 baud rate
  UART0_FBRD_R = 11;    // Fraction part
  UART0_CC_R = 0;       // Use system Clock
  UART0_LCRH_R = 0x60;  // 8-Bit Data, No parity, 1-Stop bit, No FIFO
  UART0_CTL_R = 0x301;  // Enable UART0, TXE, and RXE
}

void uartgpioA(void){
SYSCTL_RCGCGPIO_R=0X00000001;
while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
GPIO_PORTA_AFSEL_R |= (1<<1)|(1<<0);
GPIO_PORTA_PCTL_R |=(1<<0)|(1<<4);
GPIO_PORTA_DEN_R |= (1<<0)|(1<<1);
}

char UART0Rx(void)
{
    char c;
    while((UART0_FR_R & (1<<4)) != 0); // Wait until the FIFO is not empty
    c= UART0_DR_R ;                    // Read The Recieved DATA
    return c;
}

void printChar(char c){

    while((UART0_FR_R & (1<<5)) != 0); // Wait until the FIFO is Empty to put the new byte
    UART0_DR_R = c;
}

void printString(char *String, void (*PTR_Func)(char)){
  // This loop will continue until we get the null character
  while(*String){
  
    PTR_Func (*String);
    String++;    // Increment the address of the string elements by one
      
  }

}