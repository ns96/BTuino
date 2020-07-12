/*
 *******************************************************************************
 * Copyright (c) 2017, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define   PC7	0
#define   PC6	1
#define   PB13	2
#define   PB14	3
#define   PB15	4
#define   PB12	5
#define   PD13	6
#define   PC8	7
#define   PC4	A6
#define   PC9	9
#define   PA7	A5
#define   PA8	11
#define   PA4	A2
#define   PA6	A4
#define   PA5	A3
#define   PA9	15
#define   PD3	16
#define   PD2	17
#define   PA10	18
#define   PA2	A0
#define   PA3	A1
#define   PC12	21
#define   PC11	22
#define   PC10	23
#define   PA15	24
#define   PB11	25
#define   PB10	26
#define   PD12	27
#define   PD7	28
#define   PE2	29
#define   PD4	30
#define   PD5	31
#define   PB1	32

//XPT2046 pins
#define   PC13	33
#define   PE3	34
#define   PE4	35
#define   PE5	36
#define   PE6	37

//SPI FLASH , SPI3
#define   PB3	38
#define   PB4	39
#define   PB5	40
#define   PB6	41

// This must be a literal
#define NUM_DIGITAL_PINS 		42
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       7

// On-board user button
#define USER_BTN                PC8

#define LED_BUILTIN				PD12


//SD card
#define SD_DETECT_PIN			PC4
// SPI Definitions

#define PIN_SPI_SS              PA4
#define PIN_SPI_MOSI            PA7
#define PIN_SPI_MISO            PA6
#define PIN_SPI_SCK             PA5

/*
#define PIN_SPI_SS              PB6
#define PIN_SPI_MOSI            PB5
#define PIN_SPI_MISO            PB4
#define PIN_SPI_SCK             PB3
*/


// I2C Definitions
// (the same pins as UART3)
#define PIN_WIRE_SDA            PB11
#define PIN_WIRE_SCL            PB10

// Timer Definitions
#define TIMER_TONE              TIM3
//#define TIMER_SERVO             TIM7

// UART Definitions
#define SERIAL_UART_INSTANCE    4 
// Default pin used for 'Serial' instance (ex: ST-Link)
// Mandatory for Firmata
//#define PIN_SERIAL_RX           PC11
//#define PIN_SERIAL_TX           PC10

/* Enable Serial */
#define HAVE_HWSERIAL1
#define HAVE_HWSERIAL2
#define HAVE_HWSERIAL3
#define HAVE_HWSERIAL4

#define PIN_SERIAL1_RX           PA10
#define PIN_SERIAL1_TX           PA9

#define PIN_SERIAL2_RX           PA3
#define PIN_SERIAL2_TX           PA2

#define PIN_SERIAL3_RX           PB11
#define PIN_SERIAL3_TX           PB10

#define PIN_SERIAL4_RX           PC11
#define PIN_SERIAL4_TX           PC10




/* Extra HAL modules */
//#define HAL_DAC_MODULE_ENABLED
//#define HAL_ETH_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED 
#define HAL_SRAM_MODULE_ENABLED
#define HAL_FSMC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED 
#define HAL_TIM_MODULE_ENABLED

#define HSE_VALUE 8000000U
				   


#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
