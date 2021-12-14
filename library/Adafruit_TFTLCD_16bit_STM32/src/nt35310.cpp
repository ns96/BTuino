// IMPORTANT: LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER TFT SHIELD
// OR BREAKOUT BOARD USAGE.  SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h

// Graphics library by ladyada/adafruit with init code from Rossum
// MIT license



#include "Adafruit_common.h"

#include "nt35310.h"

#define NT35310 1

#define TFTLCD_DELAY8 0xFF

const uint8_t nt35310_init_sequential[] = {
        0xC0, 2, 0x0c, 0x02,
        0xC1, 1, 0x44,
        0xC5, 3, 0x00, 0x16, 0x80,
        0x36, 1, 0XC0,
        0x3A, 1, 0x55, // Interface Mode Control
        0XB0, 1, 0x00, // Interface Mode Control
        0xB1, 1, 0xB0, // Frame rate 70HZ
        0xB4, 1, 0x02,
        0xB6, 2, 0x02, 0x02,
        0xE9, 1, 0x00,
        0XF7, 4, 0xA9, 0x51, 0x2C, 0x82,
        0x11, 0,
        TFTLCD_DELAY8, 120,
        0x29, 0
};

/*****************************************************************************/
static void WriteCmdParamN(uint16_t cmd, int8_t N, const uint8_t * block)
{
	//Serial.print("cmd: "); Serial.print(cmd,HEX);
    writeCommand(cmd);
	//Serial.print(", data: ");
	while (N-- > 0) {
		uint8_t u8 = *block++;
		CD_DATA;
		//Serial.print(u8,HEX);
		writeData(0x00FF&u8);
	}
    CS_IDLE;
	//Serial.write('\n');
}

/*****************************************************************************/
static void init_table(const uint8_t *table, int16_t size)
{
	while (size > 0) {
		uint8_t cmd = *table++;
		uint8_t len = *table++;
		if (cmd == TFTLCD_DELAY8) {
			//Serial.print("delay: "); Serial.println(len);
			delay(len);
			len = 0;
		} else {
			WriteCmdParamN(cmd, len, table);
			table += len;
		}
		size -= len + 2;
	}
}

/*****************************************************************************/
void nt35310_begin(void)
{
//	Serial.println("\nNT35310 begin...");
	init_table(nt35310_init_sequential, sizeof(nt35310_init_sequential));
}

/*****************************************************************************/
// Sets the LCD address window. Relevant to all write routines.
// Input coordinates are assumed pre-sorted (e.g. x2 >= x1).
/*****************************************************************************/
void nt35310_setAddrWindow(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	writeRegister32(NT35310_SET_HORIZONTAL_ADDRESS, ((uint32_t)(x1<<16) | x2));
	writeRegister32(NT35310_SET_VERTICAL_ADDRESS, ((uint32_t)(y1<<16) | y2));
    writeCommand(NT35310_WRITE_MEMORY_START);  // Ready to write memory
}

/*****************************************************************************/
void nt35310_fillScreen(uint16_t color)
{
}

/*****************************************************************************/
void nt35310_drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

/*****************************************************************************/
void nt35310_setRotation(uint8_t x)
{
    uint16_t t;

    switch (x)
    {
        case 0:
            t = (NT35310_MADCTL_MY | NT35310_MADCTL_MX | NT35310_MADCTL_RGB);
            break;
        case 1:
            t = (NT35310_MADCTL_MY | NT35310_MADCTL_MV | NT35310_MADCTL_RGB);
            break;
        case 2:
            t = NT35310_MADCTL_RGB;
            break;
        case 3:
        default: // case 3:
            t = (NT35310_MADCTL_MX | NT35310_MADCTL_MV | NT35310_MADCTL_RGB);
            break;
    }

    writeRegister8(NT35310_SET_ADDRESS_MODE, t ); // MADCTL
}

/*****************************************************************************/
uint16_t nt35310_readPixel(int16_t x, int16_t y)
{
	return 0;
}

void nt35310_invertDisplay(bool i) {
    writeCommand(i ? NT35310_ENTER_INVERT_MODE : NT35310_EXIT_INVERT_MODE);
}