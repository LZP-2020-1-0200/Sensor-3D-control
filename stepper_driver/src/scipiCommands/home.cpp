

#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;



scpi::Command homeCMD{
  [](int argc, char** argv){
    xMotor.home();
    yMotor.home();
    zMotor.home();
    Serial1.print("OK\r\n");
    return 0;
  }
};