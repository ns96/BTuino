#ifndef _SRAM_H_
#define _SRAM_H_ 

#include "stm32f2xx_hal_gpio.h"
#include "stm32f2xx_hal_rcc.h"
#include "stm32yyxx_ll_fsmc.h"
#include "stm32f2xx_hal_dma.h"
#include "stm32f2xx_hal_sram.h"


#ifdef __cplusplus
extern "C"{
#endif 

//#define FSMC_BANK1                      ((void*)0x60000000) 



/*
 * SRAM/NOR Flash routines
 */
extern volatile uint16_t * fsmcData;
extern volatile uint16_t * fsmcCommand;


void fsmc_lcd_init(void); 
static void HAL_FSMC_MspInit(void);
static void FSMC_Init(void);





#ifdef __cplusplus
} /* extern "C" */
#endif


#endif