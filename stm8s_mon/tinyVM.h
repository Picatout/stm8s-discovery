/*
 * tiny stack machine
*/


typedef enum OPCODE{
	NOP,
	SUB,
	ADD,
	MUL,
	DIV,
	MOD,
	NEG,
	INV,
	AND,
	OR,
	XOR,
	ADD1,
	SUB1,
	DUP,
	OVER,
	DROP,
	TOR,
	RFROM,
	A,
	STORA,
	STORB,
	ASTOR,
	STORPLUS,
	BSTOR,
	FETCHA,
	FETCHAPLUS,
	FETCHB,
	NIP,
	SWAP,
	CALL,
	RET,
	NEXT,
}opcode_t;

typedef enum XOPCODE{
	JRA,
}xopcode_t;
