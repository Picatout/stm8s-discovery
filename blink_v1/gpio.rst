                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.5.0 #9253 (Apr  3 2018) (Linux)
                                      4 ; This file was generated Thu Apr  4 23:14:22 2019
                                      5 ;--------------------------------------------------------
                                      6 	.module gpio
                                      7 	.optsdcc -mstm8
                                      8 	
                                      9 ;--------------------------------------------------------
                                     10 ; Public variables in this module
                                     11 ;--------------------------------------------------------
                                     12 	.globl _set_pin_input
                                     13 	.globl _set_pin_output
                                     14 ;--------------------------------------------------------
                                     15 ; ram data
                                     16 ;--------------------------------------------------------
                                     17 	.area DATA
                                     18 ;--------------------------------------------------------
                                     19 ; ram data
                                     20 ;--------------------------------------------------------
                                     21 	.area INITIALIZED
                                     22 ;--------------------------------------------------------
                                     23 ; absolute external ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area DABS (ABS)
                                     26 ;--------------------------------------------------------
                                     27 ; global & static initialisations
                                     28 ;--------------------------------------------------------
                                     29 	.area HOME
                                     30 	.area GSINIT
                                     31 	.area GSFINAL
                                     32 	.area GSINIT
                                     33 ;--------------------------------------------------------
                                     34 ; Home
                                     35 ;--------------------------------------------------------
                                     36 	.area HOME
                                     37 	.area HOME
                                     38 ;--------------------------------------------------------
                                     39 ; code
                                     40 ;--------------------------------------------------------
                                     41 	.area CODE
                                     42 ;	../hal/gpio.c: 8: void set_pin_output(int port,int pin, int mode){
                                     43 ;	-----------------------------------------
                                     44 ;	 function set_pin_output
                                     45 ;	-----------------------------------------
      0080B7                         46 _set_pin_output:
      0080B7 52 09            [ 2]   47 	sub	sp, #9
                                     48 ;	../hal/gpio.c: 10: gpio[port].ddr|=pin;
      0080B9 1E 0C            [ 2]   49 	ldw	x, (0x0c, sp)
      0080BB 89               [ 2]   50 	pushw	x
      0080BC 4B 05            [ 1]   51 	push	#0x05
      0080BE 4B 00            [ 1]   52 	push	#0x00
      0080C0 CD 82 65         [ 4]   53 	call	__mulint
      0080C3 5B 04            [ 2]   54 	addw	sp, #4
      0080C5 1C 50 00         [ 2]   55 	addw	x, #0x5000
      0080C8 1F 05            [ 2]   56 	ldw	(0x05, sp), x
      0080CA 1E 05            [ 2]   57 	ldw	x, (0x05, sp)
      0080CC 5C               [ 2]   58 	incw	x
      0080CD 5C               [ 2]   59 	incw	x
      0080CE F6               [ 1]   60 	ld	a, (x)
      0080CF 0F 03            [ 1]   61 	clr	(0x03, sp)
      0080D1 1A 0F            [ 1]   62 	or	a, (0x0f, sp)
      0080D3 90 95            [ 1]   63 	ld	yh, a
      0080D5 7B 03            [ 1]   64 	ld	a, (0x03, sp)
      0080D7 1A 0E            [ 1]   65 	or	a, (0x0e, sp)
      0080D9 90 9E            [ 1]   66 	ld	a, yh
      0080DB F7               [ 1]   67 	ld	(x), a
                                     68 ;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
      0080DC 1E 05            [ 2]   69 	ldw	x, (0x05, sp)
      0080DE 1C 00 03         [ 2]   70 	addw	x, #0x0003
      0080E1 1F 01            [ 2]   71 	ldw	(0x01, sp), x
      0080E3 7B 0F            [ 1]   72 	ld	a, (0x0f, sp)
                                     73 ;	../hal/gpio.c: 14: gpio[port].cr2&=~pin;
      0080E5 1E 05            [ 2]   74 	ldw	x, (0x05, sp)
      0080E7 1C 00 04         [ 2]   75 	addw	x, #0x0004
      0080EA 1F 08            [ 2]   76 	ldw	(0x08, sp), x
                                     77 ;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
      0080EC 43               [ 1]   78 	cpl	a
      0080ED 6B 07            [ 1]   79 	ld	(0x07, sp), a
                                     80 ;	../hal/gpio.c: 11: switch(mode){
      0080EF 1E 10            [ 2]   81 	ldw	x, (0x10, sp)
      0080F1 A3 00 00         [ 2]   82 	cpw	x, #0x0000
      0080F4 27 17            [ 1]   83 	jreq	00101$
      0080F6 1E 10            [ 2]   84 	ldw	x, (0x10, sp)
      0080F8 A3 00 01         [ 2]   85 	cpw	x, #0x0001
      0080FB 27 3A            [ 1]   86 	jreq	00103$
      0080FD 1E 10            [ 2]   87 	ldw	x, (0x10, sp)
      0080FF A3 00 02         [ 2]   88 	cpw	x, #0x0002
      008102 27 1B            [ 1]   89 	jreq	00102$
      008104 1E 10            [ 2]   90 	ldw	x, (0x10, sp)
      008106 A3 00 03         [ 2]   91 	cpw	x, #0x0003
      008109 27 44            [ 1]   92 	jreq	00104$
      00810B 20 5E            [ 2]   93 	jra	00106$
                                     94 ;	../hal/gpio.c: 12: case OUTPUT_OD_SLOW:
      00810D                         95 00101$:
                                     96 ;	../hal/gpio.c: 13: gpio[port].cr1&=~pin;
      00810D 1E 01            [ 2]   97 	ldw	x, (0x01, sp)
      00810F F6               [ 1]   98 	ld	a, (x)
      008110 14 07            [ 1]   99 	and	a, (0x07, sp)
      008112 1E 01            [ 2]  100 	ldw	x, (0x01, sp)
      008114 F7               [ 1]  101 	ld	(x), a
                                    102 ;	../hal/gpio.c: 14: gpio[port].cr2&=~pin;
      008115 1E 08            [ 2]  103 	ldw	x, (0x08, sp)
      008117 F6               [ 1]  104 	ld	a, (x)
      008118 14 07            [ 1]  105 	and	a, (0x07, sp)
      00811A 1E 08            [ 2]  106 	ldw	x, (0x08, sp)
      00811C F7               [ 1]  107 	ld	(x), a
                                    108 ;	../hal/gpio.c: 15: break;
      00811D 20 4C            [ 2]  109 	jra	00106$
                                    110 ;	../hal/gpio.c: 16: case OUTPUT_OD_FAST:
      00811F                        111 00102$:
                                    112 ;	../hal/gpio.c: 17: gpio[port].cr1&=~pin;
      00811F 1E 01            [ 2]  113 	ldw	x, (0x01, sp)
      008121 F6               [ 1]  114 	ld	a, (x)
      008122 14 07            [ 1]  115 	and	a, (0x07, sp)
      008124 1E 01            [ 2]  116 	ldw	x, (0x01, sp)
      008126 F7               [ 1]  117 	ld	(x), a
                                    118 ;	../hal/gpio.c: 18: gpio[port].cr2|=pin;
      008127 1E 08            [ 2]  119 	ldw	x, (0x08, sp)
      008129 F6               [ 1]  120 	ld	a, (x)
      00812A 95               [ 1]  121 	ld	xh, a
      00812B 4F               [ 1]  122 	clr	a
      00812C 1A 0E            [ 1]  123 	or	a, (0x0e, sp)
      00812E 02               [ 1]  124 	rlwa	x
      00812F 1A 0F            [ 1]  125 	or	a, (0x0f, sp)
      008131 95               [ 1]  126 	ld	xh, a
      008132 1E 08            [ 2]  127 	ldw	x, (0x08, sp)
      008134 F7               [ 1]  128 	ld	(x), a
                                    129 ;	../hal/gpio.c: 19: break;
      008135 20 34            [ 2]  130 	jra	00106$
                                    131 ;	../hal/gpio.c: 20: case OUTPUT_PP_SLOW:
      008137                        132 00103$:
                                    133 ;	../hal/gpio.c: 21: gpio[port].cr1|=pin;
      008137 1E 01            [ 2]  134 	ldw	x, (0x01, sp)
      008139 F6               [ 1]  135 	ld	a, (x)
      00813A 95               [ 1]  136 	ld	xh, a
      00813B 4F               [ 1]  137 	clr	a
      00813C 1A 0E            [ 1]  138 	or	a, (0x0e, sp)
      00813E 02               [ 1]  139 	rlwa	x
      00813F 1A 0F            [ 1]  140 	or	a, (0x0f, sp)
      008141 95               [ 1]  141 	ld	xh, a
      008142 1E 01            [ 2]  142 	ldw	x, (0x01, sp)
      008144 F7               [ 1]  143 	ld	(x), a
                                    144 ;	../hal/gpio.c: 22: gpio[port].cr2&=~pin;
      008145 1E 08            [ 2]  145 	ldw	x, (0x08, sp)
      008147 F6               [ 1]  146 	ld	a, (x)
      008148 14 07            [ 1]  147 	and	a, (0x07, sp)
      00814A 1E 08            [ 2]  148 	ldw	x, (0x08, sp)
      00814C F7               [ 1]  149 	ld	(x), a
                                    150 ;	../hal/gpio.c: 23: break;
      00814D 20 1C            [ 2]  151 	jra	00106$
                                    152 ;	../hal/gpio.c: 24: case OUTPUT_PP_FAST:
      00814F                        153 00104$:
                                    154 ;	../hal/gpio.c: 25: gpio[port].cr1|=pin;
      00814F 1E 01            [ 2]  155 	ldw	x, (0x01, sp)
      008151 F6               [ 1]  156 	ld	a, (x)
      008152 95               [ 1]  157 	ld	xh, a
      008153 4F               [ 1]  158 	clr	a
      008154 1A 0E            [ 1]  159 	or	a, (0x0e, sp)
      008156 02               [ 1]  160 	rlwa	x
      008157 1A 0F            [ 1]  161 	or	a, (0x0f, sp)
      008159 95               [ 1]  162 	ld	xh, a
      00815A 1E 01            [ 2]  163 	ldw	x, (0x01, sp)
      00815C F7               [ 1]  164 	ld	(x), a
                                    165 ;	../hal/gpio.c: 26: gpio[port].cr2|=pin;
      00815D 1E 08            [ 2]  166 	ldw	x, (0x08, sp)
      00815F F6               [ 1]  167 	ld	a, (x)
      008160 95               [ 1]  168 	ld	xh, a
      008161 4F               [ 1]  169 	clr	a
      008162 1A 0E            [ 1]  170 	or	a, (0x0e, sp)
      008164 02               [ 1]  171 	rlwa	x
      008165 1A 0F            [ 1]  172 	or	a, (0x0f, sp)
      008167 95               [ 1]  173 	ld	xh, a
      008168 1E 08            [ 2]  174 	ldw	x, (0x08, sp)
      00816A F7               [ 1]  175 	ld	(x), a
                                    176 ;	../hal/gpio.c: 28: }
      00816B                        177 00106$:
      00816B 5B 09            [ 2]  178 	addw	sp, #9
      00816D 81               [ 4]  179 	ret
                                    180 ;	../hal/gpio.c: 31: void set_pin_input(int port,int pin,int mode){
                                    181 ;	-----------------------------------------
                                    182 ;	 function set_pin_input
                                    183 ;	-----------------------------------------
      00816E                        184 _set_pin_input:
      00816E 52 07            [ 2]  185 	sub	sp, #7
                                    186 ;	../hal/gpio.c: 33: gpio[port].cr1&=~pin;
      008170 1E 0A            [ 2]  187 	ldw	x, (0x0a, sp)
      008172 89               [ 2]  188 	pushw	x
      008173 4B 05            [ 1]  189 	push	#0x05
      008175 4B 00            [ 1]  190 	push	#0x00
      008177 CD 82 65         [ 4]  191 	call	__mulint
      00817A 5B 04            [ 2]  192 	addw	sp, #4
      00817C 1C 50 00         [ 2]  193 	addw	x, #0x5000
      00817F 1F 04            [ 2]  194 	ldw	(0x04, sp), x
      008181 1E 04            [ 2]  195 	ldw	x, (0x04, sp)
      008183 1C 00 03         [ 2]  196 	addw	x, #0x0003
      008186 1F 01            [ 2]  197 	ldw	(0x01, sp), x
      008188 1E 01            [ 2]  198 	ldw	x, (0x01, sp)
      00818A F6               [ 1]  199 	ld	a, (x)
      00818B 95               [ 1]  200 	ld	xh, a
      00818C 7B 0D            [ 1]  201 	ld	a, (0x0d, sp)
      00818E 43               [ 1]  202 	cpl	a
      00818F 6B 03            [ 1]  203 	ld	(0x03, sp), a
      008191 9E               [ 1]  204 	ld	a, xh
      008192 14 03            [ 1]  205 	and	a, (0x03, sp)
      008194 1E 01            [ 2]  206 	ldw	x, (0x01, sp)
      008196 F7               [ 1]  207 	ld	(x), a
                                    208 ;	../hal/gpio.c: 37: gpio[port].cr2&=~pin;
      008197 1E 04            [ 2]  209 	ldw	x, (0x04, sp)
      008199 1C 00 04         [ 2]  210 	addw	x, #0x0004
      00819C 1F 06            [ 2]  211 	ldw	(0x06, sp), x
                                    212 ;	../hal/gpio.c: 34: switch(mode){
      00819E 1E 0E            [ 2]  213 	ldw	x, (0x0e, sp)
      0081A0 A3 00 00         [ 2]  214 	cpw	x, #0x0000
      0081A3 27 17            [ 1]  215 	jreq	00101$
      0081A5 1E 0E            [ 2]  216 	ldw	x, (0x0e, sp)
      0081A7 A3 00 01         [ 2]  217 	cpw	x, #0x0001
      0081AA 27 3A            [ 1]  218 	jreq	00103$
      0081AC 1E 0E            [ 2]  219 	ldw	x, (0x0e, sp)
      0081AE A3 00 02         [ 2]  220 	cpw	x, #0x0002
      0081B1 27 1B            [ 1]  221 	jreq	00102$
      0081B3 1E 0E            [ 2]  222 	ldw	x, (0x0e, sp)
      0081B5 A3 00 03         [ 2]  223 	cpw	x, #0x0003
      0081B8 27 44            [ 1]  224 	jreq	00104$
      0081BA 20 5E            [ 2]  225 	jra	00106$
                                    226 ;	../hal/gpio.c: 35: case INPUT_FLOAT_DI:
      0081BC                        227 00101$:
                                    228 ;	../hal/gpio.c: 36: gpio[port].cr1&=~pin;
      0081BC 1E 01            [ 2]  229 	ldw	x, (0x01, sp)
      0081BE F6               [ 1]  230 	ld	a, (x)
      0081BF 14 03            [ 1]  231 	and	a, (0x03, sp)
      0081C1 1E 01            [ 2]  232 	ldw	x, (0x01, sp)
      0081C3 F7               [ 1]  233 	ld	(x), a
                                    234 ;	../hal/gpio.c: 37: gpio[port].cr2&=~pin;
      0081C4 1E 06            [ 2]  235 	ldw	x, (0x06, sp)
      0081C6 F6               [ 1]  236 	ld	a, (x)
      0081C7 14 03            [ 1]  237 	and	a, (0x03, sp)
      0081C9 1E 06            [ 2]  238 	ldw	x, (0x06, sp)
      0081CB F7               [ 1]  239 	ld	(x), a
                                    240 ;	../hal/gpio.c: 38: break;
      0081CC 20 4C            [ 2]  241 	jra	00106$
                                    242 ;	../hal/gpio.c: 39: case INPUT_FLOAT_EI:
      0081CE                        243 00102$:
                                    244 ;	../hal/gpio.c: 40: gpio[port].cr1&=~pin;
      0081CE 1E 01            [ 2]  245 	ldw	x, (0x01, sp)
      0081D0 F6               [ 1]  246 	ld	a, (x)
      0081D1 14 03            [ 1]  247 	and	a, (0x03, sp)
      0081D3 1E 01            [ 2]  248 	ldw	x, (0x01, sp)
      0081D5 F7               [ 1]  249 	ld	(x), a
                                    250 ;	../hal/gpio.c: 41: gpio[port].cr2|=pin;
      0081D6 1E 06            [ 2]  251 	ldw	x, (0x06, sp)
      0081D8 F6               [ 1]  252 	ld	a, (x)
      0081D9 95               [ 1]  253 	ld	xh, a
      0081DA 4F               [ 1]  254 	clr	a
      0081DB 1A 0C            [ 1]  255 	or	a, (0x0c, sp)
      0081DD 02               [ 1]  256 	rlwa	x
      0081DE 1A 0D            [ 1]  257 	or	a, (0x0d, sp)
      0081E0 95               [ 1]  258 	ld	xh, a
      0081E1 1E 06            [ 2]  259 	ldw	x, (0x06, sp)
      0081E3 F7               [ 1]  260 	ld	(x), a
                                    261 ;	../hal/gpio.c: 42: break;
      0081E4 20 34            [ 2]  262 	jra	00106$
                                    263 ;	../hal/gpio.c: 43: case INPUT_PU_DI:
      0081E6                        264 00103$:
                                    265 ;	../hal/gpio.c: 44: gpio[port].cr1|=pin;
      0081E6 1E 01            [ 2]  266 	ldw	x, (0x01, sp)
      0081E8 F6               [ 1]  267 	ld	a, (x)
      0081E9 95               [ 1]  268 	ld	xh, a
      0081EA 4F               [ 1]  269 	clr	a
      0081EB 1A 0C            [ 1]  270 	or	a, (0x0c, sp)
      0081ED 02               [ 1]  271 	rlwa	x
      0081EE 1A 0D            [ 1]  272 	or	a, (0x0d, sp)
      0081F0 95               [ 1]  273 	ld	xh, a
      0081F1 1E 01            [ 2]  274 	ldw	x, (0x01, sp)
      0081F3 F7               [ 1]  275 	ld	(x), a
                                    276 ;	../hal/gpio.c: 45: gpio[port].cr2&=~pin;
      0081F4 1E 06            [ 2]  277 	ldw	x, (0x06, sp)
      0081F6 F6               [ 1]  278 	ld	a, (x)
      0081F7 14 03            [ 1]  279 	and	a, (0x03, sp)
      0081F9 1E 06            [ 2]  280 	ldw	x, (0x06, sp)
      0081FB F7               [ 1]  281 	ld	(x), a
                                    282 ;	../hal/gpio.c: 46: break;
      0081FC 20 1C            [ 2]  283 	jra	00106$
                                    284 ;	../hal/gpio.c: 47: case INPUT_PU_EI:
      0081FE                        285 00104$:
                                    286 ;	../hal/gpio.c: 48: gpio[port].cr1|=pin;
      0081FE 1E 01            [ 2]  287 	ldw	x, (0x01, sp)
      008200 F6               [ 1]  288 	ld	a, (x)
      008201 95               [ 1]  289 	ld	xh, a
      008202 4F               [ 1]  290 	clr	a
      008203 1A 0C            [ 1]  291 	or	a, (0x0c, sp)
      008205 02               [ 1]  292 	rlwa	x
      008206 1A 0D            [ 1]  293 	or	a, (0x0d, sp)
      008208 95               [ 1]  294 	ld	xh, a
      008209 1E 01            [ 2]  295 	ldw	x, (0x01, sp)
      00820B F7               [ 1]  296 	ld	(x), a
                                    297 ;	../hal/gpio.c: 49: gpio[port].cr2|=pin;
      00820C 1E 06            [ 2]  298 	ldw	x, (0x06, sp)
      00820E F6               [ 1]  299 	ld	a, (x)
      00820F 95               [ 1]  300 	ld	xh, a
      008210 4F               [ 1]  301 	clr	a
      008211 1A 0C            [ 1]  302 	or	a, (0x0c, sp)
      008213 02               [ 1]  303 	rlwa	x
      008214 1A 0D            [ 1]  304 	or	a, (0x0d, sp)
      008216 95               [ 1]  305 	ld	xh, a
      008217 1E 06            [ 2]  306 	ldw	x, (0x06, sp)
      008219 F7               [ 1]  307 	ld	(x), a
                                    308 ;	../hal/gpio.c: 51: }
      00821A                        309 00106$:
      00821A 5B 07            [ 2]  310 	addw	sp, #7
      00821C 81               [ 4]  311 	ret
                                    312 	.area CODE
                                    313 	.area INITIALIZER
                                    314 	.area CABS (ABS)
