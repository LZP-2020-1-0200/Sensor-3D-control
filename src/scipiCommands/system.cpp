
#include <Arduino.h>
#include "scpi2.h"
#include "modelData.h"

scpi::Command idnCMD{
	nullptr,
	[](){
		Serial1.write(MANUFACTURER);
		Serial1.write(",");
		Serial1.write(MODEL);
		Serial1.write(",");
		Serial1.write(SERIAL);
		Serial1.write(",");
		Serial1.write(SOFTWARE_VERSION);
		Serial1.write("\r\n");
	}
};

void (* const resetFunc)() = 0; //declare reset function @ address 0 (not a function pointer

scpi::Command rstCMD{
	[](int argc, char** argv){
		resetFunc();
		return 0;
	}
};