
#include "endSwitch.h"

EndSwitch::EndSwitch(
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

void EndSwitch::update() {
	triggered = (1 & ((*pinreg)>>pin));
}

bool EndSwitch::getState() const {
	return triggered;
};

void switchUpdate(){
	EndSwitch::Zlow.update();
	EndSwitch::Zhigh.update();
	EndSwitch::Ylow.update();
	EndSwitch::Yhigh.update();
	EndSwitch::Xlow.update();
	EndSwitch::Xhigh.update();
}

void EndSwitch::reset(){
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

EndSwitch EndSwitch::Xlow{SWITCH_SETUP(B,2)};
EndSwitch EndSwitch::Xhigh{SWITCH_SETUP(B,1)};
EndSwitch EndSwitch::Ylow{SWITCH_SETUP(D,6)};
EndSwitch EndSwitch::Yhigh{SWITCH_SETUP(B,3)};
EndSwitch EndSwitch::Zlow{SWITCH_SETUP(F,1)};
EndSwitch EndSwitch::Zhigh{SWITCH_SETUP(F,0)};

#undef SWITCH_SETUP
