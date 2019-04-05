;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
; This file was generated Fri Apr  5 12:37:21 2019
;--------------------------------------------------------
	.module gpio
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _set_pin_mode
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	../hal/gpio.c: 8: void set_pin_mode(int port, int pin, int mode){
;	-----------------------------------------
;	 function set_pin_mode
;	-----------------------------------------
_set_pin_mode:
	sub	sp, #9
;	../hal/gpio.c: 9: volatile gpio_t* gpio=(volatile gpio_t*)(GPIO+port*sizeof(gpio_t));
	ldw	x, (0x0c, sp)
	pushw	x
	push	#0x05
	push	#0x00
	call	__mulint
	addw	sp, #4
	addw	x, #0x5000
	ldw	(0x05, sp), x
;	../hal/gpio.c: 11: _setbit(gpio->ddr,pin);
	ldw	x, (0x05, sp)
	incw	x
	incw	x
;	../hal/gpio.c: 13: _clrbit(gpio->ddr,pin);
	ld	a, (0x0f, sp)
	cpl	a
	ld	(0x09, sp), a
;	../hal/gpio.c: 10: if (mode&4){
	ld	a, (0x11, sp)
	bcp	a, #0x04
	jreq	00102$
;	../hal/gpio.c: 11: _setbit(gpio->ddr,pin);
	ld	a, (x)
	clr	(0x07, sp)
	or	a, (0x0f, sp)
	ld	yh, a
	ld	a, (0x07, sp)
	or	a, (0x0e, sp)
	ld	a, yh
	ld	(x), a
	jra	00103$
00102$:
;	../hal/gpio.c: 13: _clrbit(gpio->ddr,pin);
	ld	a, (x)
	and	a, (0x09, sp)
	ld	(x), a
00103$:
;	../hal/gpio.c: 15: switch(mode){
	tnz	(0x10, sp)
	jrpl	00128$
	jp	00113$
00128$:
	ldw	x, (0x10, sp)
	cpw	x, #0x0007
	jrsle	00129$
	jp	00113$
00129$:
;	../hal/gpio.c: 18: _clrbit(gpio->cr1,pin);
	ldw	y, (0x05, sp)
	addw	y, #0x0003
;	../hal/gpio.c: 19: _clrbit(gpio->cr2,pin);
	ldw	x, (0x05, sp)
	addw	x, #0x0004
	ldw	(0x03, sp), x
;	../hal/gpio.c: 15: switch(mode){
	ldw	x, (0x10, sp)
	sllw	x
	ldw	x, (#00130$, x)
	jp	(x)
00130$:
	.dw	#00104$
	.dw	#00108$
	.dw	#00106$
	.dw	#00110$
	.dw	#00105$
	.dw	#00109$
	.dw	#00107$
	.dw	#00111$
;	../hal/gpio.c: 16: case INPUT_FLOAT_DI:
00104$:
;	../hal/gpio.c: 17: case OUTPUT_OD_SLOW:
00105$:
;	../hal/gpio.c: 18: _clrbit(gpio->cr1,pin);
	ld	a, (y)
	and	a, (0x09, sp)
	ld	(y), a
;	../hal/gpio.c: 19: _clrbit(gpio->cr2,pin);
	ldw	x, (0x03, sp)
	ld	a, (x)
	and	a, (0x09, sp)
	ldw	x, (0x03, sp)
	ld	(x), a
;	../hal/gpio.c: 20: break;
	jra	00113$
;	../hal/gpio.c: 21: case INPUT_FLOAT_EI:
00106$:
;	../hal/gpio.c: 22: case OUTPUT_OD_FAST:
00107$:
;	../hal/gpio.c: 23: _clrbit(gpio->cr1,pin);
	ld	a, (y)
	and	a, (0x09, sp)
	ld	(y), a
;	../hal/gpio.c: 24: _setbit(gpio->cr2,pin);
	ldw	x, (0x03, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x03, sp)
	ld	(x), a
;	../hal/gpio.c: 25: break;
	jra	00113$
;	../hal/gpio.c: 26: case INPUT_PU_DI:
00108$:
;	../hal/gpio.c: 27: case OUTPUT_PP_SLOW:
00109$:
;	../hal/gpio.c: 28: _setbit(gpio->cr1,pin);
	ld	a, (y)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ld	(y), a
;	../hal/gpio.c: 29: _clrbit(gpio->cr2,pin);
	ldw	x, (0x03, sp)
	ld	a, (x)
	and	a, (0x09, sp)
	ldw	x, (0x03, sp)
	ld	(x), a
;	../hal/gpio.c: 30: break;
	jra	00113$
;	../hal/gpio.c: 31: case INPUT_PU_EI:
00110$:
;	../hal/gpio.c: 32: case OUTPUT_PP_FAST:
00111$:
;	../hal/gpio.c: 33: _setbit(gpio->cr1,pin);
	ld	a, (y)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ld	(y), a
;	../hal/gpio.c: 34: _setbit(gpio->cr2,pin);
	ldw	x, (0x03, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x03, sp)
	ld	(x), a
;	../hal/gpio.c: 36: }
00113$:
	addw	sp, #9
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
