#include "uart.h"



void UART0_init(void){
	SYSCTL_RCGCUART_R = 1;

	while((SYSCTL_PRUART_R&0x00000001) == 0){};
  
  // UART Initialization
  UART0_CTL_R = 0;      // Stop the UART peripheral
  UART0_IBRD_R = 104;   // 16MHz/16 = 1 MHz , 1 MHz/104 = 9600 baud rate
  UART0_FBRD_R = 11;    // Fraction part
  UART0_CC_R = 0;       // Use system Clock
  UART0_LCRH_R = 0x60;  // 8-Bit Data, No parity, 1-Stop bit, No FIFO
  UART0_CTL_R = 0x301;  // Enable UART0, TXE, and RXE
}