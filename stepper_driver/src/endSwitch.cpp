
#include "endSwitch.h"

endSwitch::endSwitch(
	volatile uint8_t* pullupPort, 
	int pullpin, 
	volatile uint8_t* dataDirRegister, 
	int dataDirPin, 
	volatile uint8_t* pinreg, 
	int pin,
	const char* name):
	pullupPort(pullupPort),  
	pullpin(pullpin), 
	dataDirRegister(dataDirRegister), 
	dataDirPin(dataDirPin),
	pinreg(pinreg), 
	pin(pin),
	name(name) {
	
	cli();
	// configure switch pin to input mode
	*(dataDirRegister) &= ~(1 << dataDirPin);
	// configure switch pull-up resistor
	*(pullupPort) &= ~(1 << pullpin);
	sei();
}; 

void endSwitch::update() {
	lastState = triggered;
	triggered = (1 & ((*pinreg)>>pin));
	if (triggered != lastState) {
		edge = triggered ? 1 : -1;
	}
}

void endSwitch::printEdge() {
	if (edge != 0) {
		Serial.print(name);
		Serial.print(": ");
		Serial.println((edge==1)? "triggered" : "untriggered");
		edge = 0;
	}
}

bool endSwitch::getState() {
	return triggered;
};

void switchUpdate(){
	endSwitch::Zlow.update();
	endSwitch::Zhigh.update();
	endSwitch::Ylow.update();
	endSwitch::Yhigh.update();
	endSwitch::Xlow.update();
	endSwitch::Xhigh.update();
}

void endSwitch::reset(){
	triggered=false;
}

//* fills out the correct pins and registers for endswitches
#define SWITCH_SETUP(port, pin) \
  &PORT ## port,\
  PORT ## port ## pin,\
  &DDR ## port,\
  DD ## port ## pin,\
  &PIN ## port,\
  PIN ## port ## pin

endSwitch endSwitch::Xlow{SWITCH_SETUP(B,2), "Xlow"};
endSwitch endSwitch::Xhigh{SWITCH_SETUP(B,1), "Xhigh"};
endSwitch endSwitch::Ylow{SWITCH_SETUP(D,6), "Ylow"};
endSwitch endSwitch::Yhigh{SWITCH_SETUP(B,3), "Yhigh"};
endSwitch endSwitch::Zlow{SWITCH_SETUP(F,1), "Zlow"};
endSwitch endSwitch::Zhigh{SWITCH_SETUP(F,0), "Zhigh"};

#undef SWITCH_SETUP
