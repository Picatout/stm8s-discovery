/*
 * 2019/04/04
 * GPIO configuration
 */

#include "../inc/stm8s105.h"

void set_pin_output(int port,int pin, int mode){
	gpio_t* gpio=(gpio_t*)GPIO;
	gpio[port].ddr|=pin;
	switch(mode){
		case OUTPUT_OD_SLOW:
			gpio[port].cr1&=~pin;
			gpio[port].cr2&=~pin;
			break;
		case OUTPUT_OD_FAST:
			gpio[port].cr1&=~pin;
			gpio[port].cr2|=pin;
			break;
		case OUTPUT_PP_SLOW:
			gpio[port].cr1|=pin;
			gpio[port].cr2&=~pin;
			break;
		case OUTPUT_PP_FAST:
			gpio[port].cr1|=pin;
			gpio[port].cr2|=pin;
			break;
	}
}

void set_pin_input(int port,int pin,int mode){
	gpio_t* gpio=(gpio_t*)GPIO;
	gpio[port].cr1&=~pin;
	switch(mode){
		case INPUT_FLOAT_DI:
			gpio[port].cr1&=~pin;
			gpio[port].cr2&=~pin;
			break;
		case INPUT_FLOAT_EI:
			gpio[port].cr1&=~pin;
			gpio[port].cr2|=pin;
			break;
		case INPUT_PU_DI:
			gpio[port].cr1|=pin;
			gpio[port].cr2&=~pin;
			break;
		case INPUT_PU_EI:
			gpio[port].cr1|=pin;
			gpio[port].cr2|=pin;
			break;
	}
}
