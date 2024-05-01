#include "tm4c123gh6pm.h"

void UART0_init(void);
char UART0Rx(void);
void printChar(char);
void printString(char *String, void (*PTR_Func)(char));
void uartgpioA(void);