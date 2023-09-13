
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorStateDefaultCMD;

int modeToInt(stepperState::StepperStateMachine::mode m) {
	if(m==stepperState::StepperStateMachine::mode::disabled) {
		return 0;
	} else if(m==stepperState::StepperStateMachine::mode::idle) {
		return 1;
	} else if(m==stepperState::StepperStateMachine::mode::homing) {
		return 2;
	} else if(m==stepperState::StepperStateMachine::mode::target) {
		return 3;
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