#include "stm32f4xx.h"
//pc0-pc3 are columns and pc4-pc7 are rows
void keypad_init(void)
{	
	//start port c clock
	RCC->AHB1ENR = 0x00000004;
	
}

char keypad_scan(void)
{
	
}

void delay(void)
{
	
}