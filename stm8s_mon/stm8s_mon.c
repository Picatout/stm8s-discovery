/*
*  stm8s monitor program
*  syntax:
*    command  arg_list
*   
*  commands:
*    @ addr   -> display content at addr
*    ! addr value  ->  store value at address
*    : addr  val_list ->  store a list of values starting at addr. 
*    a addr -> enter assembler mode with addr as origin
*    c addr mask  -> clear bits using &~mask
*    d addr -> disassemble code from address
*    h addr  -> memory dump in hexadecimal
*    s addr mask  -> set bits using |mask
*    t addr mask  -> toggle bits using ^mask
*    x addr  -> execute code at addr. Code must use a 'ret' instruction to return to monitor.
*  arg_list :=  arg[' 'arg]*
*  arg := addr|value|mask
*  addr := hex_number|dec_number   range {0..65535}
*  value := hex_number|dec_number  range {0..255}
*  mask := hex_number|dec_number   range {0..255}
*  hex_number := $hex_digit+
*  dec_number := dec_digit+
*  dec_digit := '0'..'9'
*  hex_digit := dec_digit 'a'..'f'
* 
*  ASCII 32  (space) is the only separator between tokens.
*/

#include <setjmp.h>
#include "../inc/ascii.h"
#include "../inc/discovery.h"


#define TIB_SIZE 80
#define PAD_SIZE 80
static signed char tib[TIB_SIZE];
static signed char pad[PAD_SIZE];
static uint8_t count;
static uint8_t in;
static uint8_t first;
#define DATA_SIZE 1024
__at(RAM_BASE+1024) static uint8_t ram_code[DATA_SIZE];
static uint8_t here=0;
static jmp_buf env;

// write data eeprom or option
static int write_eeprom_byte(uint8_t *addr, uint8_t value){
	uint8_t fOption=(((uint16_t)addr & 0xff00)==OPTION_BASE);
	
	    /* unlock EEPROM write*/
    FLASH_DUKR = FLASH_DUKR_KEY1;
    FLASH_DUKR = FLASH_DUKR_KEY2;
    if (fOption){
		/* unlock option bytes */
		FLASH_CR2 |= FLASH_CR2_OPT;
		FLASH_NCR2 &= FLASH_NCR2_NOPT;
	}
    if (!(FLASH_IAPSR & FLASH_IAPSR_DUL)){
		return 0;
	}
	nointerrupts();
    *addr++=value;
    if (fOption){ *addr=~value;}
    /* wait until programming is finished */
    while (!(FLASH_IAPSR & FLASH_IAPSR_EOP));
    /* lock EEPROM */
    FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
	interrupts();
	return 1;
}

static int write_flash_byte(uint8_t* addr, uint8_t value){
	// unlock flash write
	FLASH_PUKR=FLASH_PUKR_KEY1;
	FLASH_PUKR=FLASH_PUKR_KEY2;
	if (!(FLASH_IAPSR & FLASH_IAPSR_PUL)){
		return 0;
	}
	nointerrupts();
	*addr=value;
    /* wait until programming is finished */
    while (!(FLASH_IAPSR & FLASH_IAPSR_EOP));
    /* lock flash */
    FLASH_IAPSR &= ~FLASH_IAPSR_PUL;
    interrupts();
    return 1;
}

//convert to hex string
// buf point to 0 terminator, 
static char* to_hex(char* buf, uint16_t number, uint8_t width){
	uint8_t d;

	while (width){
		d=number%16+'0';
		number/=16;
		if (d>'9')d+=7;
        *--buf=(char)d;
        width--;		
	}
	*--buf='$';
	return buf;
}

// copy from src to dest bc character
static void move(char *dest, const char* src,int8_t bc){
	while (bc>0){
		 *dest++=*src++;
		 bc--;
	 }
}

static const char error_msg[]="command error\n";

static const char prompt[]="READY\n";

static inline void print_prompt(){
	uprint(prompt);
}

static inline void print_error(){
	_ledon();
	uprint(error_msg);
}

// skip character c in tib
static void skip(signed char c){
	while (tib[in] && (tib[in]==c)){in++;}
}

// scan tib for first occurance of c
static void scan(signed char c){
	while(tib[in] && (tib[in]!=c)){in++;}
}

static void word(){
	skip(' ');
	first=in;  
	scan(' '); 
	move(pad,(const char*)&tib[first],in-first);
	pad[in-first]=0;
}

// try to convert pad content in number
// use default base if no prefix
uint16_t number(){
	uint8_t d,i=0, b=10;
	uint16_t u16=0;
	
	word();
	if (pad[i]=='$'){ b=16;i++;}
	while(pad[i]){
		d=(pad[i++]-'0')&0x1f;
		if (d>9) d-=7;
//		if (d>=b)longjmp(env,1);
		u16=u16*b+d;
	}
	return u16;
}


// print {address,value} pair
// format: hex(decimal) hex(decimal)
static void report(uint16_t addr, uint8_t value){
		char *str;
		pad[6]=0;
		str=to_hex(&pad[6],addr,4);
	    uprint(str);
	    uputc('(');
	    uprint_int(addr);
	    uprint(")=");
	    pad[4]=0;
	    str=to_hex(&pad[4],value,2);
	    uprint(str);
	    uputc('(');
	    uprint_int(value);
	    uprint(")\n");
}

static void cmd_peek(){
	uint16_t addr;
	uint8_t value;
	addr=number();
	value=*(uint8_t*)addr;
	report(addr,value);
}

static void write_value(uint8_t* addr, uint8_t value){
	uint8_t result=1;
	if (((uint16_t)addr>=EEPROM_BASE) && ((uint16_t)addr<=OPTION_END)){
		result=write_eeprom_byte(addr,value);
	}else if ((uint16_t)addr>=FLASH_BASE){
		result=write_flash_byte(addr,value);
	}else{
		*addr=value;
	}
	if (!result) uprint("write failed\n");
}


static void cmd_poke(){
	uint16_t addr;
	uint8_t value;
	addr=number();
	value=number();
	write_value((uint8_t*)addr,value);
	report(addr,value);
}

static void cmd_store(){
	uint16_t addr;
	uint8_t value;
	addr=number();
	do {
		skip(' ');
		value=number();
		report(addr,value);
		write_value((uint8_t*)addr,value);
		addr++;
	}while(in<count);
}

static void cmd_clear(){
	uint16_t addr;
	uint8_t mask;
	addr=number();
	mask=number();
	*(volatile uint8_t*)addr&=~mask;
}

static void dump_row(uint16_t addr){
	uint8_t u8,i=8;
	char *str;
	str=to_hex(&pad[8],addr,6);
	pad[8]=' ';
	pad[9]=' ';
	pad[10]=0;
	uprint(str);
	pad[9]=0;
	while (i){
		u8=*(uint8_t*)addr++;
		str=to_hex(&pad[8],u8,2);
		uprint(str);
		i--;
	}
	uputc('\n');
}

static void cmd_hdump(){
	uint16_t addr;
	signed char c;
	while (qchar()) ugetc();
	addr=number();
	do{
		dump_row(addr); // print 8 bytes.
		addr+=8;
		uputc('?');
		c=ugetc();
		delete_left(1);
	}while (c==SPACE);
}

static void cmd_set(){
	uint16_t addr;
	uint8_t mask;
	addr=number();
	mask=number();
	*(volatile uint8_t*)addr|=mask;
}

static void cmd_toggle(){
	uint16_t addr;
	uint8_t mask;
	addr=number();
	mask=number();
	*(volatile uint8_t*)addr^=mask;
}

typedef void (*fn)(void);
static void cmd_execute(){
	uint16_t xaddr;
	xaddr=number();
	((fn)xaddr)();
}

static void exec_cmd(){
	switch(pad[0]){
	case '@':
		cmd_peek();
		break;
	case '!':
		cmd_poke();
		break;
	case ':':
		cmd_store();
		break;
	case 'c':
		cmd_clear();
		break;
	case 'h':
		cmd_hdump();
		break;
	case 's':
		cmd_set();
		break;
	case 't':
	    cmd_toggle();
		break;
	case 'x':
		cmd_execute();
		break;
	default:
		print_error();
		break;
	}//switch
}


static void parse_line(){
	in=0;
//	if (!setjmp(env)){
		word();
		exec_cmd();
		uprint(" ok\n");
//	}else{
//		print_error();
//	}
}


void main(){
	clock_init(1);
	enable_uart(B115200);
	print_prompt();
	_ledoff();
	while (1){
		count=ureadln(tib,TIB_SIZE-1);
		parse_line();
	}
 
}
