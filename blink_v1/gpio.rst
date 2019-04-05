                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
                                      4 ; This file was generated Fri Apr  5 12:37:21 2019
                                      5 ;--------------------------------------------------------
                                      6 	.module gpio
                                      7 	.optsdcc -mstm8
                                      8 	
                                      9 ;--------------------------------------------------------
                                     10 ; Public variables in this module
                                     11 ;--------------------------------------------------------
                                     12 	.globl _set_pin_mode
                                     13 ;--------------------------------------------------------
                                     14 ; ram data
                                     15 ;--------------------------------------------------------
                                     16 	.area DATA
                                     17 ;--------------------------------------------------------
                                     18 ; ram data
                                     19 ;--------------------------------------------------------
                                     20 	.area INITIALIZED
                                     21 ;--------------------------------------------------------
                                     22 ; absolute external ram data
                                     23 ;--------------------------------------------------------
                                     24 	.area DABS (ABS)
                                     25 ;--------------------------------------------------------
                                     26 ; global & static initialisations
                                     27 ;--------------------------------------------------------
                                     28 	.area HOME
                                     29 	.area GSINIT
                                     30 	.area GSFINAL
                                     31 	.area GSINIT
                                     32 ;--------------------------------------------------------
                                     33 ; Home
                                     34 ;--------------------------------------------------------
                                     35 	.area HOME
                                     36 	.area HOME
                                     37 ;--------------------------------------------------------
                                     38 ; code
                                     39 ;--------------------------------------------------------
                                     40 	.area CODE
                                     41 ;	../hal/gpio.c: 8: void set_pin_mode(int port, int pin, int mode){
                                     42 ;	-----------------------------------------
                                     43 ;	 function set_pin_mode
                                     44 ;	-----------------------------------------
      0080B8                         45 _set_pin_mode:
      0080B8 52 09            [ 2]   46 	sub	sp, #9
                                     47 ;	../hal/gpio.c: 9: volatile gpio_t* gpio=(volatile gpio_t*)(GPIO+port*sizeof(gpio_t));
      0080BA 1E 0C            [ 2]   48 	ldw	x, (0x0c, sp)
      0080BC 89               [ 2]   49 	pushw	x
      0080BD 4B 05            [ 1]   50 	push	#0x05
      0080BF 4B 00            [ 1]   51 	push	#0x00
      0080C1 CD 81 C6         [ 4]   52 	call	__mulint
      0080C4 5B 04            [ 2]   53 	addw	sp, #4
      0080C6 1C 50 00         [ 2]   54 	addw	x, #0x5000
      0080C9 1F 05            [ 2]   55 	ldw	(0x05, sp), x
                                     56 ;	../hal/gpio.c: 11: _setbit(gpio->ddr,pin);
      0080CB 1E 05            [ 2]   57 	ldw	x, (0x05, sp)
      0080CD 5C               [ 2]   58 	incw	x
      0080CE 5C               [ 2]   59 	incw	x
                                     60 ;	../hal/gpio.c: 13: _clrbit(gpio->ddr,pin);
      0080CF 7B 0F            [ 1]   61 	ld	a, (0x0f, sp)
      0080D1 43               [ 1]   62 	cpl	a
      0080D2 6B 09            [ 1]   63 	ld	(0x09, sp), a
                                     64 ;	../hal/gpio.c: 10: if (mode&4){
      0080D4 7B 11            [ 1]   65 	ld	a, (0x11, sp)
      0080D6 A5 04            [ 1]   66 	bcp	a, #0x04
      0080D8 27 10            [ 1]   67 	jreq	00102$
                                     68 ;	../hal/gpio.c: 11: _setbit(gpio->ddr,pin);
      0080DA F6               [ 1]   69 	ld	a, (x)
      0080DB 0F 07            [ 1]   70 	clr	(0x07, sp)
      0080DD 1A 0F            [ 1]   71 	or	a, (0x0f, sp)
      0080DF 90 95            [ 1]   72 	ld	yh, a
      0080E1 7B 07            [ 1]   73 	ld	a, (0x07, sp)
      0080E3 1A 0E            [ 1]   74 	or	a, (0x0e, sp)
      0080E5 90 9E            [ 1]   75 	ld	a, yh
      0080E7 F7               [ 1]   76 	ld	(x), a
      0080E8 20 04            [ 2]   77 	jra	00103$
      0080EA                         78 00102$:
                                     79 ;	../hal/gpio.c: 13: _clrbit(gpio->ddr,pin);
      0080EA F6               [ 1]   80 	ld	a, (x)
      0080EB 14 09            [ 1]   81 	and	a, (0x09, sp)
      0080ED F7               [ 1]   82 	ld	(x), a
      0080EE                         83 00103$:
                                     84 ;	../hal/gpio.c: 15: switch(mode){
      0080EE 0D 10            [ 1]   85 	tnz	(0x10, sp)
      0080F0 2A 03            [ 1]   86 	jrpl	00128$
      0080F2 CC 81 79         [ 2]   87 	jp	00113$
      0080F5                         88 00128$:
      0080F5 1E 10            [ 2]   89 	ldw	x, (0x10, sp)
      0080F7 A3 00 07         [ 2]   90 	cpw	x, #0x0007
      0080FA 2D 03            [ 1]   91 	jrsle	00129$
      0080FC CC 81 79         [ 2]   92 	jp	00113$
      0080FF                         93 00129$:
                                     94 ;	../hal/gpio.c: 18: _clrbit(gpio->cr1,pin);
      0080FF 16 05            [ 2]   95 	ldw	y, (0x05, sp)
      008101 72 A9 00 03      [ 2]   96 	addw	y, #0x0003
                                     97 ;	../hal/gpio.c: 19: _clrbit(gpio->cr2,pin);
      008105 1E 05            [ 2]   98 	ldw	x, (0x05, sp)
      008107 1C 00 04         [ 2]   99 	addw	x, #0x0004
      00810A 1F 03            [ 2]  100 	ldw	(0x03, sp), x
                                    101 ;	../hal/gpio.c: 15: switch(mode){
      00810C 1E 10            [ 2]  102 	ldw	x, (0x10, sp)
      00810E 58               [ 2]  103 	sllw	x
      00810F DE 81 13         [ 2]  104 	ldw	x, (#00130$, x)
      008112 FC               [ 2]  105 	jp	(x)
      008113                        106 00130$:
      008113 81 23                  107 	.dw	#00104$
      008115 81 49                  108 	.dw	#00108$
      008117 81 33                  109 	.dw	#00106$
      008119 81 5F                  110 	.dw	#00110$
      00811B 81 23                  111 	.dw	#00105$
      00811D 81 49                  112 	.dw	#00109$
      00811F 81 33                  113 	.dw	#00107$
      008121 81 5F                  114 	.dw	#00111$
                                    115 ;	../hal/gpio.c: 16: case INPUT_FLOAT_DI:
      008123                        116 00104$:
                                    117 ;	../hal/gpio.c: 17: case OUTPUT_OD_SLOW:
      008123                        118 00105$:
                                    119 ;	../hal/gpio.c: 18: _clrbit(gpio->cr1,pin);
      008123 90 F6            [ 1]  120 	ld	a, (y)
      008125 14 09            [ 1]  121 	and	a, (0x09, sp)
      008127 90 F7            [ 1]  122 	ld	(y), a
                                    123 ;	../hal/gpio.c: 19: _clrbit(gpio->cr2,pin);
      008129 1E 03            [ 2]  124 	ldw	x, (0x03, sp)
      00812B F6               [ 1]  125 	ld	a, (x)
      00812C 14 09            [ 1]  126 	and	a, (0x09, sp)
      00812E 1E 03            [ 2]  127 	ldw	x, (0x03, sp)
      008130 F7               [ 1]  128 	ld	(x), a
                                    129 ;	../hal/gpio.c: 20: break;
      008131 20 46            [ 2]  130 	jra	00113$
                                    131 ;	../hal/gpio.c: 21: case INPUT_FLOAT_EI:
      008133                        132 00106$:
                                    133 ;	../hal/gpio.c: 22: case OUTPUT_OD_FAST:
      008133                        134 00107$:
                                    135 ;	../hal/gpio.c: 23: _clrbit(gpio->cr1,pin);
      008133 90 F6            [ 1]  136 	ld	a, (y)
      008135 14 09            [ 1]  137 	and	a, (0x09, sp)
      008137 90 F7            [ 1]  138 	ld	(y), a
                                    139 ;	../hal/gpio.c: 24: _setbit(gpio->cr2,pin);
      008139 1E 03            [ 2]  140 	ldw	x, (0x03, sp)
      00813B F6               [ 1]  141 	ld	a, (x)
      00813C 95               [ 1]  142 	ld	xh, a
      00813D 4F               [ 1]  143 	clr	a
      00813E 1A 0E            [ 1]  144 	or	a, (0x0e, sp)
      008140 02               [ 1]  145 	rlwa	x
      008141 1A 0F            [ 1]  146 	or	a, (0x0f, sp)
      008143 95               [ 1]  147 	ld	xh, a
      008144 1E 03            [ 2]  148 	ldw	x, (0x03, sp)
      008146 F7               [ 1]  149 	ld	(x), a
                                    150 ;	../hal/gpio.c: 25: break;
      008147 20 30            [ 2]  151 	jra	00113$
                                    152 ;	../hal/gpio.c: 26: case INPUT_PU_DI:
      008149                        153 00108$:
                                    154 ;	../hal/gpio.c: 27: case OUTPUT_PP_SLOW:
      008149                        155 00109$:
                                    156 ;	../hal/gpio.c: 28: _setbit(gpio->cr1,pin);
      008149 90 F6            [ 1]  157 	ld	a, (y)
      00814B 95               [ 1]  158 	ld	xh, a
      00814C 4F               [ 1]  159 	clr	a
      00814D 1A 0E            [ 1]  160 	or	a, (0x0e, sp)
      00814F 02               [ 1]  161 	rlwa	x
      008150 1A 0F            [ 1]  162 	or	a, (0x0f, sp)
      008152 95               [ 1]  163 	ld	xh, a
      008153 90 F7            [ 1]  164 	ld	(y), a
                                    165 ;	../hal/gpio.c: 29: _clrbit(gpio->cr2,pin);
      008155 1E 03            [ 2]  166 	ldw	x, (0x03, sp)
      008157 F6               [ 1]  167 	ld	a, (x)
      008158 14 09            [ 1]  168 	and	a, (0x09, sp)
      00815A 1E 03            [ 2]  169 	ldw	x, (0x03, sp)
      00815C F7               [ 1]  170 	ld	(x), a
                                    171 ;	../hal/gpio.c: 30: break;
      00815D 20 1A            [ 2]  172 	jra	00113$
                                    173 ;	../hal/gpio.c: 31: case INPUT_PU_EI:
      00815F                        174 00110$:
                                    175 ;	../hal/gpio.c: 32: case OUTPUT_PP_FAST:
      00815F                        176 00111$:
                                    177 ;	../hal/gpio.c: 33: _setbit(gpio->cr1,pin);
      00815F 90 F6            [ 1]  178 	ld	a, (y)
      008161 95               [ 1]  179 	ld	xh, a
      008162 4F               [ 1]  180 	clr	a
      008163 1A 0E            [ 1]  181 	or	a, (0x0e, sp)
      008165 02               [ 1]  182 	rlwa	x
      008166 1A 0F            [ 1]  183 	or	a, (0x0f, sp)
      008168 95               [ 1]  184 	ld	xh, a
      008169 90 F7            [ 1]  185 	ld	(y), a
                                    186 ;	../hal/gpio.c: 34: _setbit(gpio->cr2,pin);
      00816B 1E 03            [ 2]  187 	ldw	x, (0x03, sp)
      00816D F6               [ 1]  188 	ld	a, (x)
      00816E 95               [ 1]  189 	ld	xh, a
      00816F 4F               [ 1]  190 	clr	a
      008170 1A 0E            [ 1]  191 	or	a, (0x0e, sp)
      008172 02               [ 1]  192 	rlwa	x
      008173 1A 0F            [ 1]  193 	or	a, (0x0f, sp)
      008175 95               [ 1]  194 	ld	xh, a
      008176 1E 03            [ 2]  195 	ldw	x, (0x03, sp)
      008178 F7               [ 1]  196 	ld	(x), a
                                    197 ;	../hal/gpio.c: 36: }
      008179                        198 00113$:
      008179 5B 09            [ 2]  199 	addw	sp, #9
      00817B 81               [ 4]  200 	ret
                                    201 	.area CODE
                                    202 	.area INITIALIZER
                                    203 	.area CABS (ABS)
