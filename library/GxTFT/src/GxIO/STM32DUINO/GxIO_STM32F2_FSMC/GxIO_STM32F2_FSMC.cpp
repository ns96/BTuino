// created by Jean-Marc Zingg to be the GxIO_STM32F2_FSMC io class for the GxTFT library
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
//
// for pin information see the backside of the TFT, for the data pin to port pin mapping see FSMC pin table STM32F207V doc.
//
//

#if defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_STM32L2)

#include "GxIO_STM32F2_FSMC.h"

//#include "stm32yyxx_ll_fsmc.h"
//#include "stm32yyxx_ll_rcc.h" 
SRAM_HandleTypeDef hsram1;
// TFT connector uses FSMC pins
// D0   D1   D2  D3  D4  D5  D6  D7   D8   D9   D10  D11  D12  D13 D14 D15
// PD14 PD15 PD0 PD1 PE7 PE8 PE9 PE10 PE11 PE12 PE13 PE14 PE15 PD8 PD9 PD10

// connector pins
// 01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32
// GND RST D15 D14 D13 D12 D11 D10 D9  D8  D7  D6  D5  D4  D3  D2  D1  D0  RD  WR  RS  CS  SCK SCS SI  SO  INT BLK SET GND 3.3 GND
//         D10 D9  D8  E15 E14 E13 E12 E11 E10 E9  E8  E7  D1  D0  D15 D14 D4  D5  D13 D7                      B1
																			

//#define CommandAccess ((uint32_t)0x60000000)
//#define DataAccess ((uint32_t)0x60800000)

#define CommandAccess ((uint32_t)0x60FFFFFE)
#define DataAccess ((uint32_t)0x61000000)

GxIO_STM32F2_FSMC::GxIO_STM32F2_FSMC(bool bl_active_high)
{
  _cs   = PD7;  // FSMC_NE1
  _rs   = PE2; // FSMC_A23
  _rst  = 0;    // not available, driven from NRST
  _wr   = PD5;  // FSMC_NWE
  _rd   = PD4;  // FSMC_NOE
  _bl   = PB1;
  _bl_active_high = bl_active_high;
}

void GxIO_STM32F2_FSMC::reset()
{
  // _rst pin not available
}

void GxIO_STM32F2_FSMC::init()
{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
//LL_AHB1_GRP1_PERIPH_GPIOA
//LL_AHB1_GRP1_PERIPH_GPIOB
//LL_AHB1_GRP1_PERIPH_GPIOC
//LL_AHB1_GRP1_PERIPH_GPIOD
//LL_AHB1_GRP1_PERIPH_GPIOE
//LL_AHB1_GRP1_PERIPH_SRAM1
//LL_AHB3_GRP1_PERIPH_FSMC

	GPIO_InitTypeDef GPIO_InitStruct ={0};
	__HAL_RCC_FSMC_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	
	
	  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9 
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	
	
  FSMC_NORSRAM_TimingTypeDef Timing = {0};
  FSMC_NORSRAM_TimingTypeDef ExtTiming = {0};	
	
  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 0x01;
  Timing.AddressHoldTime = 0x00;
  Timing.DataSetupTime = 0x0f;
  Timing.BusTurnAroundDuration = 0x00;
  Timing.CLKDivision = 0x00;
  Timing.DataLatency = 0x00;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */
  ExtTiming.AddressSetupTime = 0x00;
  ExtTiming.AddressHoldTime = 0x00;
  ExtTiming.DataSetupTime = 0x03;
  ExtTiming.BusTurnAroundDuration = 0x00;
  ExtTiming.CLKDivision = 0x00;
  ExtTiming.DataLatency = 0x00;
  ExtTiming.AccessMode = FSMC_ACCESS_MODE_A;
  
   if (HAL_SRAM_Init(&hsram1, &Timing, &ExtTiming) != HAL_OK)
  {
    
  }
  
	HAL_SRAM_WriteOperation_Enable(&hsram1);

  digitalWrite(_bl, LOW);
  pinMode(_bl, OUTPUT);
}

uint8_t GxIO_STM32F2_FSMC::readDataTransaction()
{	
  return *(uint8_t*)DataAccess;
}

uint16_t GxIO_STM32F2_FSMC::readData16Transaction()
{
  return *(uint16_t*)DataAccess;
}

uint8_t GxIO_STM32F2_FSMC::readData()
{
  return *(uint8_t*)DataAccess;
}

uint16_t GxIO_STM32F2_FSMC::readData16()
{
  return *(uint16_t*)DataAccess;

}

uint32_t GxIO_STM32F2_FSMC::readRawData32(uint8_t part)
{
  return *(uint16_t*)DataAccess;
}

void GxIO_STM32F2_FSMC::writeCommandTransaction(uint8_t c)
{
  *(uint8_t*)CommandAccess = c;
}

void GxIO_STM32F2_FSMC::writeCommand16Transaction(uint16_t c)
{
  *(uint16_t*)CommandAccess = c;
}

void GxIO_STM32F2_FSMC::writeDataTransaction(uint8_t d)
{
  *(uint8_t*)DataAccess = d;
}

void GxIO_STM32F2_FSMC::writeData16Transaction(uint16_t d, uint32_t num)
{
  while (num > 0)
  {
	*(uint16_t*)DataAccess = d;
    num--;
  }
}

void GxIO_STM32F2_FSMC::writeCommand(uint8_t c)
{
  *(uint8_t*)CommandAccess = c;
}

void GxIO_STM32F2_FSMC::writeCommand16(uint16_t c)
{
  *(uint16_t*)CommandAccess = c;
}

void GxIO_STM32F2_FSMC::writeData(uint8_t d)
{
  *(uint8_t*)DataAccess = d;
}

void GxIO_STM32F2_FSMC::writeData(uint8_t* d, uint32_t num)
{
  while (num > 0)
  {
    *(uint8_t*)DataAccess = *d;
    d++;
    num--;
  }
}

void GxIO_STM32F2_FSMC::writeData16(uint16_t d, uint32_t num)
{
  while (num > 0)
  {
    *(uint16_t*)DataAccess = d;
    num--;
  }
}

void GxIO_STM32F2_FSMC::writeAddrMSBfirst(uint16_t d)
{
  writeData16(d >> 8);
  writeData16(d & 0xFF);
}

void GxIO_STM32F2_FSMC::startTransaction()
{
}

void GxIO_STM32F2_FSMC::endTransaction()
{
}

void GxIO_STM32F2_FSMC::selectRegister(bool rs_low)
{
}

void GxIO_STM32F2_FSMC::setBackLight(bool lit)
{
  digitalWrite(_bl, (lit == _bl_active_high));
}

#endif
