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
void delayms(int);
void glcd_command(unsigned int);
void glcd_data(unsigned int);

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
	GPIOB->ODR = 0x00000038; // cs1 is selected and cs2 is selected and rst = 1
	delayms(20);
	glcd_command(0x3E); // display off
	glcd_command(0x40); // set y address
	glcd_command(0xB8); // set x or page address
	glcd_command(0xC0);		
	glcd_command(0x3F);
	delayms(300);
}
void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<3195;i++);
}

void glcd_command(unsigned int cmd)
{
	
	//make rs and rw low
	GPIOB->ODR |= 0x00000001;
	delayms(20);
	GPIOA->ODR = cmd;
	//make en high
	GPIOB->ODR |= 0x00000005;
	delayms(20);
	//make en low
	GPIOB->ODR &= 0xfffffffb;
	delayms(20);
}


void glcd_data(unsigned int data)
{
	//make rs=1 and rw=0;
	GPIOB->ODR |= 0x00000001;
	delayms(20);
	GPIOA->ODR = data;
	//make en high
	GPIOB->ODR |= 0x00000005;
	delayms(20);
	//make en low
	GPIOB->ODR &= 0xfffffffb;
	
	//make rs=1 and rw=0
	
}
