

#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;



scpi::Command homeCMD{
  [](int argc, char** argv){
    xMotor.setHome();
    yMotor.setHome();
    zMotor.setHome();
    Serial1.print("OK\r\n");
    return 0;
  }
};