// test a KY-040 style rotary encoder module on a blue pill board
// uncomment either LIBMAPLE_CORE or STM32DUINO_CORE 
//#define LIBMAPLE_CORE
#define STM32DUINO_CORE
// for STM32DUINO_CORE be sure to select a serial port in the tools menu

// define encoder pins
// clock and data are from the silkscreen on the encoder module
#define ENC_CLK PA8
#define ENC_DATA PC9
#define LEDPIN PD13
volatile uint32_t encoderCount;

// call this from the systick interrupt every millisecond
// modified from the original code by dannyf
// at https://github.com/dannyf00/My-MCU-Libraries---2nd-try/blob/master/encoder1.c
void encoder1_read(void)
{
  volatile static uint8_t ABs = 0;
  ABs = (ABs << 2) & 0x0f; //left 2 bits now contain the previous AB key read-out;
  ABs |= (digitalRead(ENC_CLK) << 1) | digitalRead(ENC_DATA);
  switch (ABs)
  {
    case 0x0d:
      encoderCount++;
      break;
    case 0x0e:
      encoderCount--;
      break;
  }
}

void led_blink()
{
  static uint8_t led_state = 0;
  led_state = 1 - led_state;
  digitalWrite(LEDPIN, led_state);
}

void setup()
{
  Serial.begin(115200);
  pinMode(ENC_CLK, INPUT);
  pinMode(ENC_DATA, INPUT);
  pinMode(LEDPIN, OUTPUT);
  encoderCount = 10000;
#ifdef LIBMAPLE_CORE  
  systick_attach_callback(&encoder1_read);
#endif  
}

void loop()
{
  static uint32_t count;
  static uint32_t prevCount;
  count = encoderCount;
  if (count != prevCount)
  {
    prevCount = count;
    Serial.print("Count: ");
    Serial.println(count);
    led_blink();
  }
}

#ifdef STM32DUINO_CORE
void HAL_SYSTICK_Callback()
{
  encoder1_read();
}
#endif
