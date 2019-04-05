/*
 * 2019/04/04
 *  heart beat LED on PD0
 *  Description:
 *      This version use a PWM to pulse the LED with triangular brigthness
 *  	pheripheral usage:
 * 			TIM3_CH2  pwm that control LED intensity on PD0
 * 			TIM4      delay betwen PWM duty cycle update, generate an interrupt
 */
#include "../inc/discovery.h"



void main(){
	clock_init(1);
	set_pin_mode(PD,PIN0,OUTPUT_OD_SLOW);
	_enable_dev_clock(CLK_PCKENR1,CLK_PCKENR1_TIM3);
	_enable_dev_clock(CLK_PCKENR1,CLK_PCKENR1_TIM4);
	while (1); 
}
 
