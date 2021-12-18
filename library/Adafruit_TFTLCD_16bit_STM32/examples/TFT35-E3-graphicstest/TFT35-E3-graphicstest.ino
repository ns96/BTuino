#include <Arduino.h>

#include <Adafruit_TFTLCD_16bit_STM32.h> // Hardware-specific library

Adafruit_TFTLCD_16bit_STM32 tft;

void setup(void) {
  Serial.begin(115200);
  while ( !Serial ) ;
  delay(1000);

pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(F("TFT LCD test"));

  Serial.print("TFT size is "); Serial.print((uint16_t)tft.width()); Serial.print("x"); Serial.println((uint16_t)tft.height());

  /*
    pinMode(PB2, OUTPUT);
    while(1) {
  	digitalWrite(PB2, HIGH);
  	digitalWrite(PB2, LOW);
    }
  */
  uint16_t identifier;
#if 0
  identifier = 0x9341;
#else
  tft.reset();
  do {
    identifier = tft.readID();
    if (identifier == 0) identifier = 0x9341;
    if (identifier == 0x9325) {
      Serial.println(F("Found ILI9325 LCD driver"));
    } else if (identifier == 0x9328) {
      Serial.println(F("Found ILI9328 LCD driver"));
    } else if (identifier == 0x7575) {
      Serial.println(F("Found HX8347G LCD driver"));
    } else if (identifier == 0x9341) {
      Serial.println(F("Found ILI9341 LCD driver"));
    } else if (identifier == 0x8357) {
      Serial.println(F("Found HX8357D LCD driver"));
    } else if (identifier == 0x5310) {
      Serial.println(F("Found NT35310 LCD driver"));
    } else {
      Serial.print(F("\n*** Unknown LCD driver chip: "));
      Serial.println(identifier, HEX);
      //return;
      //identifier = 0;
      delay(1000);
    }
  } while (identifier == 0);
#endif

  tft.begin(identifier);
  tft.reset();
  Serial.println("TFT begin done.");
  /*
  	// color gradient test
  	while(1) {
  		tft.setRotation(0);
  		tft.fillScreen(BLACK);
  		uint16_t x = 0, y = 10;
  		uint8_t r=0,g=0,b=0;
  		uint16_t color = 0;
  		// r
  		Serial.println("*** RED ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			r++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// g
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** GREEN ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			g++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// b
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** BLUE ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			b++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// rg
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** RED/GREEN ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			g+=2; r++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// gb
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** GREEN/BLUE ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			g++; b++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// rb
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** RED/BLUE ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			r++; b++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		// rgb
  		y+=30; x=0;
  		r=0; g=0; b=0;
  		Serial.println("*** RED/GREEN/BLUE ***");
  		while (x<tft.width()) {
  			color = tft.color565(r,g,b);
  			Serial.print("color: "); Serial.println(color,HEX);
  			tft.fillRect(x, y, 10, 20, color);
  			r++; g++; b++;
  			x+=10;
  			delay(500);
  		}
  		delay(1000);
  		while ( Serial.available()<=0 );
  	}
*/  
}


unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(BLACK);
  //delay(500);
  tft.fillScreen(RED);
  //delay(500);
  tft.fillScreen(GREEN);
  //delay(500);
  tft.fillScreen(BLUE);
  //delay(500);
  tft.fillScreen(BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(BLACK);
  //return 0;
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(BLACK);
  start = micros();
  for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n = min(tft.width(), tft.height());
  for (i = n; i > 0; i -= 6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(BLACK);
  start = micros();
  for (x = radius; x < w; x += r2) {
    for (y = radius; y < h; y += r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = tft.width()  + radius,
                      h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for (x = 0; x < w; x += r2) {
    for (y = 0; y < h; y += r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for (i = 0; i < w; i += 6) {
    i2 = i / 2;
    tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
    i2 = i / 2;
    tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
  }

  return micros() - start;
}

void doTest(void)
{
  Serial.println(F("\nBenchmark                Time (microseconds)"));

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Lines                    "));
  Serial.println(testLines(CYAN));
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(RED, BLUE));
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(GREEN));
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(YELLOW, MAGENTA));
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, MAGENTA));

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, WHITE));
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));
}

void loop(void) {
  for (uint8_t rotation = 0; rotation < 4; rotation++) {
    tft.setRotation(rotation);
    //Serial.print("ID: "); Serial.println(tft.readID(),HEX);
    Serial.print("rotation: "); Serial.print(rotation);
    Serial.print(", runtime: ");
    Serial.println(testText());
    delay(1000);
  }
  doTest();
}
