# Arduino STM32DUINO support for BIGTREETECH TFT35_E3_V3.0 board(BIGTREE_F207VCT6)

Board tested with STM32DUINO core library, version 1.9.0.
Arduino IDE 1.8.12 and 1.8.13

# Table of Contents

<!-- MarkdownTOC autolink="true" levels="1,2" -->

- [Installation](#installation)
- [Using board hardware](#using-board-hardware)
- [Board Hardware](#board-hardware)
  - [Serial interface on UART4 connector](#serial-interface-on-uart4-connector)
  - [Buzzer](#buzzer)
  - [LCD](#lcd)
  - [Touchscreen](#touchscreen)
  - [SDcard Connector](#sdcard-connector)
  - [W25Q64 flash](#w25q64-flash)
  - [Rotary encoder](#rotary-encoder)
  - [USB port](#usb-port)
  - [WS2812](#ws2812)

<!-- /MarkdownTOC -->


# Installation

1. Install Arduino core support for STM32 based boards.
	https://github.com/stm32duino/wiki/wiki/Getting-Started

2. Go to the source files directory of the STM32 core.  
Source files directory can be found here https://github.com/stm32duino/wiki/wiki/Where-are-sources#stm32-core-sources-files-location <br>

Examples:
- windows 10 path - %AppData%\Local\Arduino15\packages\STM32\hardware\stm32\1.9.0\
- Linux path - /home/\<USERNAME\>/.arduino15/packages/STM32/hardware/stm32/1.9.0/   
- Mac path - /Users/\<USERNAME\>/Library/Arduino15/packages/STM32/hardware/stm32/1.9.0/

where "1.9.0" is version of core library.  

3. Copy file "boards.local.txt" to the STM32 core source files directory (see above).

4. Copy board directory 'BIGTREE_F207VCT6' with files to the 'variants' subdirectory.

5. Restart Arduino IDE. Go to Tools -> Board:... -> 'Boards manager' and select '3D printer boards'.
Select Tools -> 'Board part number:' -> BIGTREE_F207VCT6
6. Check Tools -> Upload method, should be set to "STM32Cube programmer(SWD)"
7. Download and install "STM32Cube programmer" from https://www.st.com/en/development-tools/stm32cubeprog.html
Arduino IDE uses it to upload sketches to the board. (see the following instructions for MacOS: https://community.st.com/s/question/0D50X0000BmnqrB/how-to-run-stm32cubeprogrammer-on-macos-catalina-10151-19b88)

# Using board hardware

Pins that can be used in projects can be found in [pins-names.jpg](docs/pins-names.jpg).
(Please note that all connectors are displayed on the LCD side)

Some board hardware pins can be found on board connectors (EXP1, EXP2, EXP3), so if you us them as digital outputs you can't use board hardware connected to them.

Board supports flashing over ST-LINK debugger and programmer over SWD interface.  
(https://www.st.com/en/development-tools/st-link-v2.html)  
Driver (https://www.st.com/en/development-tools/stsw-link009.html)  
ST-LINK utility (https://www.st.com/en/development-tools/stsw-link004.html)  

You need to connect ST-LINK programmer (pins GND, SWDIO, SWCLK, 3.3V) to SWD connector on the board.
Board can be powered from ST-LINK programmer via 3.3V pin without external power adapter for programming purposes.
When using external power adapter you should disconnect 3.3V pin.

**Warning! Before flashing board with Arduino backup your board flash with ST-LINK utility.
After flashing sketches you will not be able to restore board's original firmware from SD card because original board's bootloader will be overwritten. 
Use ST-LINK to restore it if you need to go back to the original firmware.**

How to backup board's flash: 
```
1. Connect board to ST-LINK programmer and run ST-LINK utility.
2. Click "Target" -> "Connect" 
3. In field "Address" you should see "0x08000000" . In field "Size" paste "0x40000" and press enter.
4. After that ST-LINK reads controller flash memory to ST-LINK Utility.
5. Now save memory to file. Click "File" -> "Save file as..". Paste filename and press "Save" button.

```


# Board Hardware
## Serial interface on UART4 connector
Pins:
```
PC11 SERIAL_RX           
PC10 SERIAL_TX           
```

Can be used as standard [Arduino serial](https://www.arduino.cc/reference/en/language/functions/communication/serial/) port:   
```
Serial.begin(115200);   
Serial.println("Test");  
```

## Buzzer 
Pin: 
```
PD13 BUZZER_PIN 
```
Standard Arduino function can be used: 
```
tone(PD13, Note, noteDuration);
```

Example:
[examples/toneMelody/toneMelody.ino](examples/toneMelody/toneMelody.ino)



## LCD
 LCD is connected to 16 bit paralel port in FSMC (Flexible Static Memory Controller) mode. More details here: [STM32L4_Memory_FSMC.pdf](https://www.st.com/content/ccc/resource/training/technical/product_training/e0/de/1c/48/51/a9/4e/2e/STM32L4_Memory_FSMC.pdf/files/STM32L4_Memory_FSMC.pdf/jcr:content/translations/en.STM32L4_Memory_FSMC.pdf)

Pins:
```
PD12 LED_BUILTIN # LCD backlight brightness control
```
Brightness can be controlled by :
 ```
 int brightness = xx; where xx from 0 to 255
 pinMode(PD12, OUTPUT);
 analogWrite(PD12, brightness);
 or 
 digitalwrite(PD12, HIGH); for 100% brightness
```
Board is supported by two libraries: modified Adafruit_TFTLCD_16bit_STM32 and GxTFT(support of this board is added).
Both libraries fully support LCD. If you have experience of any of them you can use it.  
1. Adafruit_TFTLCD_16bit_STM32 library uses [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) (This is the core graphics library for all Adafruit displays, providing a common set of graphics primitives (points, lines, circles, etc.). So you can easy migrate your sketches with Adafruit displays to this board.  
2. GxTFT library separates the aspects of IO connection, controller type and display class into separate C++ classes. The purpose of this Library and its design is to make additions easy. But Author of the GxTFT recommends to use the Adafruit libraries whenever possible, as these are better supported 

Original libraries:  
[Adafruit_TFTLCD_16bit_STM32](https://github.com/stevstrong/Adafruit_TFTLCD_16bit_STM32)  
[GxTFT](https://github.com/ZinggJM/GxTFT)  

### 1. Adafruit_TFTLCD_16bit_STM32

Install "Adafruit GFX" and "Adafruit BusIO" libraries from Arduino Library Manager.  
Install [modified Adafruit_TFTLCD_16bit_STM32](library/Adafruit_TFTLCD_16bit_STM32/)  
[how-to-install](https://www.arduino.cc/en/guide/libraries#toc5)

Example:  
[examples/Adafruit_TFTLCD_TFT35-E3-graphicstest/Adafruit_TFTLCD_TFT35-E3-graphicstest.ino](examples/Adafruit_TFTLCD_TFT35-E3-graphicstest/Adafruit_TFTLCD_TFT35-E3-graphicstest.ino)
 
 ### 2. GxTFT

Install [modified GxTFT](library/GxTFT/)
[how-to-install](https://www.arduino.cc/en/guide/libraries#toc5)

Example:  
[examples/GxTFT-TFT35-E3_graphicstest/GxTFT-TFT35-E3_graphicstest.ino](examples/GxTFT-TFT35-E3_graphicstest/GxTFT-TFT35-E3_graphicstest.ino)
 

### FSMC GPIO Configuration

The following pins are already configured in libraries and they can`t be used in sketches:
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
Touchscreen is connected to XPT2046 chip via software SPI interface.

Install library [SoftSPIB](https://github.com/red-scorp/SoftSPIB) from Arduino Library Manager.
Install library [XPT2046_Touchscreen_SWSPI](library/XPT2046_Touchscreen_SWSPI/) (fork of XPT2046_Touchscreen library by Paul Stoffregen https://github.com/PaulStoffregen/XPT2046_Touchscreen).
[how-to-install](https://www.arduino.cc/en/guide/libraries#toc5)

Example:  
[examples/TouchTest/TouchTest.ino](examples/TouchTest/TouchTest.ino)

Pins: (can be used in other libraries or sketches if touchscreen is not used)
```
PC13  XPT2046_TPEN 	
PE3   XPT2046_MOSI
PE4   XPT2046_MISO
PE5   XPT2046_SCK 
PE6   XPT2046_CS 
```

## SDcard Connector 
Install library 'Adafruit_SPIFlash' from Arduino Library Manager ("SdFat_-_Adafruit_Fork" library will also be installed).
SD card can work with standard Arduino library ["SD"](https://www.arduino.cc/en/reference/SD) via default "SPI" interface.

Note: Card must be formatted in FAT16 or FAT32 filesystem. Use SDcard formatter from utilites [SDCardFormatterv5_WinEN](utilites/SDCardFormatterv5_WinEN.zip)


Pins:
```
PC4  CARD DETECT PIN
PA4  SPI CS_PIN
PA5  SPI SCK_PIN 
PA6  SPI MISO_PIN 
PA7  SPI MOSI_PIN 
```

Using SPI interface in Adafruit_SPIFlash library:
```
SdFat sd(&SPI);
#define SD_CS PA4
...
//some code
...
sd.begin(SD_CS, SD_SCK_MHZ(50));
```


Examples:  
1. [examples/SdInfo/SdInfo.ino](examples/SdInfo/SdInfo.ino)
2. [examples/CardInfo/CardInfo.ino](examples/CardInfo/CardInfo.ino)


## W25Q64 flash
Flash chip is connected via hardware SPI3 interface.  
My board has BoyaMicro BY25Q64AS 8MByte SPI flash. Adafruit_SPIFlash library(version 3.2.0) does not support it.

1. Install library Adafruit_SPIFlash from Arduino Library Manager("SdFat - Adafruit Fork" will be installed too)
 
 At first test your flash chip.
 Run sketch: [examples/flashinfo/flashinfo.ino](examples/flashinfo/flashinfo.ino)

Serial console output should look like the following:
```
Adafruit Serial Flash Info example
JEDEC ID: 684017
Flash size: 8388608

```
If you see "Flash size: 0" that means that your flash chip is not supported.
Proceed to the following section to add support of "JEDEC ID: 684017" chip if you have the same.

2. Adding support of "JEDEC ID: 684017" chip.
Replace files for this version of library or update your version of library manually (use any of the following options): 

a. Replace files of Adafruit_SPIFlash library from [updated Adafruit_SPIFlash library](library/Adafruit_SPIFlash/) in Arduino libraries directory according to the [how-to](https://www.arduino.cc/en/guide/libraries#toc5)

b. Manual adding support of chip.  

Open Arduino libraries folder, search Adafruit_SPIFlash library folder. Open file
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

Open file "Adafruit_SPIFlashBase.cpp" and after line 40 add "BY25Q64AS," 
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

3. Reflash flashinfo.ino sketch and check that flash size is greater than zero.

Pins:
```
PB6 PIN_SPI_SS              
PB5 PIN_SPI_MOSI            
PB4 PIN_SPI_MISO            
PB3 PIN_SPI_SCK             
```
Using SPI interface in Adafruit_SPIFlash library:
 ```
 //define spi interface and flash transport
 SPIClass mflashSPI(PB5,PB4,PB3);
 Adafruit_FlashTransport_SPI flashTransport(PB6, &mflashSPI);
 
 // now you can use flash
 Adafruit_SPIFlash flash(&flashTransport);
 ```

Format flash with fatfs filesystem:
[examples/SdFat_format/SdFat_format.ino](examples/SdFat_format/SdFat_format.ino) 

Use it for storing files:
[examples/SdFat_full_usage/SdFat_full_usage.ino](examples/SdFat_full_usage/SdFat_full_usage.ino)

You can use both SD card and flash in your sketches:
[examples/flash_manipulator/flash_manipulator.ino](examples/flash_manipulator/flash_manipulator.ino)


## Rotary encoder

Pins:
```
PC8 Button
PA8 ENCA 
PC9 ENCB 
```

Example:
[examples/encoder_test/encoder_test.ino](examples/encoder_test/encoder_test.ino)


## USB port
STM32DUINO supports STM32 as a USB device, for example, "Serial port or HID device(mouse and keyboard)".

Use Tools -> USB Support -> CDC (Generic Serial)


## WS2812
 Board has 4 NEOPIXEL RGB LEDs
 
 Pin:
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
Example:
[examples/neopixel-simple/neopixel-simple.ino](examples/neopixel-simple/neopixel-simple.ino)
