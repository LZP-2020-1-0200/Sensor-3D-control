

#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorLockCMD;
extern scpi::Command motorStateCMD;
extern scpi::Command motorEndCMD;

int motorFunc(int argc, char** argv) {
	if(argc==2){
		xMotor.setTarget(atoi(argv[1]));
		yMotor.setTarget(atoi(argv[1]));
		zMotor.setTarget(atoi(argv[1]));
		Serial1.print("OK\r\n");
		return 0;
	}else if(argc==3){
		if(strcasecmp(argv[1], "X")==0){
			xMotor.setTarget(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Y")==0){
			yMotor.setTarget(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Z")==0){
			zMotor.setTarget(atoi(argv[2]));
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

void motorGet() {
	Serial1.print(xMotor.get_position(), DEC);
	Serial1.print(" ");
	Serial1.print(yMotor.get_position(), DEC);
	Serial1.print(" ");
	Serial1.print(zMotor.get_position(), DEC);
	Serial1.print("\r\n");
}

const scpi::Command::ChildCMD motorChildCMDs[] = {
	{"LOCK", &motorLockCMD},
	{"STATE", &motorStateCMD},
	{"END", &motorEndCMD}
};

scpi::Command motorCMD{
	motorFunc,
	motorGet,
	motorChildCMDs
};