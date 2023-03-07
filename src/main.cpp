#include <Arduino.h>
#include "scpi.h"
#include "led.h"
#include "stepper.h"

#define DEFAULT_BAUD 9600
void setup()
{
  Serial.begin(DEFAULT_BAUD);
  led.init(LED_BUILTIN);
  stepper.init();
}

void loop()
{
  if (Serial.available())
  {
    scpi.addChar(Serial.read());
    return;
  }
}