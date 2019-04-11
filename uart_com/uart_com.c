/*
*  USART communication demo
*/

#include "../inc/discovery.h"


static const char error_msg[]="rx error\n";

static const char prompt[]="READY\n";

void print_prompt(){
	char *p;
	p=prompt;
	while (*p) uputc(*p++);
}

void print_error(){
	char *p;
	p=error_msg;
	while (*p) uputc(*p++);
}

inline void echo(char c){
	uputc(c);
}

void main(){
	signed char c;
	clock_init(1);
	enable_uart(B115200);
	print_prompt();
	while (1){
		c=ugetc();
		switch (c){
		case -1:
			print_error();
			break;
		case '\n':
		case '\r':
			uputc('\n');
			break;
		case 'p':
			print_prompt();
			break;
		default:
			echo(c);
		} 
		
	}
 
}
