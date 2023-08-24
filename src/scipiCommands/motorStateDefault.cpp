
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;


int motorStateDefaultFunc(int argc, char** argv) {
	if(argc==2){
		int modeNum = atoi(argv[1]);
		if(modeNum!=0 && modeNum!=1) return 1;
		StepperController::mode mode = (modeNum==0) ? StepperController::mode::disabled : StepperController::mode::idle;
		xMotor.setDefaultMode(mode);
		yMotor.setDefaultMode(mode);
		zMotor.setDefaultMode(mode);
	} else {
		return 1;
	}
	return 0;
}

void motorStateDefaultGet() {
	Serial1.print((xMotor.getDefaultMode()==StepperController::mode::disabled) ? 0 : 1);
	Serial1.print(" ");
	Serial1.print((yMotor.getDefaultMode()==StepperController::mode::disabled) ? 0 : 1);
	Serial1.print(" ");
	Serial1.print((zMotor.getDefaultMode()==StepperController::mode::disabled) ? 0 : 1);
	Serial1.print("\r\n");
}

scpi::Command motorStateDefaultCMD{
	motorStateDefaultFunc,
	motorStateDefaultGet
};