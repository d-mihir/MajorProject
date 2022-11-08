#include "glcd.h"
//pa0 - pa7 = data pins
//rs = pb0
// r/w = pb1
//	e = pb2
// cs1 = pb3
// cs2 = pb4;
// rst = pb5

const unsigned int c1[5][26] = {{0,0,0,0,0,0,0,0,0,128,192,224,240,248,248,0,0,0,0,0,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,128,128,192,255,255,255,255,192,128,128,0,0,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}};
int main(void)
{
	glcd_init();
	delayms(200);
	unsigned int var1,var2=0;
	unsigned int cPage,cColumn;
	while(1)
	{
		cColumn=0x40;
		for(var2=0;var2<5;var2++)
		{
			cPage = 0xB8+var2;
			glcd_command(cPage);
			glcd_command(cColumn);
			for(var1=0;var1<26;var1++)
			{
				glcd_data(c1[var2][var1]);
			}
		}
		delayms(500);
	}
}


