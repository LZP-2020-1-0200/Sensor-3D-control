
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorStateDefaultCMD;

int modeToInt(StepperController::mode m) {
	if(m==StepperController::mode::disabled) {
		return 0;
	} else if(m==StepperController::mode::idle) {
		return 1;
	} else if(m==StepperController::mode::homing) {
		return 2;
	} else if(m==StepperController::mode::target) {
		return 3;
	} else if(m==StepperController::mode::raw){
		return 4;
	}
	Serial.print("Invalid mode!\r\n");
	// Should never happen
	return 0;
}

void motorStateGet() {
	Serial1.print(modeToInt(xMotor.getMode()), DEC);
	Serial1.print(" ");
	Serial1.print(modeToInt(yMotor.getMode()), DEC);
	Serial1.print(" ");
	Serial1.print(modeToInt(zMotor.getMode()), DEC);
	Serial1.print("\r\n");
}

scpi::Command::ChildCMD motorStateChildCMDs[] = {
	{"DEFAULT", &motorStateDefaultCMD}
};

scpi::Command motorStateCMD{
	nullptr,
	motorStateGet,
	motorStateChildCMDs
};