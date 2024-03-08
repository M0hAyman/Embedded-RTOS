//Made by Team 7
//Yehia Hasan
//Mohammed Ayman
//Mohammed Hesham
//Ismail Seddik
//Tarek Khaled (Lost)

#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "SYSTICK.h"

#define LED_RED PIN1
#define LED_BLUE PIN2

char counter = 0;

void blink_red(void){
    while(1){
        DIO_WritePin(PORT_F,LOGIC_HIGH,LED_RED);
        while(counter < 5);
        __asm("CPSID I");
        counter = 0;
        __asm("CPSIE I");
        DIO_WritePin(PORT_F,LOGIC_LOW,LED_RED);   
        while(counter < 5);
        __asm("CPSID I");
        counter = 0;
        __asm("CPSIE I");
    }
}

void blink_blue(void){
			while(1){
        DIO_WritePin(PORT_F,LOGIC_HIGH,LED_BLUE);
        while(counter < 10);
        __asm("CPSID I");
        counter = 0;
        __asm("CPSIE I");
        DIO_WritePin(PORT_F,LOGIC_LOW,LED_BLUE);   
        while(counter < 10);
        __asm("CPSID I");
        counter = 0;
        __asm("CPSIE I");
    }
}


void setup(void){

    DIO_Init(PORT_F);
    DIO_SetupDirection(PORT_F,OUT,PIN1);
    DIO_SetupDirection(PORT_F,OUT,PIN2);
    DIO_SetupDirection(PORT_F,OUT,PIN3);
    SYSTICK_Enable();
    SYSTICK_PeriodSet(100);

}

int main(void)
{

    setup();
    volatile char run = 0;
    if(run){
	    blink_blue();
    }
    else{
       blink_red();   
    }

	while (1)
	{
		//do nothing here
	}
}

// this routine will execute after every one second

void SysTick_Handler(void)
{
    counter++;

}