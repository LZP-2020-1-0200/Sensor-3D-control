
#include <Arduino.h>
#include "scpi2.h"
#include "modelData.h"
#include "stepperController.h"
scpi::Command idnCMD{
	nullptr,
	[](){
		Serial1.print(MANUFACTURER);
		Serial1.print(",");
		Serial1.print(MODEL);
		Serial1.print(",");
		Serial1.print(SERIAL_NUMBER);
		Serial1.print(",");
		Serial1.print(SOFTWARE_VERSION);
		Serial1.print("\r\n");
	}
};

void resetFunc(){
	StepperController::xMotor.Disable();
	StepperController::yMotor.Disable();
	StepperController::zMotor.Disable();
	StepperController::xMotor.reset();
	StepperController::yMotor.reset();
	StepperController::zMotor.reset();
}

scpi::Command rstCMD{
	[](int argc, char** argv){
		Serial.print("Resetting...\r\nPlease wait...\r\n");
		Serial.flush();
		resetFunc();
		delay(1000);
		Serial.print("Reset complete.\r\n");
		Serial.flush();
		return 0;
	}
};