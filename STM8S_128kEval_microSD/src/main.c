/**
  ******************************************************************************
  * @file main.c
  * @brief Demonstrate decode and play of IMA ADPC data stored on .
  * @author STMicroelectronics - MCD Application Team Prague
  * @version V0.0.1
  * @date 05/03/2010
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2008 STMicroelectronics</center></h2>
  * @image html logo.bmp
  ******************************************************************************
  */

#include "stm8s.h"
#include "adpcm.h"
#include "microsd.h"

#ifdef __CSMC__ /* COSMIC */
	@near u8 circSampleBuffer[MAX_CIRC_BUFF];
	@near u8 microSDBuff[BLOCK_SIZE];
#else /* _RAISONANCE_ */
	u8 data circSampleBuffer[MAX_CIRC_BUFF];
	u8 data microSDBuff[BLOCK_SIZE];
#endif /* _COSMIC_ */

vu16 firstToRead = 0;
vu16 nextToWrite = 0;

//-----------------------------------------------------------------------------
void Delay(u16 nCount)
//-----------------------------------------------------------------------------
{
    // Decrement nCount value
    while (nCount != 0)
    {
        nCount--;
    }
}


//-----------------------------------------------------------------------------
void ClockInit (void)
//-----------------------------------------------------------------------------
{
	// HSI 16 MHz
	CLK->CKDIVR = 0x00; CLK->CKDIVR |= 0x00;
	return;
}


//-----------------------------------------------------------------------------
void TIM1_Init (void)
//-----------------------------------------------------------------------------
{
    // control registers
    TIM1->CR1 = 0b10000000; //0b11100000
    
		// prescaler to fclk/1
    TIM1->PSCRH = 0x00;
		TIM1->PSCRL = 0x00;
    
		// auto-reload value to 0x05AB -> f = 11026.878 Hz
    // auto-reload value to 0x07D0 -> f = 8000 Hz
		// auto-reload value to 0x03E8 -> f = 16000 Hz
		// TIM2->ARRH = 0x02; TIM2->ARRL = 0xD5;
    TIM1->ARRH = 0x00; TIM1->ARRL = 0xFF;
    // TIM2->ARRH = 0x03; TIM2->ARRL = 0xE8;
		 
		TIM1->RCR = 0x03; // every fourth PWN half period will be updated i.e. 16MHz/256/4
		//TIM1->RCR = 0x02; // every third PWN half period will be updated i.e. 16MHz/256/3
		
		// capture/compare enable registers
    TIM1->CCER1 = 0x00;
    TIM1->CCER2 = 0x00;
		
    // capture/compare mode registers (CC3, CC4 to PWM mode 1, preload enabled)
    TIM1->CCMR1 = 0b00000000;
    TIM1->CCMR2 = 0b00000000;
    TIM1->CCMR3 = 0b01101000;
		TIM1->CCMR4 = 0b01101000;

		//clear the counter
    TIM1->EGR |= 0b00100001;

		// clear status registers
    TIM1->SR1 = 0x00;
    TIM1->SR2 = 0x00;

    // enable update interrupt (overflow)
    TIM1->IER = 0b00000001;

    // enable CC3, CC4 output
    SetBit(TIM1->CCER2,0);
		SetBit(TIM1->CCER2,4);

    // capture/compare registers (CC1 PWM duty 50%)
    TIM1->CCR1H = 0x00; TIM1->CCR1L = 0x80;
    TIM1->CCR2H = 0x00; TIM1->CCR2L = 0x80;
    TIM1->CCR3H = 0x00; TIM1->CCR3L = 0x80;
		TIM1->CCR4H = 0x00; TIM1->CCR2L = 0x80;
		
		TIM1->BKR |= 0x80;

    // start the timer
    SetBit(TIM1->CR1,0);
    return;
}

//-----------------------------------------------------------------------------
u8 MSD_ReadAudioBlock(u8 *pBuffer)
//-----------------------------------------------------------------------------
{
  u16 i = 0;
  u8 rvalue = MSD_RESPONSE_FAILURE;
	static u32 Address=0;
  
    // Send CMD17 (MSD_READ_SINGLE_BLOCK) to read one block
    MSD_SendCmd (MSD_READ_SINGLE_BLOCK, Address, 0xFF);
    // Check if the MSD acknowledged the read block command: R1 response (0x00: no errors)
    if (MSD_GetResponse(MSD_RESPONSE_NO_ERROR))
    {
      return  MSD_RESPONSE_FAILURE;
    }
    // Now look for the data token to signify the start of the data
    if (!MSD_GetResponse(MSD_START_DATA_SINGLE_BLOCK_READ))
    {
      // Read the MSD block data : read NumByteToRead data
      for (i = 0; i < BLOCK_SIZE; i++)
      {
        // Read the pointed data
        *pBuffer = MSD_ReadByte();
        // Point to the next location where the byte read will be saved
        pBuffer++;
      }
      // Set next read address
      Address += BLOCK_SIZE;
      // get CRC bytes (not really needed for application, but required by MSD)
      MSD_ReadByte();
      MSD_ReadByte();
      // Set response value to success 
      rvalue = MSD_RESPONSE_NO_ERROR;
    }
    else
    {
      // Set response value to failure
      rvalue = MSD_RESPONSE_FAILURE;
    }
  return rvalue;
}

//-----------------------------------------------------------------------------
void main(void)
//-----------------------------------------------------------------------------
{
	u8 cardStatus;
	
	firstToRead = 0;
	nextToWrite = 0;

	ClockInit();
	TIM1_Init();

	GPIOB->DDR |= (0x01);
	GPIOB->CR1 |= (0x01);   
	GPIOB->CR2 |= (0x01);

  /*********************** SPI and MicroSD initialization ******************/

	SPI_DeInit();

  // Init the SPI in the fast communication fmaster/2 
  SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_HIGH, SPI_CLOCKPHASE_2EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);

  SPI_Cmd(ENABLE);
  while (MSD_Detect() == MICROSD_NOT_PRESENT)
  {
      // Wait MicroSD card insertion
  }

  Delay(0xFFFF);
  // Init the micro SD flash
  cardStatus = MSD_Init();

  initDecoder();
  // decode first samples and put it to the circular buffer

  // MSD chip select low
  MSD_ChipSelect(ENABLE);

	cardStatus = MSD_ReadAudioBlock( &circSampleBuffer[nextToWrite] );
	while (cardStatus != 0){} // locked here? Something wrong with SD card - Please, replace it by error handler
	
	nextToWrite = 512;
	firstToRead = 0x00;
	rim(); // start the interrupt decoder routine
	

	for(;;){ // endless reading - put here some limit, according to length of data stream in SD card

		while (firstToRead >= 512) {
			nop();
		} //wait till the higher half of buffer will be released
		cardStatus = MSD_ReadAudioBlock( &circSampleBuffer[nextToWrite] );
		while (cardStatus != 0){} // locked here? Something wrong with SD card - Please, replace it by error handler
		nextToWrite = 0; // next time will be filled lower half of buffer

		while (firstToRead < 512) {
			nop();
		} //wait till the lower half of buffer will be released
		cardStatus = MSD_ReadAudioBlock( &circSampleBuffer[nextToWrite] );
		while (cardStatus != 0){} // locked here? Something wrong with SD card - Please, replace it by error handler
		nextToWrite = 512; // next time will be filled higher half of buffer
		
	}
}