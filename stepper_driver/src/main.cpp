#include <Arduino.h>
#include "scpi2.h"
#include "stepper.h"
#include "endSwitch.h"
#include "stepperController.h"
#define DEFAULT_BAUD 9600



StepperController& xMotor = StepperController::xMotor;
StepperController& yMotor = StepperController::yMotor;
StepperController& zMotor = StepperController::zMotor;

extern scpi::Command baseCMD;

scpi::scpi2 inputHandler = scpi::scpi2(Serial1, baseCMD);

#ifndef PIO_UNIT_TESTING
void setup()
{
  Serial.begin(DEFAULT_BAUD);
  Serial.setTimeout(100);
  Serial1.begin(DEFAULT_BAUD);
  Serial1.setTimeout(100);
  StepperController::motors[0]=&xMotor;
  StepperController::motors[1]=&yMotor;
  StepperController::motors[2]=&zMotor;
  //s.set_direction(STEPPER_UP);
  xMotor.setDelay("100");
  yMotor.setDelay("100");
  zMotor.setDelay("200");
  //zMotor.setTarget(30000);
  delay(3000);
  Serial.print("Initialized\r\n");
  baseCMD.dump();
  //zMotor.setMode(StepperController::mode::homing);
}

void loop()
{
  inputHandler.update();
  endSwitch::Xlow.printEdge();
  endSwitch::Xhigh.printEdge();
  endSwitch::Ylow.printEdge();
  endSwitch::Yhigh.printEdge();
  endSwitch::Zlow.printEdge();
  endSwitch::Zhigh.printEdge();
}

#endif
