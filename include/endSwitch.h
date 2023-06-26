
#include <Arduino.h>
#ifndef ENDSWITCH_H
#define ENDSWITCH_H


class endSwitch{
	/*
	 * the port that holds data about the pull-up resistor state
	 * of this switch
	 */
	volatile uint8_t* pullupPort;
	//* pin in pull-up resistor port
	int pullpin;
	//* the data direction register for that pin
	volatile uint8_t* dataDirRegister;
	//* pin number in DDR
	int dataDirPin;
	//* register of the read value
	volatile uint8_t* pinreg;
	//* pin number in read register
	int pin;
	//* read-only value for the last switch state
	bool triggered=false;
public:
	endSwitch(volatile uint8_t*, int, volatile uint8_t*, int, volatile uint8_t*, int);
	//* fetches the latest state of the switch
	void update();
	//* returns last known switch state
	bool getState();

	static endSwitch Zlow;
	static endSwitch Zhigh;
	static endSwitch Ylow;
	static endSwitch Yhigh;
	static endSwitch Xlow;
	static endSwitch Xhigh;
};

//* calls update all switches
void switchUpdate();

#endif
