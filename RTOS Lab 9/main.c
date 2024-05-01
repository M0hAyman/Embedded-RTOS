#include "uart.h"
#include "DIO.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "interrupt.h"
#include <stdlib.h>
//char UART0Rx(void);
void printChar(char);
void printString(char *String, void (*PTR_Func)(char));
char counterString[21];


int counter = 0;
QueueHandle_t xIntegerQueue;
QueueHandle_t xStringQueue;
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
	uartgpioA();
	DIO_Init(PORT_F);
	DIO_SetupDirection(PORT_F,IN,PIN0);
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	interrupt_init(FALLING_EDGE);
	interrupt_enable_pin(PIN0);
}


void vIntegerGenerator( void *pvParameters )
{
	portTickType xLastExecutionTime;
	unsigned long ulValueToSend = 0;
	int i;
	/* Initialize the variable used by the call to vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();
	for( ;; )
	{
		/* This is a periodic task. Block until it is time to run again.
		The task will execute every 200ms. */
		vTaskDelayUntil( &xLastExecutionTime, 200 / portTICK_RATE_MS );
		/* Send an incrementing number to the queue five times. The values will
		be read from the queue by the interrupt service routine. The interrupt
		service routine always empties the queue so this task is guaranteed to be
		able to write all five values, so a block time is not required. */
		for( i = 0; i < 5; i++ )
		{
			xQueueSendToBack( xIntegerQueue, &ulValueToSend, 0 );
			ulValueToSend++;
		}
		ulValueToSend = 0;
		/* Force an interrupt so the interrupt service routine can read the
		values from the queue. */


		
	}
}

void GPIOF_Handler( void )
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	static unsigned long ulReceivedNumber;
	/* The strings are declared static const to ensure they are not allocated to the
	interrupt service routine stack, and exist even when the interrupt service routine
	is not executing. */
	static const char *pcStrings[] =
	{
		"String 0\n\r",
		"String 1\n\r",
		"String 2\n\r",
		"String 3\n\r",
		"String 4\n\r"
	};
	printString("Generator task - About to generate an interrupt.\n\r",printChar);
	DIO_WritePin(PORT_F,LOGIC_HIGH,PIN1);

	while(DIO_ReadPin(PORT_F,PIN0) == 0);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
	
	/* Loop until the queue is empty. */
	while( xQueueReceiveFromISR( xIntegerQueue,&ulReceivedNumber,&xHigherPriorityTaskWoken ) != errQUEUE_EMPTY )
	{
		/* Truncate the received value to the last two bits (values 0 to 3 inc.),
		then send the string that corresponds to the truncated value to the other
		queue. */
		//ulReceivedNumber &= 0x03;
		xQueueSendToBackFromISR( xStringQueue,
		&pcStrings[ ulReceivedNumber ], //pointer to pointer to character
		&xHigherPriorityTaskWoken );
	}
	/* Clear the software interrupt bit using the interrupt controllers Clear
	Pending register. */
	GPIO_PORTF_ICR_R |= 0x1;
	/* xHigherPriorityTaskWoken was initialised to pdFALSE. It will have then
	been set to pdTRUE only if reading from or writing to a queue caused a task
	of equal or greater priority than the currently executing task to leave the
	Blocked state. When this is the case a context switch should be performed.
	In all other cases a context switch is not necessary.
	NOTE: The syntax for forcing a context switch within an ISR varies between
	FreeRTOS ports. The portEND_SWITCHING_ISR() macro is provided as part of
	the Cortex-M3 port layer for this purpose. taskYIELD() must never be called
	from an ISR! */
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
	printString("Generator task - Interrupt generated.\n\r",printChar);
}



void sendToUart(void * paramss){
	char value[20];
	char* tst = value;
	portBASE_TYPE xStatus;
	for( ; ; ){
		xStatus = xQueueReceive(xStringQueue,&tst,pdMS_TO_TICKS(100));
		if(xStatus == pdPASS){
			printString(tst,printChar);
		}
	}
	
}

int main()
{

		/* Before a queue can be used it must first be created. Create both queues
	used by this example. One queue can hold variables of type unsigned long,
	the other queue can hold variables of type char*. Both queues can hold a
	maximum of 10 items. A real application should check the return values to
	ensure the queues have been successfully created. */
	xIntegerQueue = xQueueCreate( 10, sizeof( unsigned long ) );
	xStringQueue = xQueueCreate( 10, sizeof( char * ) );
	
	InitTask();
	xTaskCreate(vIntegerGenerator,"IntGen",40,0,1,0);
	
	xTaskCreate(sendToUart,"UART Task",40,0,2,0);		
	vTaskStartScheduler();
	

        
  // End of While Loop
		/* If all is well then main() will never reach here as the scheduler will
	now be running the tasks. If main() does reach here then it is likely that
	there was insufficient heap memory available for the idle task to be created.
	Chapter 5 provides more information on memory management. */
	for( ;; );
  }
  
// End of Main Function




