#include "tm4c123gh6pm.h" 
#include "bitwise_operation.h"
#include "types.h"
#define NUM_PINS 8
//6 Ports A-F
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'
#define PORT_E 'E'
#define PORT_F 'F'

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define OUT 1
#define IN 0

#define LOGIC_HIGH 1
#define LOGIC_LOW 0
//Random Description
uint8 DIO_Init(uint8 PORT);
uint8 DIO_WritePort(uint8 PORT,uint8 VALUE);
uint8 DIO_WritePin(uint8 PORT,uint8 VALUE,uint8 pin);
uint8 DIO_SetupDirection(uint8 PORT,uint8 VALUE,uint8 pin);
uint8 DIO_ReadPort(uint8 PORT);
uint8 DIO_ReadPin(uint8 PORT,uint8 pin);

