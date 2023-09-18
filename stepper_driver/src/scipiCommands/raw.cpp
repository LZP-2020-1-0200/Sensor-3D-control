
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorLockCMD;
extern scpi::Command motorStateCMD;
extern scpi::Command motorEndCMD;

int rawFunc(int argc, char** argv) {
	if(argc==2){
		xMotor.setTargetRaw(atoi(argv[1]));
		yMotor.setTargetRaw(atoi(argv[1]));
		zMotor.setTargetRaw(atoi(argv[1]));
		Serial1.print("OK\r\n");
		return 0;
	}else if(argc==3){
		if(strcasecmp(argv[1], "X")==0){
			xMotor.setTargetRaw(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Y")==0){
			yMotor.setTargetRaw(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Z")==0){
			zMotor.setTargetRaw(atoi(argv[2]));
		} else {
			Serial1.print("ERROR\r\n");
			return 1;
		}
		Serial1.print("OK\r\n");
		return 0;
	}
	Serial1.print("ERROR\r\n");
	return 1;
} 


scpi::Command rawCMD{
	rawFunc
};