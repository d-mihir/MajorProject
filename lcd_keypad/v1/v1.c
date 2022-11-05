#include "stm32f4xx.h"
#include "lcd.h"
#include<string.h>
void delay(void);
void keypad_init(void);

char keypad_press(void);


int main(void)
{
	lcd_init(); // initialize lcd
	keypad_init(); //initialize keypad
	
	RCC->AHB1ENR |= 0x00000001; // start port a clock
	GPIOA->MODER |= 0x00000400; // make pa5 as output port.
	lcd_data('o');
	delayms(50);
	lcd_data('k');
	delayms(100);
	lcd_cmd(0x01);
	delayms(500);
	while(1)
	{ 
		char temp = keypad_press();
		if(strcmp(temp,'0')){ // if key is not pressed
			GPIOA->ODR = 0x00000000;
		}
		else{ //if any key is pressed
			GPIOA->ODR = 0x00000020;
		}
		//delayms(500);
	}
	
}

void keypad_init(void)
{
	RCC->AHB1ENR |= 0x00000014; // start port c clock
	GPIOC->MODER = 0x00000000; 
	GPIOC->PUPDR = 0x00000055; // enable pull up resistors for columns
}

char keypad_press(void)
{
		int col;
	GPIOC->MODER = 0x00005500; // make row pins as output
	GPIOC->ODR = 0x00000000; // drive all pins low
	delay();
	col = GPIOC->IDR & 0x000F; // read all column pins
	if(col==0x000F) return '0'; // all are high therefore no key has been pressed
	else { lcd_data('a'); delayms(50); return 'a';}
}

void delay(void)
{
	int i;
	for(i=0;i<20;i++);
}


/*
		*/