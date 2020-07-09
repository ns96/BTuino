# Arduino STM32DUINO support for BIGTREETECH TFT35_E3_V3.0 board(BIGTREE_F207VCT6)

board tested on STM32DUINO core library, version 1.9.0.
Arduino IDE 1.8.12 and 1.8.13 

# Installation

1. Install Arduino core support for STM32 based boards.
	https://github.com/stm32duino/wiki/wiki/Getting-Started

2. Go to the source files directory of the STM32 core.  
Source files directory can found here https://github.com/stm32duino/wiki/wiki/Where-are-sources#stm32-core-sources-files-location <br>
examples:<br>
- windows 10 path - %AppData%\Local\Arduino15\packages\STM32\hardware\stm32\1.9.0\
- Linux path - /home/\<USERNAME\>/.arduino15/packages/STM32/hardware/stm32/1.9.0/   
- Mac path - /Users/\<USERNAME\>/Library/Arduino15/packages\STM32\hardware\stm32\1.9.0\
where "1.9.0" is version of core library.  
Copy board directory 'BIGTREE_F207VCT6' with files to 'variants' directory.

	
3. Add this lines to board.txt file
	%AppData%\Local\Arduino15\packages\STM32\hardware\stm32\1.9.0\board.txt

```
#BIGTREE_F207VCT6 board
3dprinter.menu.pnum.BIGTREE_F207VC=BIGTREE F207VCT6
3dprinter.menu.pnum.BIGTREE_F207VC.upload.maximum_size=262144
3dprinter.menu.pnum.BIGTREE_F207VC.upload.maximum_data_size=131072
3dprinter.menu.pnum.BIGTREE_F207VC.build.mcu=cortex-m3
3dprinter.menu.pnum.BIGTREE_F207VC.build.board=BIGTREE_F207VC
3dprinter.menu.pnum.BIGTREE_F207VC.build.series=STM32F2xx
3dprinter.menu.pnum.BIGTREE_F207VC.build.product_line=STM32F207xx
3dprinter.menu.pnum.BIGTREE_F207VC.build.variant=BIGTREE_F207VC
3dprinter.menu.pnum.BIGTREE_F207VC.build.cmsis_lib_gcc=arm_cortexM3l_math

```

4. Restart Arduino IDE program. Go to 'boards manager' and select '3D printer boards'.
Select "board part number" - BIGTREE_F207VCT6
	


# Using board hardware

Pins that can be used in projects can be found in docs/pins-names.jpg.
(Please note that all connectors are displayed on the LCD side. )

Some board hardware pins can be found on board connectors (EXP1, EXP2,EXP3), so if you using them as digital outputs you can't use board hardware connected to them.


**Warning! Before flashing board with Arduino backup your board memory with ST-link utility.
After flashing sketches you can`t restore board firmware from SD card. Use ST-link for restore. 
In dump folder placed working dump of board memory.**



# Board hardware
## Serial interface on UART4 connector on the board
pins:
```
 PC11 SERIAL_RX           
 PC10 SERIAL_TX           
```

 Can be used as standart Arduino serial output :   
 Serial.begin(115200);   
 Serial.println("Test");  

## Buzzer 
pin: 
```
PD12 BUZZER_PIN 
```
You can use standart arduino function tone(PD13, Note, noteDuration);

example:  
example/toneMelody/toneMelody.ino



## LCD
 LCD connected to 16 bit paralel port in FSMC mode.

pins:
```
PD12 - LCD backlight brightness.
```
Brightness can be controlled by :
 ```
 int brightness = xx; where xx from 0 to 255
 pinMode(PD12, OUTPUT);
 analogWrite(PD12, brightness);
 or 
 digitalwrite(PD12,HIGH); for 100% brightness

This pin has alternative name LED_BUILTIN.
```

Install library Adafruit_TFTLCD_16bit_STM32 or GxTFT from library folder.
(Adafruit_TFTLCD_16bit_STM32 modifyed for supporting this board. 
In GxTFT library added support for this board)

example:  
GxTFT library:  
 example/GxTFT-TFT35-E3_graphicstest/GxTFT-TFT35-E3_graphicstest.ino
 
Adafruit_TFTLCD_16bit_STM32 library:  
 example/Adafruit_TFTLCD_TFT35-E3-graphicstest/Adafruit_TFTLCD_TFT35-E3-graphicstest.ino

FSMC GPIO Configuration, these pins can`t be used in sketches  
 ```
  PE2   ------> FSMC_A23
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10   ------> FSMC_D7
  PE11   ------> FSMC_D8
  PE12   ------> FSMC_D9
  PE13   ------> FSMC_D10
  PE14   ------> FSMC_D11
  PE15   ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10   ------> FSMC_D15
  PD14   ------> FSMC_D0
  PD15   ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PD4   ------> FSMC_NOE
  PD5   ------> FSMC_NWE
  PD7   ------> FSMC_NE1
 ```
  
## Touchscreen
Touchscreen connected to XPT2046 chip via software SPI interface.

Install library SoftSPIB, available in Arduino Library Manager(https://github.com/red-scorp/SoftSPIB).
Install library XPT2046_Touchscreen_SWSPI (fork of XPT2046_Touchscreen Paul Stoffregen library https://github.com/PaulStoffregen/XPT2046_Touchscreen ).

example:  
examples/TouchTest/TouchTest.ino

pins can be used in other libraries or sketches
```
PC13 XPT2046_TPEN 	
PE3	 XPT2046_MOSI
PE4	 XPT2046_MISO
PE5	 XPT2046_SCK 
PE6	 XPT2046_CS 
```

## Sdcard connector 
Install Adafruit_SPIFlash from Arduino Library Manager(also will be installed "SdFat_-_Adafruit_Fork" library)
SD card can work with standart Arduino library "SD" via default "SPI" interface.(https://www.arduino.cc/en/reference/SD)

Note: Card must be formatted in fat filesystem. Use Sdcart formatter from utilites folder.
(SDCardFormatterv5_WinEN.zip)


pins:
```
PC4  CARD DETECT PIN
PA4  SPI CS_PIN
PA5  SPI SCK_PIN 
PA6  SPI MISO_PIN 
PA7  SPI MOSI_PIN 
```

using spi interface in Adafruit_SPIFlash library:
```
SdFat sd(&SPI);
#define SD_CS PA4
...
//some code
...
sd.begin(SD_CS, SD_SCK_MHZ(50));
```


example:  
examples/SdInfo/SdInfo.ino
examples/CardInfo/CardInfo.ino for SD library



## W25Q64 flash                  
 Flash chip connected via hardware SPI3 interface
 My board has BoyaMicro BY25Q64AS 8MiB SPI flash. At now Adafruit_SPIFlash library(version 3.2.0) does not support him.
 
 
 At first test your flash chip. 
 run sketch 
 examples/flashinfo/flashinfo.ino

Serial output must be look like:
```
Adafruit Serial Flash Info example
JEDEC ID: 684017
Flash size: 8388608

```
if you see "Flash size: 0" that meat that your flash chip does not supported 
Lets add support of "JEDEC ID: 684017" chip if you have same.

1. open Arduino libraries folder, search Adafruit_SPIFlash library folder. Open file
"flash_devices.h" and add lines at the end of the file before last line "#endif // MICROPY_INCLUDED_ATMEL_SAMD_EXTERNAL_FLASH_DEVICES_H"

End of file will looks like this:
```
// Settings for the BoyaMicro BY25Q64AS 8MiB SPI flash. 
//Datasheet: https://datasheet.lcsc.com/szlcsc/1904091402_BOYAMICRO-BY25Q64ASSIG_C383793.pdf
#define BY25Q64AS                                                            \
  {                                                                            \
    .total_size = (1 << 23), /* 8 MiB */                                       \
        .start_up_time_us = 5000, .manufacturer_id = 0x68,                     \
    .memory_type = 0x40, .capacity = 0x17, .max_clock_speed_mhz = 120,         \
    .quad_enable_bit_mask = 0x00, .has_sector_protection = false,              \
    .supports_fast_read = true, .supports_qspi = false,                         \
    .supports_qspi_writes = false, .write_status_register_split = false,        \
    .single_status_byte = false,                                               \
  }

#endif // MICROPY_INCLUDED_ATMEL_SAMD_EXTERNAL_FLASH_DEVICES_H
```

2. Open file "Adafruit_SPIFlashBase.cpp" and after line 40 add "BY25Q64AS," 
Block of code will looks like :

```
/// List of all possible flash devices used by Adafruit boards
static const SPIFlash_Device_t possible_devices[] = {
    // Main devices used in current Adafruit products
    GD25Q16C,
    GD25Q64C,
    S25FL116K,
    S25FL216K,

    // Only a handful of production run
    W25Q16FW,
    W25Q64JV_IQ,

    // Nordic PCA10056
    MX25R6435F,

    // Other common flash devices
    W25Q16JV_IQ,
	BY25Q64AS,
};

```
Than reflash flashinfo.ino sketch and check that size greater than zero.

Also in library folder placed modified library. Just install it. 
 
 
pins:
```
PB6 PIN_SPI_SS              
PB5 PIN_SPI_MOSI            
PB4 PIN_SPI_MISO            
PB3 PIN_SPI_SCK             
```
using spi interface in Adafruit_SPIFlash library:
 ```
 //define spi interface and flash transport
 SPIClass mflashSPI(PB5,PB4,PB3);
 Adafruit_FlashTransport_SPI flashTransport(PB6, &mflashSPI);
 
 // now you can use flash
 Adafruit_SPIFlash flash(&flashTransport);
 ```

now you can format flash in fatfs filesystem.
examples/SdFat_format/SdFat_format.ino 

and use it for storing files
examples/SdFat_full_usage/SdFat_full_usage.ino

You can use both SD card and flash in your sketces
examples/flash_manipulator/flash_manipulator.ino


##Rotary encoder

pins:
```
PC8 Button
PA8 ENCA 
PC9 ENCB 
```


## USB port


## WS2812
 Board has 4 NEOPIXEL PIXELS
 pin:
 ```
 PC7 
 ```
 Install "Adafruit_NeoPixel" library from Library Manager.
 Define pin and neopixels number
 ```
 // Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PC7 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size
 ```
 examples/neopixel-simple/neopixel-simple.ino
