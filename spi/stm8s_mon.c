/*
*  stm8s monitor program
*  syntax:
*    command  arg_list
*   
*  commands:
*    @ addr   -> display content at addr
*    ! addr value  ->  store value at address
*    : -> loop start store 'in' on control stack  
*    a addr -> enter assembler mode with addr as origin
*    c addr mask  -> clear bits using &~mask
*    d msec -> delay in milliseconds
*    h addr  -> memory dump in hexadecimal
*    r -> loop command, exit loop by CTRL_C
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

#include <stdio.h>
#include <setjmp.h>
#include "../inc/ascii.h"
#include "../inc/discovery.h"

// must be declare in this file to be include in vector table!!!
void uart2_rx_isr(void) __interrupt(INT_UART2_RX_FULL);

#define TIB_SIZE 80
#define PAD_SIZE 80
#define CSTK_SIZE 8
#define ASTK_SIZE 16
static signed char *eval_str;
static signed char tib[TIB_SIZE];
static signed char pad[PAD_SIZE];
static uint8_t ctrl_stack[CSTK_SIZE];
static int16_t arg_stack[ASTK_SIZE];
static int8_t csp=0;
static int8_t asp=0;
static uint8_t count;
static uint8_t in;
static uint8_t first;
#define ENV_SIZE 1024
static char env[ENV_SIZE];
static uint16_t here=0;

static jmp_buf abort;

static void eval();

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

static void timer4_init() {
    // CK_PSC (internal fMASTER) is divided by the prescaler value.
    TIM4_PSCR = TIM4_PSCR_128;
    // Enable update interrupt for timer 4
    TIM4_IER |= TIM4_IER_UIE;
    // Clear timer interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
    // auto-reload value
    TIM4_ARR=125; // 1msec
    // Enable timer 4
    TIM4_CR1 |= TIM4_CR1_CEN+TIM4_CR1_ARPE;
}

static uint16_t ticks=0;

void timer4_isr(void) __interrupt(INT_TIM4_OVF){
	ticks++;
    // Clear interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
}

//idle loop for msec milliseconds
static void delay_msec(uint16_t msec){
	uint16_t t0;
	t0=ticks+msec;
	while (ticks!=t0);
}

static bool digit(char c){
	return (c>='0') && (c<='9');
}

static bool hex_digit(char c){
	if (c>='a') c-=32;
	return digit(c) || ((c>='A') && (c<='F')); 
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
//	*--buf='$';
	return buf;
}


// copy from src to dest bc character
static void move(char *dest, const char* src,int16_t bc){
	while (bc>0){
		 *dest++=*src++;
		 bc--;
	 }
}

int16_t search_var(const char *name){
	int16_t i=0;
	while (i<here){
		if (!strcmp(&env[i],name)){
			return i;
		}
		i+=strlen(&env[i])+1;
		i+=(int16_t)env[i]+1;
	}
	return -1;
}

void delete_var(int16_t pos){
	int8_t name_len,val_len;
	int16_t var_next;
	
	name_len=(int8_t)strlen(&env[pos]);
	val_len=(int8_t)env[pos+name_len+1];
	var_next=pos+name_len+2+val_len;
	move(&env[pos],(const char*)&env[var_next],here-var_next);
	here-=var_next-pos;
	memset(&env[here],0,ENV_SIZE-here);
}


static const char error_msg[]="command error";

static const char prompt[]="READY";


static inline void print_error(){
	_ledon();
	puts(error_msg);
}

// skip character c in eval_str
static void skip(signed char c){
	while ((in<count) && eval_str[in] && (eval_str[in]==c)){in++;}
}

// scan eval_str for first occurance of c
static void scan(signed char c){
	while((in<count) && eval_str[in] && (eval_str[in]!=c)){in++;}
}

static void word(){
	skip(' ');
	first=in;  
	scan(' '); 
	move(pad,(const char*)&eval_str[first],in-first);
	pad[in-first]=0;
}

static int16_t pad2i(){
	bool negative=FALSE;
	uint8_t d, i=0, b=10;
	int16_t i16=0;
	
	if (pad[i]=='-'){
		negative=TRUE;
		i++;
	}else if ((pad[i]=='0') && ((pad[i+1]=='x')||(pad[i+1]=='X'))){b=16;i+=2;}
	while(pad[i]){
		d=(pad[i++]-'0')&0x1f;
		if (d>9) d-=7;
		if (d>=b)break;
		i16=i16*b+d;
	}
	if (negative) i16=-i16;
	return i16;
}

// try to convert pad content in number
// use default base if no prefix
static int16_t number(){
	word();
	return pad2i();
}

static bool try_number(){
	if (digit(pad[0])||((pad[0]=='-')&&digit(pad[1]))||((pad[0]=='$')&&hex_digit(pad[1]))){
		arg_stack[++asp]=pad2i();
		return TRUE;
	}
	return FALSE;
}

// print {address,value} pair
// format: hex(decimal) hex(decimal)
static void report(uint16_t addr, int8_t value){
		char *str;
		pad[6]=0;
		str=to_hex(&pad[6],addr,4);
		printf("%s(%d)=",str,addr);
	    pad[4]=0;
	    str=to_hex(&pad[4],(uint8_t)value,2);
	    printf("%s(%d)\n",str,value);
}

static void cmd_peek(){
	uint16_t addr;
	int8_t value;
	addr=number();
	value=*(int8_t*)addr;
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
	if (!result) puts("write failed");
}

static void cmd_store(){
	uint16_t addr;
	int8_t value;
	addr=number();
	do {
		skip(' ');
		if ((eval_str[in]==':') || (eval_str[in]==';'))break;
		value=(int8_t)number();
		report(addr,value);
		write_value((uint8_t*)addr,(uint8_t)value);
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
	uint8_t i=0;
	int8_t i8;
	char *str, ascii[11];
	ascii[0]=ascii[1]=' ';
	ascii[10]=0;
	str=to_hex(&pad[8],addr,6);
	pad[8]=' ';
	pad[9]=' ';
	pad[10]=0;
	printf(str);
	pad[9]=0;
	while (i<8){
		i8=*(int8_t*)addr++;
		if (i8>31) ascii[i+2]=i8;else ascii[i+2]=' ';
		str=to_hex(&pad[8],i8,2);
		printf(str);
		i++;
	}
	puts(ascii);
}

static void cmd_hdump(){
	uint16_t addr;
	signed char c;
	while (qchar()) getchar();
	addr=number();
	do{
		dump_row(addr); // print 8 bytes.
		addr+=8;
		putchar('?');
		c=getchar();
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

const char MSG_ENV_FULL[]="failed, environment full.";
static void cmd_create_var(){
	int16_t i;
	
	word(); // variable name
	i=search_var((const char*)pad);
	if (i>-1) delete_var(i);
	skip(' ');
	if (in<count){
		if ((here+strlen((const char*)pad)+2+count-in)>=ENV_SIZE){
			puts(MSG_ENV_FULL);
		}else{
			strcpy(&env[here],(const char*)pad);
			here+=strlen((const char*)pad)+1;
			env[here++]=count-in;
			move(&env[here],&eval_str[in],env[here-1]);
			here+=env[here-1];
			in=count;
		}
	}
	printf("%d env. bytes left\n",ENV_SIZE-here);
}

static void var_eval(){
	int16_t i;
	uint8_t cnt_save,in_save;
	signed char *eval_save;
	
	i=search_var(&pad[1]);
	if (i>-1){
		i+=strlen(&env[i])+1;
		cnt_save=count;
		in_save=in;
		eval_save=eval_str;
		in=0;
		count=(uint8_t)env[i++];
		eval_str=&env[i];
		eval();
		count=cnt_save;
		in=in_save;
		eval_str=eval_save;
	}else{
		in=count;
	}
}

static void exec_cmd(){
	int16_t tmp;
	switch(pad[0]){
	case '@':
		cmd_peek();
		break;
	case '!':
		cmd_store();
		break;
	case ';': // comment
		in=count;
		break;
	case ':': // mark loop begin
		ctrl_stack[++csp]=in;
		break;
	case '\'': // create env variable
		cmd_create_var();
		break;
	case '$': // variable substitution
	    var_eval();
	    break;
	case 'C':
		cmd_clear();
		break;
	case 'D': // dup ( n -- n n )
		if (asp>=0){
			tmp=arg_stack[asp];
			 arg_stack[++asp]=tmp;
		 }
	    break;	
	case 'E':
		if (asp>=0)putchar(arg_stack[asp--]&0x7f);
		break;
	case 'H':
		cmd_hdump();
		break;
    case 'K':
        if (qchar()){
			 arg_stack[++asp]=(int16_t)getchar();
		}else arg_stack[++asp]=0;
        break;
	case 'M':
	    delay_msec(number());
	    break;
    case 'O':
        if (asp>=1){
			 tmp=arg_stack[asp-1];
			 arg_stack[++asp]=tmp;
		 }
        break;
    case '?':
		if ((asp>=0) && arg_stack[asp--]){
			break;
		}
    case 'R':
        if (csp>=0) in=ctrl_stack[csp]; else in=0;
        break;
	case 'S':
		cmd_set();
		break;
	case 'T':
	    cmd_toggle();
		break;
	case 'X':
		cmd_execute();
		break;
	case '.': // print TOS
	   if (asp>=0) printf("%d",arg_stack[asp--]);
	   break;
	case '~':
	   if (asp>=0)arg_stack[asp]=~arg_stack[asp];
	   break;
	case '-': 
	    arg_stack[asp-1]=arg_stack[asp-1]-arg_stack[asp--];
		break;
	case '+': 
	    arg_stack[asp-1]=arg_stack[asp-1]+arg_stack[asp--];
	    break;
	case '*':
	    arg_stack[asp-1]=arg_stack[asp-1]*arg_stack[asp--];
	    break;
	case '/':
	   arg_stack[asp-1]=arg_stack[asp-1]/arg_stack[asp--];    
	   break;
	case '%':
	   arg_stack[asp-1]=arg_stack[asp-1]%arg_stack[asp--];
	   break;
	default:
	    if (! try_number()){
			 putchar(pad[0]);putchar(' ');
			 print_error();
		 }
		break;
	}//switch
}


static void eval(){
	signed char c;

		while (in<count){
			word();
			exec_cmd();
			if (qchar()){
				c=getchar();
				if (c==CTRL_C){
					longjmp(abort,1);
				 }
				ungetchar(c);
			}
		}
}

void main(){
	clock_init(1);
	timer4_init();
	interrupts();
	enable_uart(B115200);
	puts(prompt);
	_ledoff();
	while (1){
		count=ureadln(tib,TIB_SIZE-1);
		upper(tib);
		eval_str=tib;
		in=0;
		csp=0;
		while (csp<CSTK_SIZE)ctrl_stack[csp++]=0;
		csp=-1;
		asp=-1;
		if (!setjmp(abort)){eval();}
		if (asp>-1){
			printf("s: ");
			while (asp>-1){
				printf("%d ",arg_stack[asp--]);
			}
		}
		puts(" ok");
	}
}


