

#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorLockCMD;

int motorFunc(int argc, char** argv) {
	if(argc==2){
		xMotor.setTarget(atoi(argv[1]));
		yMotor.setTarget(atoi(argv[1]));
		zMotor.setTarget(atoi(argv[1]));
	return 0;
	}else if(argc==3){
		if(strcasecmp(argv[1], "X")==0){
			xMotor.setTarget(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Y")==0){
			yMotor.setTarget(atoi(argv[2]));
		}else if(strcasecmp(argv[1], "Z")==0){
			zMotor.setTarget(atoi(argv[2]));
		} else {
			return 1;
		}
		return 0;
	}
	return 1;
} 

void motorGet() {
	char buff[32];
    itoa(xMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(yMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(zMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write("\r\n");
}

scpi::Command motorCMD{
	motorFunc,
	motorGet,
	{
		{"LOCK", &motorLockCMD}
	}
};