#include "stm32f4xx.h"

void delayms(int);
int main(void)
{
	RCC->AHB1ENR=0x00000006; // start clock for port b and c
	GPIOB->MODER=0x00005555; // port b as output port
	GPIOC->MODER=0x00000005; // port C0 c1 as output port for controlling number	
	
	int arr[] = {63,6,91};
	int i=0;
	for(;;)
	{
		for(i=0;i<3;i++)
		{
			
			GPIOB->ODR=arr[i];
			GPIOC->BSRR = 0x00010000;
			GPIOC->BSRR = 0x00000002;
			delayms(500);
		}
		//GPIOB->ODR=0x006D;
		//GPIOC->BSRR=0x00020000;
		//GPIOB->BSRR=0x00000001;
		//delayms(8);
	}
}

void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<3195;i++);
}