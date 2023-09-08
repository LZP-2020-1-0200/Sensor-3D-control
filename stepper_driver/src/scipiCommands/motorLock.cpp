
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
		Serial1.print("OK\r\n");
		return 0;
	}else if(strcasecmp(argv[1], "OFF")==0){
		xMotor.Disable();
		yMotor.Disable();
		zMotor.Disable();
		Serial1.print("OK\r\n");
		return 0;
	}else{
		return 1;
	}
	}else if(argc==3){
		if(strcasecmp(argv[1], "X")==0){
			if(strcasecmp(argv[2], "ON")==0){
			xMotor.Enable();
			Serial1.print("OK\r\n");
			return 0;
			}else if(strcasecmp(argv[2], "OFF")==0){
			xMotor.Disable();
			Serial1.print("OK\r\n");
			return 0;
			}
		}else if(strcasecmp(argv[1], "Y")==0){
			if(strcasecmp(argv[2], "ON")==0){
			yMotor.Enable();
			Serial1.print("OK\r\n");
			return 0;
			}else if(strcasecmp(argv[2], "OFF")==0){
			yMotor.Disable();
			Serial1.print("OK\r\n");
			return 0;
			}
		}else if(strcasecmp(argv[1], "Z")==0){
			if(strcasecmp(argv[2], "ON")==0){
				zMotor.Enable();
				Serial1.print("OK\r\n");
				return 0;
			}else if(strcasecmp(argv[2], "OFF")==0){
				zMotor.Disable();
				Serial1.print("OK\r\n");
				return 0;
			}
		}
	}
	Serial1.print("ERROR\r\n");
	return 1;
}

void motorLockGet() {
	if(xMotor.isEnabled()){
		Serial1.print("1");
	}else{
		Serial1.print("0");
	}
	Serial1.print(" ");
	if(yMotor.isEnabled()){
		Serial1.print("1");
	}else{
		Serial1.print("0");
	}
	Serial1.print(" ");
	if(zMotor.isEnabled()){
		Serial1.print("1");
	}else{
		Serial1.print("0");
	}
	Serial1.print("\r\n");
}

scpi::Command motorLockCMD{
  motorLockFunc,
  motorLockGet
};