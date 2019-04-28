;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
; This file was generated Sat Apr 27 13:44:48 2019
;--------------------------------------------------------
	.module clock_init
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
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
;	../hal/clock_init.c: 9: void clock_init(int wait){
;	-----------------------------------------
;	 function clock_init
;	-----------------------------------------
_clock_init:
;	../hal/clock_init.c: 10: _setbit(CLK_SWCR,CLK_SWCR_SWEN);
	ldw	x, #0x50c5
	ld	a, (x)
	or	a, #0x02
	ld	(x), a
;	../hal/clock_init.c: 11: CLK_SWR=CLK_SWR_HSE;
	mov	0x50c4+0, #0xb4
;	../hal/clock_init.c: 12: if (wait){
	ldw	x, (0x03, sp)
	jreq	00106$
;	../hal/clock_init.c: 13: while (CLK_CMSR!=CLK_SWR_HSE);
00101$:
	ldw	x, #0x50c3
	ld	a, (x)
	cp	a, #0xb4
	jrne	00101$
00106$:
	ret
	.area CODE
	.area INITIALIZER
	.area CABS (ABS)
