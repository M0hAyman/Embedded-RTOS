//Made by Team 7
//Yehia Hasan
//Mohammed Ayman
//Mohammed Hesham
//Ismail Seddik
//Tarek Khaled (Lost)
//THUMB BIT SHOULD BE 1 (BIT 24) DEFAULT TO ALLOW THE PSR TO WORK
#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "SYSTICK.h"
#include "scheduler.h"
#define LED_RED PIN1
#define LED_BLUE PIN2
#define LED_GREEN PIN3

char counter = 0;
char flag=0;
//uint32 blinky1_st[40];
//uint32 blinky2_st[40];

//uint32* sp_blinky1=&blinky1_st[40];
//uint32* sp_blinky2=&blinky2_st[40];

void blink_red(void){
 //   while(1){
        DIO_WritePin(PORT_F,LOGIC_HIGH,LED_RED);
        DIO_WritePin(PORT_F,LOGIC_LOW,LED_RED);   
 //   }
}

void blink_blue(void){

        DIO_WritePin(PORT_F,LOGIC_HIGH,LED_BLUE);
        DIO_WritePin(PORT_F,LOGIC_LOW,LED_BLUE);   

}

void blink_green(void){
	
        DIO_WritePin(PORT_F,LOGIC_HIGH,LED_GREEN);
        DIO_WritePin(PORT_F,LOGIC_LOW,LED_GREEN);   
}

void setup(void){

    DIO_Init(PORT_F);
    DIO_SetupDirection(PORT_F,OUT,PIN1);
    DIO_SetupDirection(PORT_F,OUT,PIN2);
    DIO_SetupDirection(PORT_F,OUT,PIN3);
    SYSTICK_Enable();
    SYSTICK_PeriodSet(5); //The value inside is in ms

}

int main(void)
{

		

		
		setup();
		create_task(blink_red,5);
		create_task(blink_blue,10);
		create_task(blink_green,20);
//    volatile char run = 0;
//    if(run){
//	    blink_blue();
//    }
//    else{
//        blink_red();   
//    }

	while (1)
	{
		__asm("CPSID I");
		Tasks_Scheduler();
		__asm("CPSIE I");
		//do nothing here
	}
}

// this routine will execute after every one second

void SysTick_Handler(void)
{
    counter++;
	flag =1;
}