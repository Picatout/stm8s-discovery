;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
; This file was generated Thu Apr  4 23:14:22 2019
;--------------------------------------------------------
	.module gpio
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _set_pin_input
	.globl _set_pin_output
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
;	../hal/gpio.c: 8: void set_pin_output(int port,int pin, int mode){
;	-----------------------------------------
;	 function set_pin_output
;	-----------------------------------------
_set_pin_output:
	sub	sp, #9
;	../hal/gpio.c: 10: gpio[port].ddr|=pin;
	ldw	x, (0x0c, sp)
	pushw	x
	push	#0x05
	push	#0x00
	call	__mulint
	addw	sp, #4
	addw	x, #0x5000
	ldw	(0x05, sp), x
	ldw	x, (0x05, sp)
	incw	x
	incw	x
	ld	a, (x)
	clr	(0x03, sp)
	or	a, (0x0f, sp)
	ld	yh, a
	ld	a, (0x03, sp)
	or	a, (0x0e, sp)
	ld	a, yh
	ld	(x), a
;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
	ldw	x, (0x05, sp)
	addw	x, #0x0003
	ldw	(0x01, sp), x
	ld	a, (0x0f, sp)
;	../hal/gpio.c: 14: gpio[port].cr2&=~pin;
	ldw	x, (0x05, sp)
	addw	x, #0x0004
	ldw	(0x08, sp), x
;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
	cpl	a
	ld	(0x07, sp), a
;	../hal/gpio.c: 11: switch(mode){
	ldw	x, (0x10, sp)
	cpw	x, #0x0000
	jreq	00101$
	ldw	x, (0x10, sp)
	cpw	x, #0x0001
	jreq	00103$
	ldw	x, (0x10, sp)
	cpw	x, #0x0002
	jreq	00102$
	ldw	x, (0x10, sp)
	cpw	x, #0x0003
	jreq	00104$
	jra	00106$
;	../hal/gpio.c: 12: case OUTPUT_OD_SLOW:
00101$:
;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	and	a, (0x07, sp)
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 14: gpio[port].cr2&=~pin;
	ldw	x, (0x08, sp)
	ld	a, (x)
	and	a, (0x07, sp)
	ldw	x, (0x08, sp)
	ld	(x), a
;	../hal/gpio.c: 15: break;
	jra	00106$
;	../hal/gpio.c: 16: case OUTPUT_OD_FAST:
00102$:
;	../hal/gpio.c: 17: gpio[port].cr1&=~pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	and	a, (0x07, sp)
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 18: gpio[port].cr2|=pin;
	ldw	x, (0x08, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x08, sp)
	ld	(x), a
;	../hal/gpio.c: 19: break;
	jra	00106$
;	../hal/gpio.c: 20: case OUTPUT_PP_SLOW:
00103$:
;	../hal/gpio.c: 21: gpio[port].cr1|=pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 22: gpio[port].cr2&=~pin;
	ldw	x, (0x08, sp)
	ld	a, (x)
	and	a, (0x07, sp)
	ldw	x, (0x08, sp)
	ld	(x), a
;	../hal/gpio.c: 23: break;
	jra	00106$
;	../hal/gpio.c: 24: case OUTPUT_PP_FAST:
00104$:
;	../hal/gpio.c: 25: gpio[port].cr1|=pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 26: gpio[port].cr2|=pin;
	ldw	x, (0x08, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0e, sp)
	rlwa	x
	or	a, (0x0f, sp)
	ld	xh, a
	ldw	x, (0x08, sp)
	ld	(x), a
;	../hal/gpio.c: 28: }
00106$:
	addw	sp, #9
	ret
;	../hal/gpio.c: 31: void set_pin_input(int port,int pin,int mode){
;	-----------------------------------------
;	 function set_pin_input
;	-----------------------------------------
_set_pin_input:
	sub	sp, #7
;	../hal/gpio.c: 33: gpio[port].cr1&=~pin;
	ldw	x, (0x0a, sp)
	pushw	x
	push	#0x05
	push	#0x00
	call	__mulint
	addw	sp, #4
	addw	x, #0x5000
	ldw	(0x04, sp), x
	ldw	x, (0x04, sp)
	addw	x, #0x0003
	ldw	(0x01, sp), x
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	xh, a
	ld	a, (0x0d, sp)
	cpl	a
	ld	(0x03, sp), a
	ld	a, xh
	and	a, (0x03, sp)
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 37: gpio[port].cr2&=~pin;
	ldw	x, (0x04, sp)
	addw	x, #0x0004
	ldw	(0x06, sp), x
;	../hal/gpio.c: 34: switch(mode){
	ldw	x, (0x0e, sp)
	cpw	x, #0x0000
	jreq	00101$
	ldw	x, (0x0e, sp)
	cpw	x, #0x0001
	jreq	00103$
	ldw	x, (0x0e, sp)
	cpw	x, #0x0002
	jreq	00102$
	ldw	x, (0x0e, sp)
	cpw	x, #0x0003
	jreq	00104$
	jra	00106$
;	../hal/gpio.c: 35: case INPUT_FLOAT_DI:
00101$:
;	../hal/gpio.c: 36: gpio[port].cr1&=~pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	and	a, (0x03, sp)
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 37: gpio[port].cr2&=~pin;
	ldw	x, (0x06, sp)
	ld	a, (x)
	and	a, (0x03, sp)
	ldw	x, (0x06, sp)
	ld	(x), a
;	../hal/gpio.c: 38: break;
	jra	00106$
;	../hal/gpio.c: 39: case INPUT_FLOAT_EI:
00102$:
;	../hal/gpio.c: 40: gpio[port].cr1&=~pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	and	a, (0x03, sp)
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 41: gpio[port].cr2|=pin;
	ldw	x, (0x06, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0c, sp)
	rlwa	x
	or	a, (0x0d, sp)
	ld	xh, a
	ldw	x, (0x06, sp)
	ld	(x), a
;	../hal/gpio.c: 42: break;
	jra	00106$
;	../hal/gpio.c: 43: case INPUT_PU_DI:
00103$:
;	../hal/gpio.c: 44: gpio[port].cr1|=pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0c, sp)
	rlwa	x
	or	a, (0x0d, sp)
	ld	xh, a
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 45: gpio[port].cr2&=~pin;
	ldw	x, (0x06, sp)
	ld	a, (x)
	and	a, (0x03, sp)
	ldw	x, (0x06, sp)
	ld	(x), a
;	../hal/gpio.c: 46: break;
	jra	00106$
;	../hal/gpio.c: 47: case INPUT_PU_EI:
00104$:
;	../hal/gpio.c: 48: gpio[port].cr1|=pin;
	ldw	x, (0x01, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0c, sp)
	rlwa	x
	or	a, (0x0d, sp)
	ld	xh, a
	ldw	x, (0x01, sp)
	ld	(x), a
;	../hal/gpio.c: 49: gpio[port].cr2|=pin;
	ldw	x, (0x06, sp)
	ld	a, (x)
	ld	xh, a
	clr	a
	or	a, (0x0c, sp)
	rlwa	x
	or	a, (0x0d, sp)
	ld	xh, a
	ldw	x, (0x06, sp)
	ld	(x), a
;	../hal/gpio.c: 51: }
00106$:
	addw	sp, #7
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
