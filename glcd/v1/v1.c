#include "stm32f4xx.h"
#define glcd_width 84
#define glcd_height 48

void glcd_setcursor(unsigned char x, unsigned char y);
void glcd_clear(void);
void glcd_init(void);
void glcd_data_write(unsigned char data);
void glcd_command_write(unsigned char data);
void glcd_putchar(int c);
void spi_init(void);
void spi_write(unsigned char data);

char font_table[][6]= {
	{0x7e,0x11,0x11,0x11,0x7e,0},
	{0x7f,0x49,0x49,0x49,0x36,0},
	{0x3e,0x41,0x41,0x41,0x22,0},
};


int main(void)
{
	glcd_init();
	glcd_clear();
	glcd_putchar(0);
	glcd_putchar(1);
	glcd_putchar(2);
	while(1){
	}
}



void glcd_putchar(int c){
	int i;
	for(i=0;i<6;i++)
	glcd_data_write(font_table[c][i]);
}

void glcd_setcursor(unsigned char x, unsigned char y)
{
	glcd_command_write(0x80 | x);
	glcd_command_write(0x40 | y);
	
}

void glcd_clear(void)
{
	int32_t index;
	for(index=0;index<(glcd_width * glcd_height / 8);index++)
	glcd_data_write(0x00);
	glcd_setcursor(0,0);
}


void gcd_init(void)
{
		spi_init();
	
	RCC->AHB1ENR |= 2;
	GPIOB->MODER &= ~0x00303000;
	GPIOB->MODER |= 0x00101000;
	GPIOB->BSRR = 0x04000000;
	GPIOB->BSRR = 0x00000400;
	
	glcd_command_write(0x21);
	glcd_command_write(0xB8);
	glcd_command_write(0x04);
	glcd_command_write(0x14);
	glcd_command_write(0x20);
	glcd_command_write(0x0C);
	
}

void glcd_data_write(unsigned char data)
{
	GPIOB->BSRR = 0x00000040;
	spi_write(data);
	
}

void glcd_command_write(unsigned char data)
{
	GPIOB->BSRR = 0x00400000;
	spi_write(data);
	
}

void spi_init(void)
{
	RCC->AHB1ENR |= 1;
	RCC->APB2ENR |= 0x1000;
	
	GPIOA->MODER |= 0x00008800;
	GPIOA->AFR[0] |= 0x50500000;
	
