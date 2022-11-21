#include "stm32f4xx.h"
#include "delay.h"
#include "bitmap.h"
#include "glcd.h"
#include "horse.h"



int main(void)
	{
	ST7920_Init();
	delay(100);
	ST7920_SendString(0,0, "HELLO WORLD");
  ST7920_SendString(1,0, "FROM");
  ST7920_SendString(2,0, "EmbeddedExpertIO");
  ST7920_SendString(3,0, "1234567890!@#$%^");
	delay(2000);
	ST7920_Clear();
  ST7920_GraphicMode(1);
  ST7920_DrawBitmap(logo);
	delay(2000);
	ST7920_Clear();
	DrawCircle(110, 31, 12);

			DrawCircle(110, 31, 16);

			DrawLine(3, 60, 127, 33);

			ST7920_Update();
				
			delay(2000);
				
			DrawRectangle (100, 12, 20, 14);

			ST7920_Update();
				
			delay(2000);
				
			DrawFilledRectangle(30, 20, 30, 10);

			ST7920_Update();
				
			delay(2000);
			
			DrawFilledCircle(15, 30, 6);

			ST7920_Update();

			DrawFilledTriangle(1,5,10,5,6,15);

			ST7920_Update();
			
		  delay(2000);
			
			ST7920_Clear();
	while(1)
			{
			ST7920_DrawBitmap(horse1);
			ST7920_DrawBitmap(horse2);
			ST7920_DrawBitmap(horse3);
			ST7920_DrawBitmap(horse4);
			ST7920_DrawBitmap(horse5);
			ST7920_DrawBitmap(horse6);
			ST7920_DrawBitmap(horse7);
			ST7920_DrawBitmap(horse8);
			ST7920_DrawBitmap(horse9);
			ST7920_DrawBitmap(horse10);
			}
	
	
	
	}