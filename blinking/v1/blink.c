#include "stm32f4xx.h"

void delayms(int);
int main(void)
{
		RCC->AHB1ENR |= 0x00000002;
		GPIOB->MODER &= ~0x00000280;
	GPIOB->MODER |= 0x00000004;
	
	while(1)
	{
		GPIOB->ODR = 0x00000002;
		delayms(500);
		GPIOB->ODR = 0x00000000;
		delayms(500);
	}
}

void delayms(int n)
{
	int i;
	for(;n>0;n--)
	{
		for(i=0;i<3195;i++);
	}
}