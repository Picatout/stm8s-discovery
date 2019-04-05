/*
 * 2019/04/04
 *  blink LED on PD0
 */
#include "../inc/stm8s105.h"

extern void clock_init(int wait);
extern void enable_dev_clock(int device);
extern void set_pin_output(int port,int pin, int mode);
extern void set_pin_input(int port,int pin,int mode);

void delay(uint32_t delay){
	while (delay) delay--;
}

void main(){
	clock_init(1);
	set_pin_output(PD,PIN0,OUTPUT_OD_SLOW);
	while (1){
		PD_ODR^=PIN0;
		delay(512500);
	}
}
 
