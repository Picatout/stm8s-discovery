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

/**
 * Timer 4 is a simple 8-bit upcounting counter.
 * Prescaler = 128, fMASTER = 16MHz, Counter = 125 => interrupt interval
 * is 1ms.
 */
static void timer4_init() {
    // CK_PSC (internal fMASTER) is divided by the prescaler value.
    TIM4_PSCR = TIM4_PSCR_128;
    // Enable update interrupt for timer 4
    TIM4_IER |= TIM4_IER_UIE;
    // Clear timer interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
    // auto-reload value
    TIM4_ARR=255; // maximum count
    // Enable timer 4
    TIM4_CR1 |= TIM4_CR1_CEN+TIM4_CR1_ARPE;
    interrupts();
}

// Timer 3 channel 2 used to control LED intensity.
static void pwm_init(){
	TIM3_CCMR2=(6<<TIM3_CCMR2_OC2M_POS)|(1<<TIM3_CCMR2_OC2PE_POS);
	TIM3_CCER1=TIM3_CCER1_CC2E;
	TIM3_CCR2H=0;
	TIM3_CCR2L=250;
	TIM3_ARRH=255;
	TIM3_ARRL=255;
	TIM3_CR1=TIM3_CR1_CEN|TIM3_CR1_ARPE;
}

void main(){
	clock_init(1);
	set_pin_mode(PD,PIN0,OUTPUT_OD_SLOW);
	timer4_init();
	pwm_init();
	_setbit(PD_ODR,PIN0);
	while (1){
	} 
}
 
void timer4_isr(void) __interrupt(INT_TIM4_OVF) {
#define SPEED 30
	static uint8_t post_div=SPEED, dir=1;
	static uint16_t dc=1;
	post_div--;
	if (!post_div){
		post_div=SPEED;
		if (dir){
			dc=(dc<<1)|1; 
			if (dc==65535) dir=1-dir;
		}else{
			dc=dc>>1;
			if (dc==1) dir=1-dir;
		}
	}	
	TIM3_CCR2H=dc>>8;
	TIM3_CCR2L=dc&0xff;
    // Clear interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
}

