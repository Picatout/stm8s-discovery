/*
*   USART functions
*   RX on PD5
*   TX on PD6
*/

#include "../inc/discovery.h"



void enable_uart(baud_t baud){
		set_pin_mode(PD,PIN5,OUTPUT_PP_FAST);
		set_pin_mode(PD,PIN0,OUTPUT_OD_SLOW);
		set_baudrate(baud);
		UART2_CR2=UART_CR2_TEN|UART_CR2_REN;
}

// brr divisor values for Fmaster=16Mhz
static const uint16_t brr_div[]={
		0x1a0b, // 2400
		0xd05,  // 4800
		0x693, // 9600
		0x341, // 19200
		0x1a1, // 38400
		0x116, // 57600
		0x8b, // 115200
		0x45, // 230400
		0x23, // 460800
		0x11, // 921600
};

void set_baudrate(baud_t baud){
	uint16_t br;
	br=brr_div[baud];
	UART2_BRR2=(br&0xf)+((br>>12)&0xf0);
	UART2_BRR1=(br>>4)&0xff;
}

uint8_t uchar(){
	return UART2_SR&UART_SR_RXNE?1:0;
}

signed char ugetc(){
	uint8_t status;
	signed char c;
	while (!(status=UART2_SR&(UART_SR_FE|UART_SR_OR|UART_SR_NF|UART_SR_RXNE)));
	c=UART2_DR;
	if (status != UART_SR_RXNE) c=-1;
}

void uputc(char c){
	while (!(UART2_SR&UART_SR_TXE));
	UART2_DR=c;
}
