
#include <Arduino.h>
#ifndef ENDSWITCH_H
#define ENDSWITCH_H

/**
 * @class EndSwitch
 * @brief A class that represents an end switch
 * @details This class represents an end switch. It is used to detect when the stepper has reached the end of its range of motion.
*/
class EndSwitch{
	/**
	 * @brief The port that holds data about the pull-up resistor state
	 * of this switch
	 */
	volatile uint8_t* pullupPort;
	/// @brief pin in pull-up resistor port
	int pullpin;
	/// @brief the data direction register for that pin
	volatile uint8_t* dataDirRegister;
	/// @brief pin number in DDR
	int dataDirPin;
	/// @brief register of the read value
	volatile uint8_t* pinreg;
	/// @brief pin number in read register
	int pin;
	/// @brief read-only value for the last switch state
	bool triggered=false;
public:
	/// @brief The constructor for EndSwitch
	EndSwitch(volatile uint8_t*, int, volatile uint8_t*, int, volatile uint8_t*, int);
	/// @brief fetches the latest state of the switch
	void update();
	/// @brief returns last known switch state
	bool getState() const;

	/// @brief resets the switch
	void reset();

	static EndSwitch Zlow;
	static EndSwitch Zhigh;
	static EndSwitch Ylow;
	static EndSwitch Yhigh;
	static EndSwitch Xlow;
	static EndSwitch Xhigh;
};

/// @brief calls update on all static switches
void switchUpdate();

#endif
