const int PWMPin = 3;  // Only works with Pin 3
const int PotPin = 0;  // Analog 0

void setup()
{
  pinMode(PWMPin, OUTPUT);
  // Fast PWM Mode, Prescaler = /8
  // PWM on Pin 3, Pin 11 disabled
  // 16Mhz / 8 / (79 + 1) = 25Khz
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21);
  // Set TOP and initialize duty cycle to zero(0)
  OCR2A = 79;   // TOP - DO NOT CHANGE, SETS PWM PULSE RATE
  OCR2B = 0;    // duty cycle for Pin 3 (0-79) generates 1 500nS pulse even when 0
}

void loop()
{
  int in, out;

  in = analogRead(PotPin);
  out = map(in, 0, 1023, 0, 79);
  OCR2B = out;
  delay(200);
}

