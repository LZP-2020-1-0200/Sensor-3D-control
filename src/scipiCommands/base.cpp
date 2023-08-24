


#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorCMD;
extern scpi::Command homeCMD;
extern scpi::Command rstCMD;
extern scpi::Command idnCMD;

const scpi::Command::ChildCMD baseChildCMDs[] {
	{"MOTOR", &motorCMD},
	{"HOME", &homeCMD},
	{"*RST", &rstCMD},
	{"*IDN", &idnCMD}
};

scpi::Command baseCMD(
	nullptr,
	nullptr,
	baseChildCMDs
);