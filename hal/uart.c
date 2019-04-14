/*
*   USART functions
*   RX on PD5
*   TX on PD6
*/

#include "../inc/discovery.h"
#include "../inc/ascii.h"


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

// check if character available from UART2
uint8_t qchar(){
	return UART2_SR&UART_SR_RXNE;
}

// get a character from UART2
signed char ugetc(){
	uint8_t status;
	signed char c;
	while (!(status=UART2_SR&(UART_SR_FE|UART_SR_OR|UART_SR_NF|UART_SR_RXNE)));
	c=UART2_DR;
	if (status != UART_SR_RXNE) c=-1;
	return c;
}

// send a character via uart2
void uputc(char c){
	while (!(UART2_SR&UART_SR_TXE));
	UART2_DR=c;
}

void delete_left(uint8_t count){
	while(count){
		uputc(CTRL_H);
		uputc(' ');
		uputc(CTRL_H);
		count--;
	}
}

// read a line of text from UART2
// return line length
uint8_t ureadln(char *buf, uint8_t size){
	signed char c;
	uint8_t eol=0,len=0;
	
	while (!eol){
		c=ugetc();
		switch(c){
		case '\n':
		case '\r':
			uputc('\n');
			buf[len]=0;
			eol=1;
			break;
		case CTRL_H:
			if (len){
				uputc(CTRL_H);
				len--;
				uputc(' ');
				uputc(CTRL_H);
			}
			break;
		case CTRL_X:
			delete_left(len);
			len=0;
			break;
		default:
			if ((c>=' ') && (len<size)){
				uputc(c);
				buf[len++]=c;
			}
		}//switch
	}//while
	return len;
}

void uprint(const char* str){
	while (*str) uputc(*str++);
}

void uprint_int(int16_t i){
	char sign=0,j=8, str[8];
	if (i<0){ 
		sign=-1;
		i=-i;
	}
	str[--j]=0;
	while (i){
		str[--j]=i%10+'0';
		i/=10;
	}
	if (j==7) str[--j]='0';
	if (sign<0){
		str[--j]='-';
	}
	uprint(&str[j]);
}

