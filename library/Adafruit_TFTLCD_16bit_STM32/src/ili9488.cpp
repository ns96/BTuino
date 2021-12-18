// IMPORTANT: LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER TFT SHIELD
// OR BREAKOUT BOARD USAGE.  SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h

// Graphics library by ladyada/adafruit with init code from Rossum
// MIT license

/*
Benchmark                Time (microseconds)
---------------------------------------------
Using GPIO
---------------------------------------------
Screen fill              104767
Text                     10386
Lines                    185635
Horiz/Vert Lines         9400
Rectangles (outline)     5971
Rectangles (filled)      255546
Circles (filled)         95452
Circles (outline)        78896
Triangles (outline)      51741
Triangles (filled)       112147
Rounded rects (outline)  26409
Rounded rects (filled)   295197
---------------------------------------------
Using FSMC:
---------------------------------------------
Screen fill              48091
Text                     5683
Lines                    83850
Horiz/Vert Lines         4258
Rectangles (outline)     2655
Rectangles (filled)      117322
Circles (filled)         39360
Circles (outline)        35190
Triangles (outline)      23373
Triangles (filled)       50048
Rounded rects (outline)  12160
Rounded rects (filled)   134562
Done!

*/

#include "Adafruit_common.h"

#include "ili9488.h"

#define ILI9486 1

/**/
#define TFTLCD_DELAY8 0xFF

const uint8_t ILI9488_regValues_ada[] = {        // Adafruit_TFTLCD only works with EXTC=0
	//                     0xF6, 3, 0x00, 0x01, 0x00,  //Interface Control needs EXTC=1 TM=0, RIM=0
	//            0xF6, 3, 0x01, 0x01, 0x03,  //Interface Control needs EXTC=1 RM=1, RIM=1
/**/
	0xF6, 3, 0x09, 0x01, 0x03,  //Interface Control needs EXTC=1 RM=0, RIM=1
	0xB0, 1, 0x40,      //RGB Signal [40] RCM=2
	0xB4, 1, 0x00,      //Inversion Control [02] .kbv NLA=1, NLB=1, NLC=1
	0xC0, 1, 0x23,      //Power Control 1 [26]
	0xC1, 1, 0x10,      //Power Control 2 [00]
	0xC5, 2, 0x2B, 0x2B,        //VCOM 1 [31 3C]
	0xC7, 1, 0xC0,      //VCOM 2 [C0]
	0x36, 1, 0x48,      //Memory Access [00]
	0xB1, 2, 0x00, 0x1B,        //Frame Control [00 1B]
	0xB7, 1, 0x07,      //Entry Mode [00]
//	TFTLCD_DELAY8, 1,
};

/*
.write16: 36_write8: 0__write8: 36__write8: 48_
.write16: 33_write8: 0__write8: 33__write8: 0__write8: 0__write8: 1__write8: 40__write8: 0__write8: 0_
.write16: 37_write8: 0__write8: 37__write8: 0__write8: 0_
.write16: 13_write8: 0__write8: 13_
.write16: 21_write8: 0__write8: 21_
*/
const uint8_t ILI9488_regValues_post[] =
{ // post-init settings, sniffed from David's lib
	0x36, 1, 0x48,      //Memory Access [00]
	0x33, 6, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00,
	0x37, 2, 0x00, 0x00,
	0x13, 0,			// normaldisp
	0x21, 0,			// invert off
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

const uint8_t reset_off[] = {
	0x01, 0,            //Soft Reset
	TFTLCD_DELAY8, 150,  // .kbv will power up with ONLY reset, sleep out, display on
	0x28, 0,            //Display Off
	0x3A, 1, 0x55,      //Pixel read=565, write=565.
#ifdef ILI9486
	// PGAMCTRL(Positive Gamma Control)
	0xE0, 15, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98,
	          0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
	// NGAMCTRL(Negative Gamma Control)
	0xE1, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
	          0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
	// Digital Gamma Control 1
	0xE2, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
	          0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
#endif
};
const uint8_t wake_on[] = {
	0x11, 0,            //Sleep Out
	TFTLCD_DELAY8, 150,
	0x29, 0,            //Display On
	//additional settings
//	0x21, 0,			// invert off
	0x36, 1, 0x48,      //Memory Access
	0xB0, 1, 0x40,      //RGB Signal [40] RCM=2
};
/*****************************************************************************/
void ili9488_begin(void)
{
//	Serial.println("\nILI9488 begin...");
	init_table(reset_off, sizeof(reset_off));
	//init_table(ILI9488_regValues_ada, sizeof(ILI9488_regValues_ada));   //can change PIXFMT
	init_table(wake_on, sizeof(wake_on));
	//init_table(ILI9488_regValues_post, sizeof(ILI9488_regValues_post));
}

/*****************************************************************************/
// Sets the LCD address window. Relevant to all write routines.
// Input coordinates are assumed pre-sorted (e.g. x2 >= x1).
/*****************************************************************************/
void ili9488_setAddrWindow(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	writeRegister32(ILI9488_COLADDRSET, ((uint32_t)(x1<<16) | x2));  // HX8357D uses same registers!
	writeRegister32(ILI9488_PAGEADDRSET, ((uint32_t)(y1<<16) | y2)); // HX8357D uses same registers!
}

/*****************************************************************************/
void ili9488_fillScreen(uint16_t color)
{
}

/*****************************************************************************/
void ili9488_drawPixel(int16_t x, int16_t y, uint16_t color)
{
}

/*****************************************************************************/
void ili9488_setRotation(uint8_t x)
{
    uint16_t t;

    switch (x)
    {
        case 0:
            t = (ILI9488_MADCTL_BGR | ILI9488_MADCTL_MY);
            break;
        case 1:
            t = (ILI9488_MADCTL_BGR | ILI9488_MADCTL_MV | ILI9488_MADCTL_MX | ILI9488_MADCTL_MY);
            break;
        case 2:
            t = (ILI9488_MADCTL_BGR | ILI9488_MADCTL_MX);
            break;
        case 3:
            t = (ILI9488_MADCTL_BGR | ILI9488_MADCTL_MV);
            break;
    }

    writeRegister8(ILI9488_MADCTL, t ); // MADCTL
}

/*****************************************************************************/
uint16_t ili9488_readPixel(int16_t x, int16_t y)
{
	return 0;
}

void ili9488_invertDisplay(bool i) {
    writeCommand(i ? ILI9488_INVERTON : ILI9488_INVERTOFF);
}
