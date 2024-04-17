#include "uart.h"
#include "DIO.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdlib.h>
char UART0Rx(void);
void printChar(char);
void printString(char *String, void (*PTR_Func)(char));
char counterString[21];


int counter = 0;
QueueHandle_t myQueue;
void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}
// Implementation of citoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    char isNegative = 0;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

void InitTask(void){
	UART0_init();
	DIO_Init(PORT_F);
	DIO_SetupDirection(PORT_F,IN,PIN0);
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_SetupDirection(PORT_F,IN,PIN4);
}

void BTN_one_check(void * params){
	for( ; ; ){
		if(DIO_ReadPin(PORT_F,PIN0) == 0){
			DIO_WritePin(PORT_F,LOGIC_HIGH,PIN1);
			counter++;
			while(DIO_ReadPin(PORT_F,PIN0) == 0);
			DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
		}
		taskYIELD();
	}

}

void BTN_two_check(void * params){
	for( ; ; ){
		if(DIO_ReadPin(PORT_F,PIN4) == 0){
			xQueueSendToBack(myQueue,&counter,0);
			counter = 0;
			while(DIO_ReadPin(PORT_F,PIN4) == 0);
		}
		taskYIELD();
	}
}

void sendToUart(void * paramss){
	int value;
	for( ; ; ){
		xQueueReceive(myQueue,&value,pdMS_TO_TICKS(100));
		printString(itoa(value,counterString,10),printChar);
		
	}
	
	
	
	
}

int main()
{

	myQueue = xQueueCreate(2,sizeof(int));
	InitTask();
	xTaskCreate(BTN_one_check,"Button 1",40,0,1,0);
	xTaskCreate(BTN_two_check,"Button 2",40,0,1,0);	
	xTaskCreate(sendToUart,"UART Task",40,0,2,0);		
	vTaskStartScheduler();
	
 
	

  
  /*// Configure PA0 and PA1 to be used for TX0 and RX0 respectively
  GPIO_PORTA_DEN_R = 0x3;
  GPIO_PORTA_AFSEL_R = 0x3;
  GPIO_PORTA_PCTL_R = 0x11;
  
  // Configure the leds of PORTF
  GPIO_PORTF_DEN_R = 0x0E;
  GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_DATA_R = 0x0E;*/
  
  //while(1){
  
    //printString ("write 'r' or 'g' or 'b'\n\r" , printChar);
    /* Receive character */
    //c= UART0Rx();
    //c = 'r';
    //printString (&c,printChar);
    //printString("\n",printChar);
        
  // End of While Loop
  }
  
// End of Main Function


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