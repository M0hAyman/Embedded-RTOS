#include "DIO.h"
#include "interrupt.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//define a Semaphore handle
xSemaphoreHandle xBinarySemaphore;



//this Task "semaphoreTask" is awakened when the semaphore is available
void semaphoreTask(void *pvParameters){
xSemaphoreTake(xBinarySemaphore,0);
for(;;)
{
	xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
//use xSemaphoreTake function with max delay value, i.e. this task will be blocked until it takes the semaphore from ISR
//Toggle the Blue LED
	Toggle_Bit(GPIO_PORTF_DATA_R,2);
}
}



/* This Periodic task is preempted by the task "semaphoreTask" */
void vPeriodicTask(void *pvParameters){
for(;;)
{
	//Toggle the Red LED
	Toggle_Bit(GPIO_PORTF_DATA_R,1);
	vTaskDelay(1000/portTICK_RATE_MS);
}
}



//Initialize the hardware of Port-F
void PortF_Init(void){
DIO_Init(PORT_F);
DIO_SetupDirection(PORT_F,IN,PIN0);
DIO_SetupDirection(PORT_F,OUT,PIN1);
DIO_SetupDirection(PORT_F,OUT,PIN2);
	
DIO_WritePin(PORT_F,LOGIC_LOW,PIN0);
DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
DIO_WritePin(PORT_F,LOGIC_LOW,PIN2);

	// Setup the interrupt on PortF
		// Unmask the interrupts for PF0 
		// Make bits PF0 falling edge sensitive
		// Sense on Falling edge
		// Enable the Interrupt for PortF in NVIC
	interrupt_init(FALLING_EDGE);
	interrupt_enable_pin(PIN0);
	
}
/*------------------------------------------------------------------------*/
void GPIOF_Handler(void){
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//Give the semaphore to the Task named handler, use xSemaphoreGiveFromISR, refer to FreeRTOS documentation.
	xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
// clear the interrupt flag of PORTF
	 GPIO_PORTF_ICR_R |= 0x1;
/* Giving the semaphore may have unblocked a task - if it did and the
unblocked task has a priority equal to or above the currently executing
task then xHigherPriorityTaskWoken will have been set to pdTRUE and
portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
higher priority task.
NOTE: The syntax for forcing a context switch within an ISR varies between
FreeRTOS ports. The portEND_SWITCHING_ISR() macro is provided as part of
the Corte M3 port layer for this purpose. taskYIELD() must never be called
from an ISR!, use portEND_SWITCHING_ISR, refer to FreeRTOS documentation.*/
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
/*main function*/
/*------------------------------------------------------------------------*/
int main( void )
{
PortF_Init();
__asm("CPSIE i");
//vSemaphoreCreateBinary(xBinarySemaphore); //This is not working don't use it
xBinarySemaphore = xSemaphoreCreateBinary();
if( xBinarySemaphore != NULL )
{
/* Create the 'handler' task. This is the task that will be synchronized
with the interrupt. The handler task is created with a high priority to
ensure it runs immediately after the interrupt exits. In this case a
priority of 3 is chosen. */
xTaskCreate( semaphoreTask, "semaphoreTask", 40, NULL, 2, NULL );
/* Create the task that will periodically generate a software interrupt.
This is created with a priority below the handler task to ensure it will
get preempted each time the handler task exits the Blocked state. */
xTaskCreate( vPeriodicTask, "Periodic", 40, NULL, 1, NULL );
/* Start the scheduler so the created tasks start executing. */
vTaskStartScheduler();
}
/* If all is well we will never reach here as the scheduler will now be
running the tasks. If we do reach here then it is likely that there was
insufficient heap memory available for a resource to be created. */
for( ;; );
}
