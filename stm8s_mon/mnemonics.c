/*
 *  STM8 mnemonics and code.
 *  code forms ref: https://en.wikipedia.org/wiki/STM8#Instruction_set
*/

#include "../inc/discovery.h"
#include "mnemonics.h"

// instructions mnemonics used by assemblr
static const char* inst_mnemo[]={
	"ADC",
	"ADD",
	"ADDW",
	"AND",
	"BCCM",
	"BCP",
	"BCPL",
	"BREAK",
	"BRES",
	"BSET",
	"BTJF",
	"BTJT",
	"CALL",
	"CALLF",
	"CALLR",
	"CCF",
	"CLR",
	"CLRW",
	"CP",
	"CPW",
	"CPL",
	"CPLW",
	"DEC",
	"DECW",
	"DIV",
	"DIVW",
	"EXG",
	"EXGW",
	"HALT",
	"INC",
	"INCW",
	"INT",
	"IRET",
	"JP",
	"JRA",
	"JPF",
    "JRC",
    "JREQ",
    "JRF",
    "JRH",
    "JRIH",
    "JRIL",
    "JRM",
    "JRMI",
    "JRNC",
    "JRNE",
    "JRNH",
    "JRNM",
    "JRNV",
    "JRPL",
    "JRSGE",
    "JRSGT",
    "JRSLE",
    "JRSLT",
    "JRT",
    "JRUGE",
    "JRUGT",
    "JRULE",
    "JRULT",
    "JRV",    
	"LD",
	"LDF",
	"LDW",
	"MOV",
	"MUL",
	"NEG",
	"NEGW",
	"NOP",
	"OR",
	"POP",
	"POPW",
	"PUSH",
	"PUSHW",
	"RCF",
	"RET",
	"RETF",
	"RIM",
	"RLC",
	"RLCW",
	"RLWA",
	"RRC",
	"RRCW",
	"RRWA",
	"RVF",
	"SBC",
	"SCF",
	"SIM",
	"SLA",
	"SLAW",
	"SLL",
	"SLLW",
	"SRA",
	"SRAW",
	"SRL",
	"SRLW",
	"SUB",
	"SUBW",
	"SWAP",
	"SWAPW",
	"TNZ",
	"TNZW",
	"TRAP",
	"WFE",
	"WFI",
	"XOR",
	0
};




int8_t search_mnemo(const char *str){
	uint8_t u=0;
	while (inst_mnemo[u]){
		if (!strcmp(str,inst_mnemo[u])) return u;
		u++;
	}
	return -1;
}

