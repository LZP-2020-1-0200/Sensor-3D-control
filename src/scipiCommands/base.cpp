


#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorCMD;
extern scpi::Command homeCMD;
extern scpi::Command rstCMD;
extern scpi::Command idnCMD;

scpi::Command baseCMD{
	nullptr,
	nullptr,
	{
		{"MOTOR", &motorCMD},
		{"HOME", &homeCMD},
		{"*RST", &rstCMD},
		{"*IDN", &idnCMD}
	}
};