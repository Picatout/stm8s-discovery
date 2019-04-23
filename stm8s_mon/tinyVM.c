/*
 * A tiny stack machine inspired from Green Arrays F18A
 * 
 * 2 stacks  data and return
 * 2 pointers  a et b    b is a byte pointer.   
 * Instructions coded on byte.
 *  code forms:
 *  form 0  (bit 7==0)  ( implicit operands, or target address if condition code)
 * 		bits 4:0  32 opcodes 
 * 			opcode |  mnemonic | description
 *             0   |    'nop'    |   nop
 *             1   |     '-'     |  T = N-T
 *             2   |     '+'     |  T = N+T
 *             3   |     '*'     |  T = N*T
 *             4   |     '/'     |  T = N/T
 *             5   |     '%'     |  T = N%T
 *             6   |    'neg'    |  T = NEG  (two's complement)
 *             7   |    'inv'    |  T = INVERT (one's complement)
 *             8   |     '&'     |  T = N & T
 *             9   |     '|'     |  T = N | T
 *             10  |     '^'     |  T = N ^ T
 *             11  |     '1+'    |  T = T+1
 *             12  |     '1-'    |  T = T-1
 *             13  |    'dup'    |  n -- n n
 *             14  |    'over'   |  n1 n2 --  n1 n2 n1
 *             15  |    'drop'   |  n --
 *             16  |     '>r'    |  n --  R: -- n
 *             17  |     'r>'    |  -- n R: n --
 *             18  |     'a'     |  -- a   fetch a in T
 *             19  |     '!a'    |  n --   a <- n   pop T in  a
 *             20  |     '!b'    |  n --   b <- n   pop T in  b
 *             21  |     'a!'    |  n --   mem[a] <- n
 *             22  |     '!+'    |  n --   mem[a++] <- n
 *             23  |     'b!'    |  u8 --   mem[b]<- u8
 *             24  |     '@a'    |  -- n   T <- mem[a]
 *             25  |     '@a+'   |  -- n   T <- mem[a++]
 *             26  |     '@b'    |  -- u8  T <- mem[b]
 *             27  |     'nip'   |  n1 n2 --  n2
 *             28  |     'swap'  |  n1 n2 --  n2 n1
 *             29  |     'call'  |  swap   r and pc
 *             30  |     ';'     |  pop r in pc
 *             31  |     'next'  |  decrement R, if R loop to address, else drop R exit loop
 *      bits 7:5  condition code
 *             0b000   no condition code
 *             0b001   jump if T>0 , drop T,  pc <- target address
 *             0b010   jump if T<0 , drop T,  pc <- target address
 *             0b011   jump if T==0,  drop T,  pc <- target address
 *
 *  form 1  (bit 7==1, 1 operand)
 *       bits 7:5  |  mnemonic    |   description
 *          0b100     |   'jra'      |   unconditionnal jump to 13 bits relative address
 *          0b101     |   'lit5'     |   -- n   T <- 5 bits literal
 *          0b110     |   'lit13'    |   -- n   T <- 13 bits literal
 *          0b111     |   subcode    |   extended code form 2
 * 
 *  form 2  (bits 7:5==111) extended code
 * 			bits 4:0  |  mnemonic |   description
 *              0     |   'lit16' |  -- n  16 bits literal follow opcode
 *              1     |
 *              2     |
 *              3     |
 *              4     |
 *              5     |
 *              6     |
 *              7     |
 *              8     |
 *              9     |
 *              10    |
 *              11    |
 *              12    |
 *              13    |
 *              14    |
 *              15    | 
 *            0b1xxxx |   'pick'  |   xn .. x0 --  xn .. x0 xn,  push nth element xxxx -> {0..15}
 *              
 */
 
 
 #define ASTK_SIZE (16)
 #define RSTK_SIZE (16)
 static int16_t  astack[ASTK_SIZE];
 static uint16_t rstack[RSTK_SIZE];
 static int8_t asp;
 static int8_t rsp;
 static uint16_t pc;
 static uint16_t a,b;
 
 
 /*
  *  input:
  *  	code  -> bytecode buffer
  *     size  -> buffer size (tvm exit when pc>=size)
  *     reset -> reset tvm state if true
  *  output:
  *     number of items on asp at exit. 
 */
 int8_t tvm(uint16_t *code, uint16_t size, int8_t reset){
		uint8_t bc; // bytecode
		if (reset){
			asp=-1;
			rsp=-1;
		}
		pc=0;
		while ((pc>=0) && (pc<size)){
			bc=code[pc++];
			if (!(bc &0x80)){ 
				switch(bc&0x1f){ // form 0
				}//std code switch
				if (bc&0x60){ // condition code.
					bc>>=5;
					switch(bc){
					}// CC switch
				}
			}else{ // form1 and form 2
				switch ((bc&0x60)>>5){
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}//switch ((bc&0xe0)>>5)
			}
		}//while
 }
 
  
