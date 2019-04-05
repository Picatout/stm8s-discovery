/*
*   declare all exported functions in hal
*/

#ifndef DISCO_H
#define DISCO_H
#include "stm8s105.h"

//macros
#define _enable_dev_clock(reg,dev) _setbit(reg,dev)

// exported functions
extern void clock_init(int wait);
extern void set_pin_mode(int port,int pin, int mode);

#endif
