
#include "endSwitch.h"

endSwitch::endSwitch(
	volatile uint8_t* pullupPort, 
	int pullpin, 
	volatile uint8_t* dataDirRegister, 
	int dataDirPin, 
	volatile uint8_t* pinreg, 
	int pin):
	pullupPort(pullupPort),  
	pullpin(pullpin), 
	dataDirRegister(dataDirRegister), 
	dataDirPin(dataDirPin),
	pinreg(pinreg), 
	pin(pin) {
	
	cli();
	// configure switch pin to input mode
	*(dataDirRegister) &= ~(1 << dataDirPin);
	// configure switch pull-up resistor
	*(pullupPort) &= ~(1 << pullpin);
	sei();
}; 

void endSwitch::update() {
	triggered = (1 & ((*pinreg)>>pin));
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

//* fills out the correct pins and registers for endswitches
#define SWITCH_SETUP(port, pin) \
  &PORT ## port,\
  PORT ## port ## pin,\
  &DDR ## port,\
  DD ## port ## pin,\
  &PIN ## port,\
  PIN ## port ## pin

endSwitch endSwitch::Xlow{SWITCH_SETUP(B,2)};
endSwitch endSwitch::Xhigh{SWITCH_SETUP(B,1)};
endSwitch endSwitch::Ylow{SWITCH_SETUP(D,6)};
endSwitch endSwitch::Yhigh{SWITCH_SETUP(B,3)};
endSwitch endSwitch::Zlow{SWITCH_SETUP(F,1)};
endSwitch endSwitch::Zhigh{SWITCH_SETUP(F,0)};

#undef SWITCH_SETUP
