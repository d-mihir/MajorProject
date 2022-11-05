#include "stm32f4xx.h"
// data pins to port b
// rs, rw, en to port c10,c11,c12;
//this contains all lcd functions required
//wherever possible use or (or) and functions
void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<3195;i++);
}
void lcd_cmd(unsigned char cmd)
{
	GPIOC->ODR = 0x00000000; // make rs and rw 0
	GPIOB->ODR = cmd;
	delayms(1);
	GPIOC->ODR = 0x00001000; //make en high
	delayms(1);
	GPIOC->ODR = 0x00000000; // make en low
	if (cmd<4)
		delayms(4);
	else
		delayms(1);
}
void lcd_data(char data)
{
	GPIOC->ODR = 0x00000400; // rs=1 and rw=0;
	delayms(1);
	GPIOB->ODR = data;
	GPIOC->ODR = 0x00001400; //make en high
	delayms(1);
	GPIOC->ODR = 0x00000400; // make en low
	delayms(1);
}

void port_init(void)
{
	RCC->AHB1ENR = 0x00000006; // start clock for port b and port c
	GPIOB->MODER = 0x00005555; // make port b as output port
	GPIOC->MODER |= 0x01500000; // make c10,c11,c12 as output
}
void lcd_init(void)
{
	port_init();
	delayms(30);
	lcd_cmd(0x30);
	delayms(10);
	lcd_cmd(0x30);
	delayms(1);
	lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	lcd_cmd(0x0F);
}
