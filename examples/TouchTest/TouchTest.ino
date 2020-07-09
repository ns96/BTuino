#include <XPT2046_Touchscreen_swspi.h>


#define CS_PIN  PE6

//XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  PC13
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

void setup() {
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    Serial.print("Pressure = ");
    Serial.print(p.z);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    delay(30);
    Serial.println();
  }
}
