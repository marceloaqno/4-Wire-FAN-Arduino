/*
 *                         ATtiny85
 *                      -------u-------
 *  RST - A0 - (D 5) --| 1 PB5   VCC 8 |-- +5V
 *                     |               |
 *        A3 - (D 3) --| 2 PB3   PB2 7 |-- (D 2) - A1  --> 10K Potentiometer
 *                     |               | 
 *        A2 - (D 4) --| 3 PB4   PB1 6 |-- (D 1) - PWM --> Fan Blue wire
 *                     |               |      
 *              Gnd ---| 4 GND   PB0 5 |-- (D 0) - PWM --> Disabled
 *                     -----------------
 */
 
// normal delay() won't work anymore because we are changing Timer1 behavior
// Adds delay_ms and delay_us functions
#include <util/delay.h>

// Clock at 8mHz
#define F_CPU 8000000  // This is used by delay.h library

const int PWMPin = 1;  // Only works with Pin 1(PB1)
const int PotPin = A1;

void setup()
{
  pinMode(PWMPin, OUTPUT);
  // Fast PWM Mode, Prescaler = /8
  // PWM on Pin 1(PB1), Pin 0(PB0) disabled
  // 8Mhz / 8 / (39 + 1) = 25Khz
  TCCR0A = _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS01);
  // Set TOP and initialize duty cycle to zero(0)
  OCR0A = 39;    // TOP - DO NOT CHANGE, SETS PWM PULSE RATE
  OCR0B = 0;     // duty cycle for Pin 1(PB1) - generates 1 500nS pulse even when 0
}

void loop()
{
  int in, out;

  in = analogRead(PotPin);
  out = map(in, 0, 1023, 0, 39);
  OCR0B = out;
  _delay_ms(200);
}

