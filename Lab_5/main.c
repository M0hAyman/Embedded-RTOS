#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"
void TaskRed(void *pvParameters){
	
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void TaskBlue(void *pvParameters){
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

void TaskGreen(void *pvParameters){
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
}

// void func();
// void func(void);


int main(void){

	static const uint32 Red = 1;
	static const uint32 Blue = 2;
	static const uint32 Green = 3;//0011
	DIO_Init(PORT_F);
	
	//Red setup
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
	//Blue setup
	DIO_SetupDirection(PORT_F,OUT,PIN2);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN2);
	//Green setup
	DIO_SetupDirection(PORT_F,OUT,PIN3);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN3);
	
	xTaskCreate(TaskRed,"TaskRed",40,(void *)&Red,1,NULL); //1000 0100
	xTaskCreate(TaskBlue,"TaskBlue",40,(void *)&Blue,1,NULL);
	xTaskCreate(TaskGreen,"TaskGreen",40,(void *) &Green,1,NULL);

	vTaskStartScheduler();
	for(;;){}

}