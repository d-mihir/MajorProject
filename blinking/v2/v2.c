#include "stm32f4xx.h"

int main(void)
{
	//pb1 as led
	RCC->AHB1ENR = 0x00000002;
	//GPIOB->MODER = ~0x00000280; //clear
	GPIOB->MODER = 0x00000004;
	//pb2 as switch pull up
	GPIOB->PUPDR = 0x00000400;

	
	while(1)
	{
		//if switch is pressed then glow light
		if(GPIOB->IDR & 0x0020)
		{
			GPIOB->ODR = 0x00000000;
		}
		else GPIOB->ODR = 0x00000002;
		
	}
	
}