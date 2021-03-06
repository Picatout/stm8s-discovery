/*
 * 2019/04/04
 * STM8S105x4/6 µC registers map
 * code adapted from https://github.com/erno-szabados/sdcc-stm8s/stm8s.h
*/

#ifndef STM8S105_H
#define STM8S105_H
#include <stdint.h>

// bit mask
#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

#define Fmaster 16000000UL

// special fonction register type
#define sfr (volatile uint8_t*)
// pointer
#define sfrp *sfr

// controller memory regions
// C4/C6,S4/S6 and K4/K6 all have 2K RAM and 1K EEPROM
#define RAM_SIZE (2048) 
#define EEPROM_SIZE (1024)
// STM8S105x4 have 16K flash
#define X4_FLASH_SIZE (16384)
// STM8S105x6 have 32K flash
#define X6_FLASH_SIZE (32768)

#define RAM_BASE (0)
#define RAM_END (RAM_BASE+RAM_SIZE-1)
#define EEPROM_BASE (0x4000)
#define EEPROM_END (EEPROM_BASE+EEPROM_SIZE-1)
#define SFR_BASE (0x5000)
#define SFR_END (0x57FF)
#define FLASH_BASE (0x8000)
#define X6_FLASH_END (FLASH_BASE+X6_FLASH_SIZE-1)
#define X4_FLASH_END (FLASH_BASE+X4_FLASH_SIZE-1)
#define OPTION_BASE (0x4800)
#define OPTION_END (0x487F)
#define DEVID_BASE (0x48CD)
#define DEVID_END (0x48D8)

// options bytes
// this one can be programmed only from SWIM (ICP)
#define OPT0 sfrp(0x4800)
// these can be programmed at runtime (IAP)
#define OPT1 sfrp(0x4801)
#define NOPT1 sfrp(0x4802)
#define OPT2 sfrp(0x4803)
#define NOPT2 sfrp(0x4804)
#define OPT3 sfrp(0x4805)
#define NOPT3 sfrp(0x4806)
#define OPT4 sfrp(0x4807)
#define NOPT4 sfrp(0x4808)
#define OPT5 sfrp(0x4809)
#define NOPT5 sfrp(0x480A)
#define OPT6 sfrp(0x480B)
#define OPTBL sfrp(0x487E)
#define NOPTBL sfrp(0x487F)
// option registers usage
// read out protection, value 0xAA enable ROP
#define ROP OPT0  
// user boot code, {0..0x3e} 512 bytes row
#define UBC OPT1
#define NUBC NOPT1
// alternate function register
#define AFR OPT2
#define NAFR NOPT2
// miscelinous options
#define MISCOPT OPT3
#define NMISCOPT NOPT3
// clock options
#define CLKOPT OPT4
#define NCLKOPT NOPT4
// HSE clock startup delay
#define HSECNT OPT5
#define NHSECNT NOPT5

// MISCOPT bits
#define  MISCOPT_HSITRIM   BIT4
#define  MISCOPT_LSIEN     BIT3
#define  MISCOPT_IWDG_HW   BIT2
#define  MISCOPT_WWDG_HW   BIT1
#define  MISCOPT_WWDG_HALT BIT0
// NMISCOPT bits
#define  NMISCOPT_NHSITRIM   ~BIT4
#define  NMISCOPT_NLSIEN     ~BIT3
#define  NMISCOPT_NIWDG_HW   ~BIT2
#define  NMISCOPT_NWWDG_HW   ~BIT1
#define  NMISCOPT_NWWDG_HALT ~BIT0
// CLKOPT bits
#define CLKOPT_EXT_CLK  BIT3
#define CLKOPT_CKAWUSEL BIT2
#define CLKOPT_PRS_C1   BIT1
#define CLKOPT_PRS_C0   BIT0
// NCLKOPT bits
#define NCLKOPT_NEXT_CLK  ~BIT3
#define NCLKOPT_NCKAWUSEL ~BIT2
#define NCLKOPT_NPRS_C1   ~BIT1
#define NCLKOPT_NPRS_C0   ~BIT0

// AFR option, remapable functions
#define AFR7_BEEP    BIT7
#define AFR6_I2C     BIT6
#define AFR5_TIM1    BIT5
#define AFR4_TIM1  	 BIT4
#define AFR3_TIM1    BIT3
#define AFR2_CCO     BIT2
#define AFR1_TIM2    BIT1
#define AFR0_ADC     BIT0
// NAFR option, remapable functions
#define NAFR7_NBEEP    ~BIT7
#define NAFR6_NI2C     ~BIT6
#define NAFR5_NTIM1    ~BIT5
#define NAFR4_NTIM1    ~BIT4
#define NAFR3_NTIM1    ~BIT3
#define NAFR2_NCCO     ~BIT2
#define NAFR1_NTIM2    ~BIT1
#define NAFR0_NADC     ~BIT0
 

//device ID (read only)
#define DEVID_XL sfrp(0x48CD)
#define DEVID_XH sfrp(0x48CE)
#define DEVID_YL sfrp(0x48CF)
#define DEVID_YH sfrp(0x48D0)
#define DEVID_WAF sfrp(0x48D1)
#define DEVID_LOT0 sfrp(0x48D2)
#define DEVID_LOT1 sfrp(0x48D3)
#define DEVID_LOT2 sfrp(0x48D4)
#define DEVID_LOT3 sfrp(0x48D5)
#define DEVID_LOT4 sfrp(0x48D6)
#define DEVID_LOT5 sfrp(0x48D7)
#define DEVID_LOT6 sfrp(0x48D8)


typedef struct{
	uint8_t odr;
	uint8_t idr;
	uint8_t ddr;
	uint8_t cr1;
	uint8_t cr2; 
}gpio_t;

// GPIO ports array
#define PORT_COUNT  (7)
#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5
#define PG 6
// port bit mask
#define PIN0 (1<<0)
#define PIN1 (1<<1)
#define PIN2 (1<<2)
#define PIN3 (1<<3)
#define PIN4 (1<<4)
#define PIN5 (1<<5)
#define PIN6 (1<<6)
#define PIN7 (1<<7)

#define GPIO 0x5000

/* GPIO */
#define PA_ODR sfrp(0x5000)
#define PA_IDR sfrp(0x5001)
#define PA_DDR sfrp(0x5002)
#define PA_CR1 sfrp(0x5003)
#define PA_CR2 sfrp(0x5004)

#define PB_ODR sfrp(0x5005)
#define PB_IDR sfrp(0x5006)
#define PB_DDR sfrp(0x5007)
#define PB_CR1 sfrp(0x5008)
#define PB_CR2 sfrp(0x5009)

#define PC_ODR sfrp(0x500A)
#define PC_IDR sfrp(0x500B)
#define PC_DDR sfrp(0x500C)
#define PC_CR1 sfrp(0x500D)
#define PC_CR2 sfrp(0x500E)

#define PD_ODR sfrp(0x500F)
#define PD_IDR sfrp(0x5010)
#define PD_DDR sfrp(0x5011)
#define PD_CR1 sfrp(0x5012)
#define PD_CR2 sfrp(0x5013)

#define PE_ODR sfrp(0x5014)
#define PE_IDR sfrp(0x5015)
#define PE_DDR sfrp(0x5016)
#define PE_CR1 sfrp(0x5017)
#define PE_CR2 sfrp(0x5018)

#define PF_ODR sfrp(0x5019)
#define PF_IDR sfrp(0x501A)
#define PF_DDR sfrp(0x501B)
#define PF_CR1 sfrp(0x501C)
#define PF_CR2 sfrp(0x501D)

#define PG_ODR sfrp(0x501E)
#define PG_IDR sfrp(0x501F)
#define PG_DDR sfrp(0x5020)
#define PG_CR1 sfrp(0x5021)
#define PG_CR2 sfrp(0x5022)

//input modes CR1
#define INPUT_FLOAT (0)
#define INPUT_PULLUP (1)
//output mode CR1
#define OUTPUT_OD (0)
#define OUTPUT_PP (1)
//input modes CR2
#define INPUT_DI (0)
#define INPUT_EI (1)
//output speed CR2
#define OUTPUT_SLOW (0)
#define OUTPUT_FAST (1)
// combined bits for configuration
//input, bit 0 -> input type, bit 1 -> interrupt
#define INPUT_FLOAT_DI (0)
#define INPUT_FLOAT_EI (2)
#define INPUT_PU_DI (1)
#define INPUT_PU_EI (3)
//output, bit 0 -> type, bit 1 -> speed
#define OUTPUT_OD_SLOW (0+4)
#define OUTPUT_OD_FAST (2+4)
#define OUTPUT_PP_SLOW (1+4)
#define OUTPUT_PP_FAST (3+4)


/* Flash */
#define FLASH_CR1 sfrp(0x505A)
#define FLASH_CR2 sfrp(0x505B)
#define FLASH_NCR2 sfrp(0x505C)
#define FLASH_FPR sfrp(0x505D)
#define FLASH_NFPR sfrp(0x505E)
#define FLASH_IAPSR sfrp(0x505F)
#define FLASH_PUKR sfrp(0x5062)
#define FLASH_DUKR sfrp(0x5064)
// data memory unlock keys
#define FLASH_DUKR_KEY1 (0xae)
#define FLASH_DUKR_KEY2 (0x56)
// flash memory unlock keys
#define FLASH_PUKR_KEY1 (0x56)
#define FLASH_PUKR_KEY2 (0xae)
// FLASH_CR1 bits
#define FLASH_CR1_HALT BIT3
#define FLASH_CR1_AHALT BIT2
#define FLASH_CR1_IE BIT1
#define FLASH_CR1_FIX BIT0
// FLASH_CR2 bits
#define FLASH_CR2_OPT BIT7
#define FLASH_CR2_WPRG BIT6
#define FLASH_CR2_ERASE BIT5
#define FLASH_CR2_FPRG BIT4
#define FLASH_CR2_PRG BIT0
// FLASH_NCR2 bits
#define FLASH_NCR2_NOPT ~BIT7
#define FLASH_NCR2_NWPRG ~BIT6
#define FLASH_NCR2_NERASE ~BIT5
#define FLASH_NCR2_NFPRG ~BIT4
#define FLASH_NCR2_NPRG ~BIT0
// FLASH_FPR bits
#define FLASH_FPR_WPB5 BIT5
#define FLASH_FPR_WPB4 BIT4
#define FLASH_FPR_WPB3 BIT3
#define FLASH_FPR_WPB2 BIT2
#define FLASH_FPR_WPB1 BIT1
#define FLASH_FPR_WPB0 BIT0
// FLASH_NFPR bits
#define FLASH_NFPR_NWPB5 BIT5
#define FLASH_NFPR_NWPB4 BIT4
#define FLASH_NFPR_NWPB3 BIT3
#define FLASH_NFPR_NWPB2 BIT2
#define FLASH_NFPR_NWPB1 BIT1
#define FLASH_NFPR_NWPB0 BIT0
// FLASH_IAPSR bits
#define FLASH_IAPSR_HVOFF BIT6
#define FLASH_IAPSR_DUL BIT3
#define FLASH_IAPSR_EOP BIT2
#define FLASH_IAPSR_PUL BIT1
#define FLASH_IAPSR_WR_PG_DIS BIT0

/* Interrupt control */
#define EXTI_CR1 sfrp(0x50A0)
#define EXTI_CR2 sfrp(0x50A1)

/* Reset Status */
#define RST_SR sfrp(0x50B3)

/* Clock Registers */
#define CLK_ICKR sfrp(0x50c0)
#define CLK_ECKR sfrp(0x50c1)
#define CLK_CMSR sfrp(0x50C3)
#define CLK_SWR sfrp(0x50C4)
#define CLK_SWCR sfrp(0x50C5)
#define CLK_CKDIVR sfrp(0x50C6)
#define CLK_PCKENR1 sfrp(0x50C7)
#define CLK_CSSR sfrp(0x50C8)
#define CLK_CCOR sfrp(0x50C9)
#define CLK_PCKENR2 sfrp(0x50CA)
#define CLK_HSITRIMR sfrp(0x50CC)
#define CLK_SWIMCCR sfrp(0x50CD)

// Peripherals clock gating
// CLK_PCKENR1 
#define CLK_PCKENR1_TIM1 (1<<7)
#define CLK_PCKENR1_TIM3 (1<<6)
#define CLK_PCKENR1_TIM2 (1<<5)
#define CLK_PCKENR1_TIM4 (1<<4)
#define CLK_PCKENR1_UART2 (1<<3)
#define CLK_PCKENR1_SPI (1<<1)
#define CLK_PCKENR1_I2C (1<<0)
//CLK_PCKENR2
#define CLK_PCKENR2_ADC (1<<3)
#define CLK_PCKENR2_AWU (1<<2)

/* Clock bitmasks */
#define CLK_ICKR_REGAH (1 << 5)
#define CLK_ICKR_LSIRDY (1 << 4)
#define CLK_ICKR_LSIEN (1 << 3)
#define CLK_ICKR_FHW (1 << 2)
#define CLK_ICKR_HSIRDY (1 << 1)
#define CLK_ICKR_HSIEN (1 << 0)

#define CLK_ECKR_HSERDY (1 << 1)
#define CLK_ECKR_HSEEN (1 << 0)
// clock source
#define CLK_SWR_HSI 0xE1
#define CLK_SWR_LSI 0xD2
#define CLK_SWR_HSE 0xB4

#define CLK_SWCR_SWIF (1 << 3)
#define CLK_SWCR_SWIEN (1 << 2)
#define CLK_SWCR_SWEN (1 << 1)
#define CLK_SWCR_SWBSY (1 << 0)

#define CLK_CKDIVR_HSIDIV1 (1 << 4)
#define CLK_CKDIVR_HSIDIV0 (1 << 3)
#define CLK_CKDIVR_CPUDIV2 (1 << 2)
#define CLK_CKDIVR_CPUDIV1 (1 << 1)
#define CLK_CKDIVR_CPUDIV0 (1 << 0)

/* Watchdog */
#define WWDG_CR sfrp(0x50D1)
#define WWDG_WR sfrp(0x50D2)
#define IWDG_KR sfrp(0x50E0)
#define IWDG_PR sfrp(0x50E1)
#define IWDG_RLR sfrp(0x50E2)
#define AWU_CSR1 sfrp(0x50F0)
#define AWU_APR sfrp(0x50F1)
#define AWU_TBR sfrp(0x50F2)

/* Beep */
#define BEEP_CSR sfrp(0x50F3)

/* SPI */
#define SPI_CR1 sfrp(0x5200)
#define SPI_CR2 sfrp(0x5201)
#define SPI_ICR sfrp(0x5202)
#define SPI_SR sfrp(0x5203)
#define SPI_DR sfrp(0x5204)
#define SPI_CRCPR sfrp(0x5205)
#define SPI_RXCRCR sfrp(0x5206)
#define SPI_TXCRCR sfrp(0x5207)

/* I2C */
#define I2C_CR1 sfrp(0x5210)
#define I2C_CR2 sfrp(0x5211)
#define I2C_FREQR sfrp(0x5212)
#define I2C_OARL sfrp(0x5213)
#define I2C_OARH sfrp(0x5214)
#define I2C_DR sfrp(0x5216)
#define I2C_SR1 sfrp(0x5217)
#define I2C_SR2 sfrp(0x5218)
#define I2C_SR3 sfrp(0x5219)
#define I2C_ITR sfrp(0x521A)
#define I2C_CCRL sfrp(0x521B)
#define I2C_CCRH sfrp(0x521C)
#define I2C_TRISER sfrp(0x521D)
#define I2C_PECR sfrp(0x521E)

#define I2C_CR1_NOSTRETCH (1 << 7)
#define I2C_CR1_ENGC (1 << 6)
#define I2C_CR1_PE (1 << 0)

#define I2C_CR2_SWRST (1 << 7)
#define I2C_CR2_POS (1 << 3)
#define I2C_CR2_ACK (1 << 2)
#define I2C_CR2_STOP (1 << 1)
#define I2C_CR2_START (1 << 0)

#define I2C_OARL_ADD0 (1 << 0)

#define I2C_OAR_ADDR_7BIT ((I2C_OARL & 0xFE) >> 1)
#define I2C_OAR_ADDR_10BIT (((I2C_OARH & 0x06) << 9) | (I2C_OARL & 0xFF))

#define I2C_OARH_ADDMODE (1 << 7)
#define I2C_OARH_ADDCONF (1 << 6)
#define I2C_OARH_ADD9 (1 << 2)
#define I2C_OARH_ADD8 (1 << 1)

#define I2C_SR1_TXE (1 << 7)
#define I2C_SR1_RXNE (1 << 6)
#define I2C_SR1_STOPF (1 << 4)
#define I2C_SR1_ADD10 (1 << 3)
#define I2C_SR1_BTF (1 << 2)
#define I2C_SR1_ADDR (1 << 1)
#define I2C_SR1_SB (1 << 0)

#define I2C_SR2_WUFH (1 << 5)
#define I2C_SR2_OVR (1 << 3)
#define I2C_SR2_AF (1 << 2)
#define I2C_SR2_ARLO (1 << 1)
#define I2C_SR2_BERR (1 << 0)

#define I2C_SR3_DUALF (1 << 7)
#define I2C_SR3_GENCALL (1 << 4)
#define I2C_SR3_TRA (1 << 2)
#define I2C_SR3_BUSY (1 << 1)
#define I2C_SR3_MSL (1 << 0)

#define I2C_ITR_ITBUFEN (1 << 2)
#define I2C_ITR_ITEVTEN (1 << 1)
#define I2C_ITR_ITERREN (1 << 0)

/* Precalculated values, all in KHz */
#define I2C_CCRH_16MHZ_FAST_400 0x80
#define I2C_CCRL_16MHZ_FAST_400 0x0D
/*
 * Fast I2C mode max rise time = 300ns
 * I2C_FREQR = 16 (MHz) => tMASTER = 1/16 = 62.5 ns
 * TRISER = (300/62.5) + 1 = floor(4.8) + 1 = 5.
 */
#define I2C_TRISER_16MHZ_FAST_400 0x05;

#define I2C_CCRH_16MHZ_FAST_320 0xC0
#define I2C_CCRL_16MHZ_FAST_320 0x02
#define I2C_TRISER_16MHZ_FAST_320 0x05;

#define I2C_CCRH_16MHZ_FAST_200 0x80
#define I2C_CCRL_16MHZ_FAST_200 0x1A
#define I2C_TRISER_16MHZ_FAST_200 0x05;

#define I2C_CCRH_16MHZ_STD_100 0x00
#define I2C_CCRL_16MHZ_STD_100 0x50
/*
 * Standard I2C mode max rise time = 1000ns
 * I2C_FREQR = 16 (MHz) => tMASTER = 1/16 = 62.5 ns
 * TRISER = (1000/62.5) + 1 = floor(16) + 1 = 17.
 */
#define I2C_TRISER_16MHZ_STD_100 0x11;

#define I2C_CCRH_16MHZ_STD_50 0x00
#define I2C_CCRL_16MHZ_STD_50 0xA0
#define I2C_TRISER_16MHZ_STD_50 0x11;

#define I2C_CCRH_16MHZ_STD_20 0x01
#define I2C_CCRL_16MHZ_STD_20 0x90
#define I2C_TRISER_16MHZ_STD_20 0x11;

#define I2C_READ 1
#define I2C_WRITE 0

typedef enum {
// baudrate constant for brr_value table access
B2400=0,
B4800,
B9600,
B19200,
B38400,
B57600,
B115200,
B230400,
B460800,
B921600,
}baud_t;

/* UART2 */
#define UART2_SR   sfrp(0x5240)
#define UART2_DR   sfrp(0x5241)
#define UART2_BRR1 sfrp(0x5242)
#define UART2_BRR2 sfrp(0x5243)
#define UART2_CR1  sfrp(0x5244)
#define UART2_CR2  sfrp(0x5245)
#define UART2_CR3  sfrp(0x5246)
#define UART2_CR4  sfrp(0x5247)
#define UART2_CR5  sfrp(0x5248)
#define UART2_CR6  sfrp(0x4249)
#define UART2_GTR  sfrp(0x524A)
#define UART2_PSCR sfrp(0x524B)



/* UART Status Register bits */
#define UART_SR_TXE (1 << 7)
#define UART_SR_TC (1 << 6)
#define UART_SR_RXNE (1 << 5)
#define UART_SR_IDLE (1 << 4)
#define UART_SR_OR (1 << 3)
#define UART_SR_NF (1 << 2)
#define UART_SR_FE (1 << 1)
#define UART_SR_PE (1 << 0)

/* Uart Control Register bits */
#define UART_CR1_R8 (1 << 7)
#define UART_CR1_T8 (1 << 6)
#define UART_CR1_UARTD (1 << 5)
#define UART_CR1_M (1 << 4)
#define UART_CR1_WAKE (1 << 3)
#define UART_CR1_PCEN (1 << 2)
#define UART_CR1_PS (1 << 1)
#define UART_CR1_PIEN (1 << 0)

#define UART_CR2_TIEN (1 << 7)
#define UART_CR2_TCIEN (1 << 6)
#define UART_CR2_RIEN (1 << 5)
#define UART_CR2_ILIEN (1 << 4)
#define UART_CR2_TEN (1 << 3)
#define UART_CR2_REN (1 << 2)
#define UART_CR2_RWU (1 << 1)
#define UART_CR2_SBK (1 << 0)

#define UART_CR3_LINEN (1 << 6)
#define UART_CR3_STOP1 (1 << 5)
#define UART_CR3_STOP0 (1 << 4)
#define UART_CR3_CLKEN (1 << 3)
#define UART_CR3_CPOL (1 << 2)
#define UART_CR3_CPHA (1 << 1)
#define UART_CR3_LBCL (1 << 0)

#define UART_CR4_LBDIEN (1 << 6)
#define UART_CR4_LBDL (1 << 5)
#define UART_CR4_LBDF (1 << 4)
#define UART_CR4_ADD3 (1 << 3)
#define UART_CR4_ADD2 (1 << 2)
#define UART_CR4_ADD1 (1 << 1)
#define UART_CR4_ADD0 (1 << 0)

#define UART_CR5_SCEN (1 << 5)
#define UART_CR5_NACK (1 << 4)
#define UART_CR5_HDSEL (1 << 3)
#define UART_CR5_IRLP (1 << 2)
#define UART_CR5_IREN (1 << 1)

/* TIMERS */
/* Timer 1 - 16-bit timer with complementary PWM outputs */
#define TIM1_CR1 sfrp(0x5250)
#define TIM1_CR2 sfrp(0x5251)
#define TIM1_SMCR sfrp(0x5252)
#define TIM1_ETR sfrp(0x5253)
#define TIM1_IER sfrp(0x5254)
#define TIM1_SR1 sfrp(0x5255)
#define TIM1_SR2 sfrp(0x5256)
#define TIM1_EGR sfrp(0x5257)
#define TIM1_CCMR1 sfrp(0x5258)
#define TIM1_CCMR2 sfrp(0x5259)
#define TIM1_CCMR3 sfrp(0x525A)
#define TIM1_CCMR4 sfrp(0x525B)
#define TIM1_CCER1 sfrp(0x525C)
#define TIM1_CCER2 sfrp(0x525D)
#define TIM1_CNTRH sfrp(0x525E)
#define TIM1_CNTRL sfrp(0x525F)
#define TIM1_PSCRH sfrp(0x5260)
#define TIM1_PSCRL sfrp(0x5261)
#define TIM1_ARRH sfrp(0x5262)
#define TIM1_ARRL sfrp(0x5263)
#define TIM1_RCR sfrp(0x5264)
#define TIM1_CCR1H sfrp(0x5265)
#define TIM1_CCR1L sfrp(0x5266)
#define TIM1_CCR2H sfrp(0x5267)
#define TIM1_CCR2L sfrp(0x5268)
#define TIM1_CCR3H sfrp(0x5269)
#define TIM1_CCR3L sfrp(0x526A)
#define TIM1_CCR4H sfrp(0x526B)
#define TIM1_CCR4L sfrp(0x526C)
#define TIM1_BKR sfrp(0x526D)
#define TIM1_DTR sfrp(0x526E)
#define TIM1_OISR sfrp(0x526F)

/* Timer Control Register bits */
#define TIM_CR1_ARPE (1 << 7)
#define TIM_CR1_CMSH (1 << 6)
#define TIM_CR1_CMSL (1 << 5)
#define TIM_CR1_DIR (1 << 4)
#define TIM_CR1_OPM (1 << 3)
#define TIM_CR1_URS (1 << 2)
#define TIM_CR1_UDIS (1 << 1)
#define TIM_CR1_CEN (1 << 0)

#define TIM1_CR2_MMS2 (1 << 6)
#define TIM1_CR2_MMS1 (1 << 5)
#define TIM1_CR2_MMS0 (1 << 4)
#define TIM1_CR2_COMS (1 << 2)
#define TIM1_CR2_CCPC (1 << 0)

/* Timer Slave Mode Control bits */
#define TIM1_SMCR_MSM (1 << 7)
#define TIM1_SMCR_TS2 (1 << 6)
#define TIM1_SMCR_TS1 (1 << 5)
#define TIM1_SMCR_TS0 (1 << 4)
#define TIM1_SMCR_SMS2 (1 << 2)
#define TIM1_SMCR_SMS1 (1 << 1)
#define TIM1_SMCR_SMS0 (1 << 0)

/* Timer External Trigger Enable bits */
#define TIM1_ETR_ETP (1 << 7)
#define TIM1_ETR_ECE (1 << 6)
#define TIM1_ETR_ETPS1 (1 << 5)
#define TIM1_ETR_ETPS0 (1 << 4)
#define TIM1_ETR_ETF3 (1 << 3)
#define TIM1_ETR_ETF2 (1 << 2)
#define TIM1_ETR_ETF1 (1 << 1)
#define TIM1_ETR_ETF0 (1 << 0)

/* Timer Interrupt Enable bits */
#define TIM1_IER_BIE (1 << 7)
#define TIM1_IER_TIE (1 << 6)
#define TIM1_IER_COMIE (1 << 5)
#define TIM1_IER_CC4IE (1 << 4)
#define TIM1_IER_CC3IE (1 << 3)
#define TIM1_IER_CC2IE (1 << 2)
#define TIM1_IER_CC1IE (1 << 1)
#define TIM1_IER_UIE (1 << 0)

/* Timer Status Register bits */
#define TIM1_SR1_BIF (1 << 7)
#define TIM1_SR1_TIF (1 << 6)
#define TIM1_SR1_COMIF (1 << 5)
#define TIM1_SR1_CC4IF (1 << 4)
#define TIM1_SR1_CC3IF (1 << 3)
#define TIM1_SR1_CC2IF (1 << 2)
#define TIM1_SR1_CC1IF (1 << 1)
#define TIM1_SR1_UIF (1 << 0)

#define TIM1_SR2_CC4OF (1 << 4)
#define TIM1_SR2_CC3OF (1 << 3)
#define TIM1_SR2_CC2OF (1 << 2)
#define TIM1_SR2_CC1OF (1 << 1)

/* Timer Event Generation Register bits */
#define TIM1_EGR_BG (1 << 7)
#define TIM1_EGR_TG (1 << 6)
#define TIM1_EGR_COMG ( 1 << 5)
#define TIM1_EGR_CC4G (1 << 4)
#define TIM1_EGR_CC3G (1 << 3)
#define TIM1_EGR_CC2G (1 << 2)
#define TIM1_EGR_CC1G (1 << 1)
#define TIM1_EGR_UG (1 << 0)

/* Capture/Compare Mode Register 1 - channel configured in output */
#define TIM1_CCMR1_OC1CE (1 << 7)
#define TIM1_CCMR1_OC1M2 (1 << 6)
#define TIM1_CCMR1_OC1M1 (1 << 5)
#define TIM1_CCMR1_OC1M0 (1 << 4)
#define TIM1_CCMR1_OC1PE (1 << 3)
#define TIM1_CCMR1_OC1FE (1 << 2)
#define TIM1_CCMR1_CC1S1 (1 << 1)
#define TIM1_CCMR1_CC1S0 (1 << 0)

/* Capture/Compare Mode Register 1 - channel configured in input */
#define TIM1_CCMR1_IC1F3 (1 << 7)
#define TIM1_CCMR1_IC1F2 (1 << 6)
#define TIM1_CCMR1_IC1F1 (1 << 5)
#define TIM1_CCMR1_IC1F0 (1 << 4)
#define TIM1_CCMR1_IC1PSC1 (1 << 3)
#define TIM1_CCMR1_IC1PSC0 (1 << 2)
/* #define TIM1_CCMR1_CC1S1 (1 << 1)
#define TIM1_CCMR1_CC1S0 (1 << 0) */

/* Capture/Compare Mode Register 2 - channel configured in output */
#define TIM1_CCMR2_OC2CE (1 << 7)
#define TIM1_CCMR2_OC2M2 (1 << 6)
#define TIM1_CCMR2_OC2M1 (1 << 5)
#define TIM1_CCMR2_OC2M0 (1 << 4)
#define TIM1_CCMR2_OC2PE (1 << 3)
#define TIM1_CCMR2_OC2FE (1 << 2)
#define TIM1_CCMR2_CC2S1 (1 << 1)
#define TIM1_CCMR2_CC2S0 (1 << 0)

/* Capture/Compare Mode Register 2 - channel configured in input */
#define TIM1_CCMR2_IC2F3 (1 << 7)
#define TIM1_CCMR2_IC2F2 (1 << 6)
#define TIM1_CCMR2_IC2F1 (1 << 5)
#define TIM1_CCMR2_IC2F0 (1 << 4)
#define TIM1_CCMR2_IC2PSC1 (1 << 3)
#define TIM1_CCMR2_IC2PSC0 (1 << 2)
/* #define TIM1_CCMR2_CC2S1 (1 << 1)
#define TIM1_CCMR2_CC2S0 (1 << 0) */

/* Capture/Compare Mode Register 3 - channel configured in output */
#define TIM1_CCMR3_OC3CE (1 << 7)
#define TIM1_CCMR3_OC3M2 (1 << 6)
#define TIM1_CCMR3_OC3M1 (1 << 5)
#define TIM1_CCMR3_OC3M0 (1 << 4)
#define TIM1_CCMR3_OC3PE (1 << 3)
#define TIM1_CCMR3_OC3FE (1 << 2)
#define TIM1_CCMR3_CC3S1 (1 << 1)
#define TIM1_CCMR3_CC3S0 (1 << 0)

/* Capture/Compare Mode Register 3 - channel configured in input */
#define TIM1_CCMR3_IC3F3 (1 << 7)
#define TIM1_CCMR3_IC3F2 (1 << 6)
#define TIM1_CCMR3_IC3F1 (1 << 5)
#define TIM1_CCMR3_IC3F0 (1 << 4)
#define TIM1_CCMR3_IC3PSC1 (1 << 3)
#define TIM1_CCMR3_IC3PSC0 (1 << 2)
/* #define TIM1_CCMR3_CC3S1 (1 << 1)
#define TIM1_CCMR3_CC3S0 (1 << 0) */

/* Capture/Compare Mode Register 4 - channel configured in output */
#define TIM1_CCMR4_OC4CE (1 << 7)
#define TIM1_CCMR4_OC4M2 (1 << 6)
#define TIM1_CCMR4_OC4M1 (1 << 5)
#define TIM1_CCMR4_OC4M0 (1 << 4)
#define TIM1_CCMR4_OC4PE (1 << 3)
#define TIM1_CCMR4_OC4FE (1 << 2)
#define TIM1_CCMR4_CC4S1 (1 << 1)
#define TIM1_CCMR4_CC4S0 (1 << 0)

/* Capture/Compare Mode Register 4 - channel configured in input */
#define TIM1_CCMR4_IC4F3 (1 << 7)
#define TIM1_CCMR4_IC4F2 (1 << 6)
#define TIM1_CCMR4_IC4F1 (1 << 5)
#define TIM1_CCMR4_IC4F0 (1 << 4)
#define TIM1_CCMR4_IC4PSC1 (1 << 3)
#define TIM1_CCMR4_IC4PSC0 (1 << 2)
/* #define TIM1_CCMR4_CC4S1 (1 << 1)
#define TIM1_CCMR4_CC4S0 (1 << 0) */

/* Timer 2 - 16-bit timer */
#define TIM2_CR1 sfrp(0x5300)
#define TIM2_IER sfrp(0x5301)
#define TIM2_SR1 sfrp(0x5302)
#define TIM2_SR2 sfrp(0x5303)
#define TIM2_EGR sfrp(0x5304)
#define TIM2_CCMR1 sfrp(0x5305)
#define TIM2_CCMR2 sfrp(0x5306)
#define TIM2_CCMR3 sfrp(0x5307)
#define TIM2_CCER1 sfrp(0x5308)
#define TIM2_CCER2 sfrp(0x5309)
#define TIM2_CNTRH sfrp(0x530A)
#define TIM2_CNTRL sfrp(0x530B)
#define TIM2_PSCR sfrp(0x530C)
#define TIM2_ARRH sfrp(0x530D)
#define TIM2_ARRL sfrp(0x530E)
#define TIM2_CCR1H sfrp(0x530F)
#define TIM2_CCR1L sfrp(0x5310)
#define TIM2_CCR2H sfrp(0x5311)
#define TIM2_CCR2L sfrp(0x5312)
#define TIM2_CCR3H sfrp(0x5313)
#define TIM2_CCR3L sfrp(0x5314)

/* Timer 3 */
#define TIM3_CR1 sfrp(0x5320)
#define TIM3_IER sfrp(0x5321)
#define TIM3_SR1 sfrp(0x5322)
#define TIM3_SR2 sfrp(0x5323)
#define TIM3_EGR sfrp(0x5324)
#define TIM3_CCMR1 sfrp(0x5325)
#define TIM3_CCMR2 sfrp(0x5326)
#define TIM3_CCER1 sfrp(0x5327)
#define TIM3_CNTRH sfrp(0x5328)
#define TIM3_CNTRL sfrp(0x5329)
#define TIM3_PSCR sfrp(0x532A)
#define TIM3_ARRH sfrp(0x532B)
#define TIM3_ARRL sfrp(0x532C)
#define TIM3_CCR1H sfrp(0x532D)
#define TIM3_CCR1L sfrp(0x532E)
#define TIM3_CCR2H sfrp(0x532F)
#define TIM3_CCR2L sfrp(0x5330)

// TIM3_CR1  fields
#define TIM3_CR1_CEN (1<<0)
#define TIM3_CR1_UDIS (1<<1)
#define TIM3_CR1_URS (1<<2)
#define TIM3_CR1_OPM (1<<3)
#define TIM3_CR1_ARPE (1<<7)
//TIM3_CCR2  fields
#define TIM3_CCMR2_CC2S_POS (0)
#define TIM3_CCMR2_OC2PE_POS (3)
#define TIM3_CCMR2_OC2M_POS (4)  
//TIM3_CCER1 fields
#define TIM3_CCER1_CC1E (1<<0)
#define TIM3_CCER1_CC1P (1<<1)
#define TIM3_CCER1_CC2E (1<<4)
#define TIM3_CCER1_CC2P (1<<5)
//TIM3_CCER2 fields
#define TIM3_CCER2_CC3E (1<<0)
#define TIM3_CCER2_CC3P (1<<1)

/* Timer 4 */
#define TIM4_CR1 sfrp(0x5340)
#define TIM4_IER sfrp(0x5341)
#define TIM4_SR sfrp(0x5342)
#define TIM4_EGR sfrp(0x5343)
#define TIM4_CNTR sfrp(0x5344)
#define TIM4_PSCR sfrp(0x5345)
#define TIM4_ARR sfrp(0x5346)

/* Timer 4 bitmasks */

#define TIM4_CR1_ARPE (1 << 7)
#define TIM4_CR1_OPM (1 << 3)
#define TIM4_CR1_URS (1 << 2)
#define TIM4_CR1_UDIS (1 << 1)
#define TIM4_CR1_CEN (1 << 0)

#define TIM4_IER_UIE (1 << 0)

#define TIM4_SR_UIF (1 << 0)

#define TIM4_EGR_UG (1 << 0)

#define TIM4_PSCR_PSC2 (1 << 2)
#define TIM4_PSCR_PSC1 (1 << 1)
#define TIM4_PSCR_PSC0 (1 << 0)

#define TIM4_PSCR_1 0
#define TIM4_PSCR_2 1
#define TIM4_PSCR_4 2
#define TIM4_PSCR_8 3
#define TIM4_PSCR_16 4
#define TIM4_PSCR_32 5
#define TIM4_PSCR_64 6
#define TIM4_PSCR_128 7

/* ADC 1 */
typedef union{
	struct{
	uint8_t hbyte;
	uint8_t lbyte;
   }bytes;
   uint16_t bi; // big indian stored
}adc_data_t;

#define ADC_ARRAY_SIZE 10
typedef struct{
	adc_data_t data[ADC_ARRAY_SIZE];
}adc_array_t;

#define ADC_DATA_ARRAY *(volatile *adc_array_t)(0x53E0)
// individual element access
#define ADC_DB0RH sfrp(0x53E0)
#define ADC_DB0RL sfrp(0x53E1)
#define ADC_DB1RH sfrp(0x53E2)
#define ADC_DB1RL sfrp(0x53E3)
#define ADC_DB2RH sfrp(0x53E4)
#define ADC_DB2RL sfrp(0x53E5)
#define ADC_DB3RH sfrp(0x53E6)
#define ADC_DB3RL sfrp(0x53E7)
#define ADC_DB4RH sfrp(0x53E8)
#define ADC_DB4RL sfrp(0x53E9)
#define ADC_DB5RH sfrp(0x53EA)
#define ADC_DB5RL sfrp(0x53EB)
#define ADC_DB6RH sfrp(0x53EC)
#define ADC_DB6RL sfrp(0x53ED)
#define ADC_DB7RH sfrp(0x53EE)
#define ADC_DB7RL sfrp(0x53EF)
#define ADC_DB8RH sfrp(0x53F0)
#define ADC_DB8RL sfrp(0x53F1)
#define ADC_DB9RH sfrp(0x53F2)
#define ADC_DB9RL sfrp(0x53F3)

#define ADC_CSR sfrp(0x5400)
#define ADC_CR1 sfrp(0x5401)
#define ADC_CR2 sfrp(0x5402)
#define ADC_CR3 sfrp(0x5403)
#define ADC_DRH sfrp(0x5404)
#define ADC_DRL sfrp(0x5405)
#define ADC_TDRH sfrp(0x5406)
#define ADC_TDRL sfrp(0x5407)
#define ADC_HTRH sfrp(0x5408)
#define ADC_HTRL sfrp(0x5409)
#define ADC_LTRH sfrp(0x540A)
#define ADC_LTRL sfrp(0x540B)
#define ADC_AWSRH sfrp(0x540C)
#define ADC_AWSRL sfrp(0x540D)
#define ADC_AWCRH sfrp(0x540E)
#define ADC_AWCRL sfrp(0x540F)

/* ADC bitmasks */

#define ADC_CSR_EOC (1 << 7)
#define ADC_CSR_AWD (1 << 6)
#define ADC_CSR_EOCIE (1 << 5)
#define ADC_CSR_AWDIE (1 << 4)
#define ADC_CSR_CH3 (1 << 3)
#define ADC_CSR_CH2 (1 << 2)
#define ADC_CSR_CH1 (1 << 1)
#define ADC_CSR_CH0 (1 << 0)

#define ADC_CR1_SPSEL2 (1 << 6)
#define ADC_CR1_SPSEL1 (1 << 5)
#define ADC_CR1_SPSEL0 (1 << 4)
#define ADC_CR1_CONT (1 << 1)
#define ADC_CR1_ADON (1 << 0)

#define ADC_CR2_EXTTRIG (1 << 6)
#define ADC_CR2_EXTSEL1 (1 << 5)
#define ADC_CR2_EXTSEL0 (1 << 4)
#define ADC_CR2_ALIGN (1 << 3)
#define ADC_CR2_SCAN (1 << 1)

#define ADC_CR3_DBUF (1 << 7)
#define ADC_CR3_DRH (1 << 6)

/* CPU */
#define CPU_A sfrp(0x7F00)
#define CPU_PCE sfrp(0x7F01)
#define CPU_PCH sfrp(0x7F02)
#define CPU_PCL sfrp(0x7F03)
#define CPU_XH sfrp(0x7F04)
#define CPU_XL sfrp(0x7F05)
#define CPU_YH sfrp(0x7F06)
#define CPU_YL sfrp(0x7F07)
#define CPU_SPH sfrp(0x7F08)
#define CPU_SPL  sfrp(0x7F09)
#define CPU_CCR  sfrp(0x7F0A)

// global configuration register
#define CFG_GCR  sfrp(0x7F60)

// interrupt control registers
#define ITC_SPR1  sfrp(0x7F70)
#define ITC_SPR2  sfrp(0x7F71)
#define ITC_SPR3  sfrp(0x7F72)
#define ITC_SPR4  sfrp(0x7F73)
#define ITC_SPR5  sfrp(0x7F74)
#define ITC_SPR6  sfrp(0x7F75)
#define ITC_SPR7  sfrp(0x7F76)
#define ITC_SPR8  sfrp(0x7F77)

/* SWIM, control and status register */
#define SWIM_CSR  sfrp(0x7F80)
/* debug registers */
#define DM_BK1RE  sfrp(0x7F90)
#define DM_BK1RH  sfrp(0x7F91)
#define DM_BK1RL  sfrp(0x7F92)
#define DM_BK2RE  sfrp(0x7F93)
#define DM_BK2RH  sfrp(0x7F94)
#define DM_BK2RL  sfrp(0x7F95)
#define DM_CR1  sfrp(0x7F96)
#define DM_CR2  sfrp(0x7F97)
#define DM_CSR1  sfrp(0x7F98)
#define DM_CSR2  sfrp(0x7F99)
#define DM_ENFCTR  sfrp(0x7F9A)

/* Interrupt Numbers */
#define INT_TLI 0
#define INT_AWU 1
#define INT_CLK 2
#define INT_EXTI0 3
#define INT_EXTI1 4
#define INT_EXTI2 5
#define INT_EXTI3 6
#define INT_EXTI4 7
#define INT_RES1 8
#define INT_RES2 9
#define INT_SPI 10
#define INT_TIM1_OVF 11
#define INT_TIM1_CCM 12
#define INT_TIM2_OVF 13
#define INT_TIM2_CCM 14
#define INT_TIM3_OVF 15
#define INT_TIM3_CCM 16
#define INT_RES3 17
#define INT_RES4 18
#define INT_I2C 19
#define INT_UART2_TX_COMPLETE 20
#define INT_UART2_RX_FULL 21
#define INT_ADC1 22
#define INT_TIM4_OVF 23
#define INT_FLASH 24

/* Interrupt Vectors */
#define INT_VECTOR_RESET 0x8000
#define INT_VECTOR_TRAP 0x8004
#define INT_VECTOR_TLI 0x8008
#define INT_VECTOR_AWU 0x800C
#define INT_VECTOR_CLK 0x8010
#define INT_VECTOR_EXTI0 0x8014
#define INT_VECTOR_EXTI1 0x8018
#define INT_VECTOR_EXTI2 0x801C
#define INT_VECTOR_EXTI3 0x8020
#define INT_VECTOR_EXTI4 0x8024
#define INT_VECTOR_SPI 0x8030
#define INT_VECTOR_TIM1_OVF 0x8034
#define INT_VECTOR_TIM1_CCM 0x8038
#define INT_VECTOR_TIM2_OVF 0x803C
#define INT_VECTOR_TIM2_CCM 0x8040
#define INT_VECTOR_TIM3_OVF 0x8044
#define INT_VECTOR_TIM3_CCM 0x8048
#define INT_VECTOR_I2C 0x8054
#define INT_VECTOR_UART2_TX_COMPLETE 0x8058
#define INT_VECTOR_UART2_RX_FULL 0x805C
#define INT_VECTOR_ADC1 0x8060
#define INT_VECTOR_TIM4_OVF 0x8064
#define INT_VECTOR_FLASH 0x8068

#define nointerrupts() {__asm sim __endasm;}
#define interrupts() {__asm rim __endasm;}
#define wait_for_interrupt() {\
    __asm \
    wfi\
    nop\
    nop\
 __endasm;}

// special function register bits clear/set
#define _clrbit(reg, mask) reg &= ~mask
#define _setbit(reg, mask) reg |= mask
#define _togglebit(reg,mask) reg ^= mask

#endif
