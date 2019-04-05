/*
* 2019/04/04
*  clock  intialization
* 
*/
#include "../inc/stm8s105.h"

// initialize clock to use HSE 16 Mhz crystal
void clock_init(int wait){
		CLK_SWCR|=CLK_SWCR_SWEN;
		CLK_SWR=CLK_SWR_HSE;
		//CLK_CKDIVR&=0xf8; // no divisor on CPU clock
		//wait until switch done;
		if (wait){
			while (CLK_SWCR&CLK_SWCR_SWBSY);
		}
		
}

