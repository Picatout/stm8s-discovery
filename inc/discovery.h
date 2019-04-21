/*
*   declare all exported functions in hal
*/

#ifndef DISCO_H
#define DISCO_H
#include "stm8s105.h"

#define TRUE -1
#define FALSE 0

typedef signed char bool;

//macros
#define LED PIN0   // on board green led connected PD0
#define _ledon() _clrbit(PD_ODR,LED)
#define _ledoff() _setbit(PD_ODR,LED)
#define _ledtoggle() _togglebit(PD_ODR,LED)
#define _enable_dev_clock(reg,dev) _setbit(reg,dev)

// exported functions
// system clock initialization to 16Mhz HSE
extern void clock_init(int wait);
// set GPIO pin direction speed, and pullup
extern void set_pin_mode(int port,int pin, int mode);
// UART2 communication
// enable UART2 communication 8N1
extern void enable_uart(baud_t baud);
// set communication speed
extern void set_baudrate(baud_t baud);
// check if character in receiver.
extern bool qchar();
// retreive character received
extern signed char ugetc();
// send character
extern void uputc(char c);
// print ASCIIZ string
extern void uprint(const char* str);
// read a line of text
extern uint8_t ureadln(char *buff, uint8_t size);
// print an integer in decimal base
void uprint_int(int16_t i);
// delete n character left of cursor
void delete_left(uint8_t n);
// unget character received from uart
void ungetc(signed char c);
//in situ uppercase
void upper(char* str);
// string comparison
int8_t strcmp(const char *s1, const char*s2);

#endif
