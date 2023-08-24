
#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

int motorLockFunc(int argc, char** argv) {
	if(argc==2){
	if(strcasecmp(argv[1], "ON")==0){
		xMotor.Enable();
		yMotor.Enable();
		zMotor.Enable();
		return 0;
	}else if(strcasecmp(argv[1], "OFF")==0){
		xMotor.Disable();
		yMotor.Disable();
		zMotor.Disable();
		return 0;
	}else{
		return 1;
	}
	}else if(argc==3){
	if(strcasecmp(argv[1], "X")==0){
		if(strcasecmp(argv[2], "ON")==0){
		xMotor.Enable();
		return 0;
		}else if(strcasecmp(argv[2], "OFF")==0){
		xMotor.Disable();
		return 0;
		}
	}else if(strcasecmp(argv[1], "Y")==0){
		if(strcasecmp(argv[2], "ON")==0){
		yMotor.Enable();
		return 0;
		}else if(strcasecmp(argv[2], "OFF")==0){
		yMotor.Disable();
		return 0;
		}
	}else if(strcasecmp(argv[1], "Z")==0){
		if(strcasecmp(argv[2], "ON")==0){
		zMotor.Enable();
		return 0;
		}else if(strcasecmp(argv[2], "OFF")==0){
		zMotor.Disable();
		return 0;
		}
	}
	}
	return 1;
}

void motorLockGet() {
	if(xMotor.isEnabled()){
		Serial1.print("ON");
	}else{
		Serial1.print("OFF");
	}
	Serial1.print(" ");
	if(yMotor.isEnabled()){
		Serial1.print("ON");
	}else{
		Serial1.print("OFF");
	}
	Serial1.print(" ");
	if(zMotor.isEnabled()){
		Serial1.print("ON");
	}else{
		Serial1.print("OFF");
	}
	Serial1.print("\r\n");
}

scpi::Command motorLockCMD{
  motorLockFunc,
  motorLockGet
};