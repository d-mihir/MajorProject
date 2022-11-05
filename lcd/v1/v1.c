#include "stm32f4xx.h"

//DATA PINS ARE CONNECTED TO PORT B
// RS = PORT C0
// R/W' = PORT C1
// EN = PORT C2
void delayms(int);
void lcd_cmd(unsigned char);
void lcd_data(char);
void port_init(void);
void lcd_init(void);
void lcd_string(char* str);

// main
int main(void)
{
	lcd_init();
	while(1)
	{
		lcd_string("amar");
		delayms(1000);
		lcd_cmd(0x01); // clearing the screen
		delayms(5);
		lcd_string("rishitha");
		delayms(1000);
		lcd_cmd(0x01); // clearing the screen
		delayms(5);
	}
	
}

// initialize the lcd including ports and the commands for the lcd
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

// for basic init of the ports
// for details regarding the ports being used refer to top.
void port_init(void)
{
	RCC->AHB1ENR = 0x00000006; // start clock for port b and port c
	GPIOB->MODER = 0x00005555; // make port b as output port
	GPIOC->MODER = 0x00000015; // make c0,c1,c2 as output
}


// to issue commands to lcd
void lcd_cmd(unsigned char cmd)
{
	GPIOB->ODR = cmd;
	//GPIOC->ODR = 0x00000000; // make rs and rw 0
	delayms(1);
	GPIOC->ODR |= 0x00000004; //make en high
	delayms(1);
	GPIOC->ODR &= 0x00000000; // make en low
	if (cmd<4)
		delayms(4);
	else
		delayms(1);
}

// to print data on lcd
// prints single characters for strings refer to lcd_string();
void lcd_data(char data)
{
	GPIOC->ODR = 0x00000001; // rs=1 and rw=0;
	delayms(1);
	GPIOB->ODR = data;
	GPIOC->ODR |= 0x00000004; //make en high
	delayms(0);
	GPIOC->ODR = 0x00000001; // make en low
	delayms(1);
}
	
// for generating a delay so that cmds to the lcd are settled
void delayms(int n)
{
	int i;
	for(;n>=0;n--)
	for(i=0;i<3195;i++);
}

// for printing strings
void lcd_string(char* str)
{
	while(*str)
	{
		lcd_data(*str);
		delayms(50);
		str++;
	}
}
