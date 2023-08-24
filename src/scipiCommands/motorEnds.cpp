
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

void motorPrintEnds(StepperController& motor) {
	Serial1.print(motor.getStartSwitch(), DEC);
	Serial1.print(" ");
	Serial1.print(motor.getEndSwitch(), DEC);
}

void motorEndXGet() {
	motorPrintEnds(xMotor);
	Serial1.print("\r\n");
}

void motorEndYGet() {
	motorPrintEnds(yMotor);
	Serial1.print("\r\n");
}

void motorEndZGet() {
	motorPrintEnds(zMotor);
	Serial1.print("\r\n");
}

scpi::Command motorEndXCMD{
	nullptr,
	motorEndXGet
};

scpi::Command motorEndYCMD{
	nullptr,
	motorEndYGet
};

scpi::Command motorEndZCMD{
	nullptr,
	motorEndZGet
};

const scpi::Command::ChildCMD motorEndChildCMDs[] = {
	{"X", &motorEndXCMD},
	{"Y", &motorEndYCMD},
	{"Z", &motorEndZCMD}
};

scpi::Command motorEndCMD{
	nullptr,
	nullptr,
	motorEndChildCMDs
};