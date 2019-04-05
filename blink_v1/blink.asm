;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
; This file was generated Thu Apr  4 23:14:22 2019
;--------------------------------------------------------
	.module blink
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _delay
	.globl _set_pin_output
	.globl _clock_init
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ;reset
	int 0x0000 ;trap
	int 0x0000 ;int0
	int 0x0000 ;int1
	int 0x0000 ;int2
	int 0x0000 ;int3
	int 0x0000 ;int4
	int 0x0000 ;int5
	int 0x0000 ;int6
	int 0x0000 ;int7
	int 0x0000 ;int8
	int 0x0000 ;int9
	int 0x0000 ;int10
	int 0x0000 ;int11
	int 0x0000 ;int12
	int 0x0000 ;int13
	int 0x0000 ;int14
	int 0x0000 ;int15
	int 0x0000 ;int16
	int 0x0000 ;int17
	int 0x0000 ;int18
	int 0x0000 ;int19
	int 0x0000 ;int20
	int 0x0000 ;int21
	int 0x0000 ;int22
	int 0x0000 ;int23
	int 0x0000 ;int24
	int 0x0000 ;int25
	int 0x0000 ;int26
	int 0x0000 ;int27
	int 0x0000 ;int28
	int 0x0000 ;int29
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	blink.c: 12: void delay(uint32_t delay){
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
;	blink.c: 13: while (delay) delay--;
	ldw	y, (0x05, sp)
	ldw	x, (0x03, sp)
00101$:
	tnzw	y
	jrne	00115$
	tnzw	x
	jreq	00104$
00115$:
	subw	y, #0x0001
	ld	a, xl
	sbc	a, #0x00
	rlwa	x
	sbc	a, #0x00
	ld	xh, a
	jra	00101$
00104$:
	ret
;	blink.c: 16: void main(){
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	blink.c: 17: clock_init(1);
	push	#0x01
	push	#0x00
	call	_clock_init
	addw	sp, #2
;	blink.c: 18: set_pin_output(PD,PIN0,OUTPUT_OD_SLOW);
	clrw	x
	pushw	x
	push	#0x01
	push	#0x00
	push	#0x03
	push	#0x00
	call	_set_pin_output
	addw	sp, #6
;	blink.c: 19: while (1){
00102$:
;	blink.c: 20: PD_ODR^=PIN0;
	ldw	x, #0x500f
	ld	a, (x)
	xor	a, #0x01
	ld	(x), a
;	blink.c: 21: delay(512500);
	push	#0xf4
	push	#0xd1
	push	#0x07
	push	#0x00
	call	_delay
	addw	sp, #4
	jra	00102$
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
