#include "stm32f4xx.h"
#ifndef __glcd__h
#define __glcd__h
#include "stdint.h"
uint8_t startRow, startCol, endRow, endCol; // coordinates of the dirty rectangle
uint8_t numRows = 64;
uint8_t numCols = 128;
uint8_t Graphic_Check = 0;
uint8_t image[(128 * 64)/8];


#define SCK_LOW     (GPIOA->BSRR=GPIO_BSRR_BR0)
#define SCK_HIGH    (GPIOA->BSRR=GPIO_BSRR_BS0)

#define CS_LOW      (GPIOA->BSRR=GPIO_BSRR_BR1)
#define CS_HIGH     (GPIOA->BSRR=GPIO_BSRR_BS1)

#define SID_LOW     (GPIOA->BSRR=GPIO_BSRR_BR4)
#define SID_HIGH    (GPIOA->BSRR=GPIO_BSRR_BS4)

#define RST_LOW     (GPIOA->BSRR=GPIO_BSRR_BR8)
#define RST_HIGH    (GPIOA->BSRR=GPIO_BSRR_BS8)

/* send the string to the LCD
 * 'row' = starting ROW for the string (from 0 to 3)
 * 'col' = starting COL for the string (from 0 to 7)
 */
void ST7920_SendString(int row, int col, char* string);


/* ENABLE or DISABLE the graphic mode
 * enable =1 --> graphic mode enabled
 */
void ST7920_GraphicMode (int enable);


// clear screen in any mode
void ST7920_Clear()
{
    if (Graphic_Check == 1)  // if the graphic mode is set
    {
        uint8_t x, y;
        for(y = 0; y < 64; y++)
        {
            if(y < 32)
            {
                ST7920_SendCmd(0x80 | y);
                ST7920_SendCmd(0x80);
            }
            else
            {
                ST7920_SendCmd(0x80 | (y-32));
                ST7920_SendCmd(0x88);
            }
            for(x = 0; x < 8; x++)
            {
                ST7920_SendData(0);
                ST7920_SendData(0);
            }
        }
    }

    else
    {
        ST7920_SendCmd(0x01);   // clear the display using command
        //delay(2); // delay >1.6 ms
    }
}

static void ST7920_SendCmd (uint8_t cmd)
{

	CS_HIGH;  // PUll the CS high

	SendByteSPI(0xf8+(0<<1));  // send the SYNC + RS(0)
	SendByteSPI(cmd&0xf0);  // send the higher nibble first
	SendByteSPI((cmd<<4)&0xf0);  // send the lower nibble
	delayUs(50);

	CS_LOW;  // PUll the CS LOW

}

static void ST7920_SendData (uint8_t data)
{

	CS_HIGH;

	SendByteSPI(0xf8+(1<<1));  // send the SYNC + RS(1)
	SendByteSPI(data&0xf0);  // send the higher nibble first
	SendByteSPI((data<<4)&0xf0);  // send the lower nibble
	delayUs(50);
	CS_LOW;  // PUll the CS LOW
}

// Draw bitmap on the display
void ST7920_DrawBitmap(const unsigned char* graphic);



// Update the display with the selected graphics
void ST7920_Update(void)
{
    ST7920_DrawBitmap(image);
}



// Initialize the display
void ST7920_Init (void)
{
    RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER|=(GPIO_MODER_MODE0_0|GPIO_MODER_MODE1_0|GPIO_MODER_MODE4_0|GPIO_MODER_MODE8_0);
    GPIOA->MODER&=~(GPIO_MODER_MODE0_1|GPIO_MODER_MODE1_1|GPIO_MODER_MODE4_1|GPIO_MODER_MODE8_1);
    GPIOA->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR0|GPIO_OSPEEDER_OSPEEDR1|GPIO_OSPEEDER_OSPEEDR4|GPIO_OSPEEDER_OSPEEDR8;
    
    RST_LOW;                    // RESET=0
    delay(10);   // wait for 10ms
    RST_HIGH;

    delay(50);   //wait for >40 ms


    ST7920_SendCmd(0x30);  // 8bit mode
    delayUs(110);  //  >100us delay

    ST7920_SendCmd(0x30);  // 8bit mode
    delayUs(40);  // >37us delay

    ST7920_SendCmd(0x08);  // D=0, C=0, B=0
    delayUs(110);  // >100us delay

    ST7920_SendCmd(0x01);  // clear screen
    delay(12);  // >10 ms delay


    ST7920_SendCmd(0x06);  // cursor increment right no shift
    delay(1);  // 1ms delay

    ST7920_SendCmd(0x0C);  // D=1, C=0, B=0
    delay(1);  // 1ms delay

    ST7920_SendCmd(0x02);  // return to home
    delay(1); 

    
}

static void SendByteSPI(uint8_t byte)
{
    for(int i=0;i<8;i++)
    {
        if((byte<<i)&0x80)
            {
                SID_HIGH;  // SID=1  OR MOSI
            }

        else {SID_LOW;}  // SID=0

        SCK_LOW;  // SCLK =0  OR SCK
        SCK_HIGH;  // SCLK=1
}
}
/* Common functions used
 * in other LCDs also
 */


// Set a pixel on the display
void SetPixel(uint8_t x, uint8_t y);



// draw line from (X0, Y0) to (X1, Y1)
void DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);


// draw rectangle from (X,Y) w- width, h- height
void DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);



// draw filled rectangle
void DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);



// draw circle with centre (X0, Y0) and radius= radius
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius);



// Draw Filled Circle with centre (X0, Y0) and radius= r

void DrawFilledCircle(int16_t x0, int16_t y0, int16_t r);



// Draw Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);



// Draw Filled Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);



#endif