
#include "scpi2.h"
#include "stepperController.h"
#include "stepperState/stepperStateMachine.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;


int motorStateDefaultFunc(int argc, char** argv) {
	if(argc==2){
		int modeNum = atoi(argv[1]);
		if(modeNum!=0 && modeNum!=1) return 1;
		stepperState::StepperStateMachine::mode mode = (modeNum==0) ? stepperState::StepperStateMachine::mode::disabled : stepperState::StepperStateMachine::mode::idle;
		xMotor.setDefaultMode(mode);
		yMotor.setDefaultMode(mode);
		zMotor.setDefaultMode(mode);
		Serial1.print("OK\r\n");
	} else {
		return 1;
	}
	return 0;
}

void motorStateDefaultGet() {
	Serial1.print((xMotor.getDefaultMode()==stepperState::StepperStateMachine::mode::disabled) ? 0 : 1);
	Serial1.print(" ");
	Serial1.print((yMotor.getDefaultMode()==stepperState::StepperStateMachine::mode::disabled) ? 0 : 1);
	Serial1.print(" ");
	Serial1.print((zMotor.getDefaultMode()==stepperState::StepperStateMachine::mode::disabled) ? 0 : 1);
	Serial1.print("\r\n");
}

scpi::Command motorStateDefaultCMD{
	motorStateDefaultFunc,
	motorStateDefaultGet
};