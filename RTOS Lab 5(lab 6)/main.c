#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"


// void func();
// void func(void);
void vApplicationIdleHook(void){

 Toggle_Bit(GPIO_PORTF_DATA_R,2);
}

void Task1(){
	while(1){
		Toggle_Bit(GPIO_PORTF_DATA_R,1);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void Task2(){
	
	while(1){
		Toggle_Bit(GPIO_PORTF_DATA_R,3);
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

int main(void){

	DIO_Init(PORT_F);
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_WritePin(PORT_F,LOGIC_HIGH,PIN1);
	
	DIO_SetupDirection(PORT_F,OUT,PIN2);
	DIO_WritePin(PORT_F,LOGIC_HIGH,PIN2);
	
	DIO_SetupDirection(PORT_F,OUT,PIN3);
  DIO_WritePin(PORT_F,LOGIC_HIGH,PIN3);

	
	xTaskCreate(Task1,"Task 1",40,NULL,1,NULL);
	xTaskCreate(Task2,"Task 2",40,NULL,1,NULL);
	vTaskStartScheduler();
	for(;;){}

}