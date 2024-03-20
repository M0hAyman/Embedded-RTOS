#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"
void ourTask(){
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,1);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


// void func();
// void func(void);


int main(void){

	DIO_Init(PORT_F);
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
	xTaskCreate(ourTask,"Task 1",40,NULL,1,NULL);
	vTaskStartScheduler();
	for(;;){}

}