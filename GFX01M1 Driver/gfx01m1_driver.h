#include "stm32f4xx.h"

//LCD dimensions defines
#define GFX01M1_WIDTH       240
#define GFX01M1_HEIGHT      320
#define GFX01M1_PIXEL_COUNT	GFX01M1_WIDTH * GFX01M1_HEIGHT
//ILI9341 LCD commands
#define GFX01M1_RESET			 		    	0x01
#define GFX01M1_SLEEP_OUT		  			0x11
#define GFX01M1_GAMMA			    			0x26
#define GFX01M1_DISPLAY_OFF					0x28
#define GFX01M1_DISPLAY_ON					0x29
#define GFX01M1_COLUMN_ADDR					0x2A
#define GFX01M1_PAGE_ADDR			  		0x2B
#define GFX01M1_GRAM				    		0x2C
#define GFX01M1_TEARING_OFF					0x34
#define GFX01M1_TEARING_ON					0x35
#define GFX01M1_DISPLAY_INVERSION		0xb4
#define GFX01M1_MAC			        		0x36
#define GFX01M1_PIXEL_FORMAT    		0x3A
#define GFX01M1_WDB			    	  		0x51
#define GFX01M1_WCD				      		0x53
#define GFX01M1_RGB_INTERFACE   		0xB0
#define GFX01M1_FRC					    	0xB1
#define GFX01M1_BPC					    	0xB5
#define GFX01M1_DFC				 	    	0xB6
#define GFX01M1_Entry_Mode_Set		0xB7
#define GFX01M1_POWER1						0xC0
#define GFX01M1_POWER2						0xC1
#define GFX01M1_VCOM1							0xC5
#define GFX01M1_VCOM2							0xC7
#define GFX01M1_POWERA						0xCB
#define GFX01M1_POWERB						0xCF
#define GFX01M1_PGAMMA						0xE0
#define GFX01M1_NGAMMA						0xE1
#define GFX01M1_DTCA							0xE8
#define GFX01M1_DTCB							0xEA
#define GFX01M1_POWER_SEQ					0xED
#define GFX01M1_3GAMMA_EN					0xF2
#define GFX01M1_INTERFACE					0xF6
#define GFX01M1_PRC				   	  	0xF7
#define GFX01M1_VERTICAL_SCROLL 	0x33

//List of colors
#define COLOR_BLACK           0x0000  
#define COLOR_NAVY            0x000F      
#define COLOR_DGREEN          0x03E0     
#define COLOR_DCYAN           0x03EF  
#define COLOR_MAROON          0x7800 
#define COLOR_PURPLE          0x780F
#define COLOR_OLIVE           0x7BE0     
#define COLOR_LGRAY           0xC618      
#define COLOR_DGRAY           0x7BEF    
#define COLOR_BLUE            0x001F    
#define COLOR_BLUE2			      0x051D
#define COLOR_GREEN           0x07E0      
#define COLOR_GREEN2		      0xB723
#define COLOR_GREEN3		      0x8000
#define COLOR_CYAN            0x07FF   
#define COLOR_RED             0xF800    
#define COLOR_MAGENTA         0xF81F    
#define COLOR_YELLOW          0xFFE0   
#define COLOR_WHITE           0xFFFF     
#define COLOR_ORANGE          0xFD20     
#define COLOR_GREENYELLOW     0xAFE5     
#define COLOR_BROWN 			    0XBC40 
#define COLOR_BRRED 			    0XFC07 


// Macros required don't know why to use them
#define swap(a,b) { int16_t t=a; a=b; b=t; }
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define min(a,b) (((a)<(b))?(a):(b))

//Function prototypes start below
//1. Write command to LCD
void GFX01M1_SendCommand(uint8_t com);
//2. Write data to LCD
void GFX01M1_SendData(uint8_t data);
//2.2 Write multiple/DMA
void GFX01M1_SendData_Multi(uint16_t Colordata, uint32_t size);
//3. Set cursor position
void GFX01M1_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
//4. Initialise function
void GFX01M1_Init(SPI_HandleTypeDef *spiLcdHandle, GPIO_TypeDef *csPORT, uint16_t csPIN, GPIO_TypeDef *dcPORT, uint16_t dcPIN, GPIO_TypeDef *resetPORT, uint16_t resetPIN);
//5. Write data to a single pixel
void GFX01M1_DrawPixel(uint16_t x, uint16_t y, uint16_t color); //Draw single pixel to ILI9341
//6. Fill the entire screen with a background color
void GFX01M1_Fill(uint16_t color); //Fill entire ILI9341 with color
//7. Rectangle drawing functions
void GFX01M1_Fill_Rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, uint16_t color);
//8. Circle drawing functions
void GFX01M1_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
static void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
static void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void GFX01M1_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
//9. Line drawing functions
void GFX01M1_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void GFX01M1_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void GFX01M1_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
//10. Triangle drawing
void GFX01M1_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void GFX01M1_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
//11. Text printing functions
void GFX01M1_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
void GFX01M1_printText(char text[], int16_t x, int16_t y, uint16_t color, uint16_t bg, uint8_t size);
//12. Image print (RGB 565, 2 bytes per pixel)
void GFX01M1_printImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t *data, uint32_t size);
//13. Set screen rotation
void GFX01M1_setRotation(uint8_t rotate);
//14. Get screen rotation
uint8_t GFX01M1_getRotation(void);