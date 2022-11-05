#include "stm32f4xx.h"


void init(void);
void write(int);
void delayms(int);
int main(void)
{
	while(1)
	{
		write('y');
		write('e');
		write('s');
		delayms(10);
	}
}

void init(void)
{
	RCC->AHB1ENR = 1;
	RCC->APB1ENR = 0x20000;
	GPIOA->AFR[0] = 0x0700;
	GPIOA->MODER = 0x00000020;
	USART2->BRR = 0x0683;
	USART2->CR1 = 0x0008;
	USART2->CR2 = 0x0000;
	USART2->CR3 = 0x0000;
	USART2->CR1 |= 0x2000; // enable the usart2
}

void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<2000;i++);
}

void write(int c)
{
	//check for the tx buffer is empty
	while(!(USART2->SR & 0x0080)){ }
	USART2->DR = (c & 0xFF);
}