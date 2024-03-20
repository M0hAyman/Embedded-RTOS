//Made by Team 7
//Yehia Hasan      (Lost)
//Mohammed Ayman
//Mohammed Hesham  (Lost)
//Ismail Seddik 
//Tarek Khaled 

#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_RED_PIN PIN1
#define LED_BLUE_PIN PIN2
#define LED_GREEN_PIN PIN3
//Task 1 example
void TaskRed(void *pvParameters){
	
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

//Task 2 example
void TaskBlue(void *pvParameters){
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

//Task 3 example
void TaskGreen(void *pvParameters){
	for( ; ; ){
		Toggle_Bit(GPIO_PORTF_DATA_R,(*(uint32*) pvParameters) );
		vTaskDelay(pdMS_TO_TICKS(3000));
	}
}


int main(void){

	//Parameters that would be passed to the 3 above functions (Just for trying "void pointer casting" stuff not really useful here)
	static const uint32 Red = LED_RED_PIN;
	static const uint32 Blue = LED_BLUE_PIN;
	static const uint32 Green = LED_GREEN_PIN;
	
	//Initiallizing the needed port for the 3 tasks
	DIO_Init(PORT_F);
	
	//Red task setup
	DIO_SetupDirection(PORT_F,OUT,PIN1);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
	//Blue task setup
	DIO_SetupDirection(PORT_F,OUT,PIN2);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN2);
	//Green task setup
	DIO_SetupDirection(PORT_F,OUT,PIN3);
	DIO_WritePin(PORT_F,LOGIC_LOW,PIN3);
	
	//Creating the 3 tasks that will run together with contex switch when a task is blocked
	
	//Below is the function prototype description
	/*BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName,
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask );*/
														
	xTaskCreate(TaskRed,"TaskRed",40,(void *)&Red,1,NULL);
	xTaskCreate(TaskBlue,"TaskBlue",40,(void *)&Blue,1,NULL);
	xTaskCreate(TaskGreen,"TaskGreen",40,(void *) &Green,1,NULL);

	vTaskStartScheduler();
	// The following line should never be reached. Omal mtnyleen 7tino leh???
	//for safety reasons: if the program goes kda wla kda we trap it here
	for(;;){}

}


//if you don't know the colors you could take a look:

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06