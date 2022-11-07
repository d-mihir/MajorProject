#include "stm32f4xx.h"

//pa0 - pa7 = data pins
//rs = pb0
// r/w = pb1
//	e = pb2
// cs1 = pb3
// cs2 = pb4;
// rst = pb5

void port_init(void);
void glcd_init(void);
void glcd_command(unsigned char);
void glcd_data(unsigned char);
void delayms(int);

int main(void)
{
	
	while(1)
	{
		glcd_data(0x0D);	//i
		glcd_data(0xFF);
		delayms(500);
	}
	
}


void port_init(void)
{
	//enable clock to port a and port b
	RCC->AHB1ENR = 0x00000003;
	GPIOA->MODER = 0x00005555;
	GPIOB->MODER = 0x00000155;
}

void glcd_init(void)
{
	port_init();
	GPIOB->ODR |= 0x00000018; // cs1 is selected and cs2 is not selected and rst = 1
	glcd_command(0x3F);
	glcd_command(0x40);
	glcd_command(0xBB);
	glcd_command(0xC0);
	
	delayms(300);
}
void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<3195;i++);
}

void glcd_command(unsigned char x)
{
	GPIOA->ODR  = x;
	delayms(1);
	GPIOB->ODR |= 0x00000004; //make rs and rw = 0
	delayms(1);
	GPIOB->ODR &= 0x00000000; //make en low
	
	if(x<4)
		delayms(4);
	else
		delayms(1);	
}

void glcd_data(unsigned char x)
{
	GPIOA->ODR = x;
	delayms(1);
	GPIOB->ODR |= 0x00000005; // rs = 1 and rw = 0;
	delayms(1);
	GPIOB->ODR = 0x00000001;
	delayms(1);	
}