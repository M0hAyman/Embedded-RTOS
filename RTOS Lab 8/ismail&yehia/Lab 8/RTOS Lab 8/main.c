#include "FreeRTOS.h"
#include "semphr.h"
#include "DIO.h"
#include "task.h"
xSemaphoreHandle binarySemaphore;
void init(void){
	DIO_Init(PORT_F);
	DIO_SetupDirection(PORT_F,IN,PIN0);
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_SetupDirection(PORT_F,OUT,PIN2);
	DIO_SetupDirection(PORT_F,IN,PIN4);
	GPIO_PORTF_IM_R|=0x11;
	Set_Bit(NVIC_EN0_R,30);
	NVIC_PRI7_R |= (5 << 21);
	
}
void PeriodicTask(void *params){
 
	for(;;){
	  Toggle_Bit(GPIO_PORTF_DATA_R,1);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

}


void SemaphoreTask(void *params){
xSemaphoreTake(binarySemaphore,0);

for(;;){

	xSemaphoreTake(binarySemaphore,portMAX_DELAY);
	  Toggle_Bit(GPIO_PORTF_DATA_R,2);

}

}


portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

void GPIOF_Handler(void){
	GPIO_PORTF_ICR_R=0XFF;
 xSemaphoreGiveFromISR(binarySemaphore,&xHigherPriorityTaskWoken);




	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	




}

int main(void){
	init();
	binarySemaphore= xSemaphoreCreateBinary(); 
	xTaskCreate(PeriodicTask,"periodicTask",140,0,1,0);
	xTaskCreate(SemaphoreTask,"SemaphoreTask",140,0,2,0);
  vTaskStartScheduler();
}