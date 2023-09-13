/**
 * @file axisData.h
 * @brief Contains the AxisData struct
 * @details This file contains the AxisData struct.
 * @see AxisData
*/

#include "endSwitch.h"
#include "stepper.h"
#pragma once

/**
 * @brief Struct that manipulator methods use to change the state of the stepper motors
 * @details This struct contains all the information that the manipulator methods need to change the state of the stepper motors.
*/
struct AxisData {
	/// @brief The time in milliseconds between each step
	unsigned int step_delay_milliseconds = 20;

	/// @brief The desired stepper direction/state enum
	enum class directionE {
		UP,
		DOWN,
		PAUSE,
		DISABLED
	};

	/// @brief The current stepper direction/state
	directionE direction = directionE::DISABLED;

	int wiggle = 0;

	/// @brief Reference to the start end switch, it is at the lower end
	const EndSwitch& start;

	/// @brief Reference to the end end switch, it is at the higher end
	const EndSwitch& end;

	/// @brief Reference to the stepper motor, used only to read data
	const Stepper& stepper;
	
	/// @brief Stepper movement pattern enum
	enum class mode {
		target = 0,
		homing = 1,
		idle = 2,
		disabled = 3,
		raw_target = 4
	};

	/// @brief The desired stepper movement pattern
	mode nextMode = mode::disabled;

	/// @brief The default stepper movement pattern
	mode defaultMode = mode::disabled;

	/// @brief Constructor for AxisData
	/// @param start The start end switch
	/// @param end The end end switch
	/// @param stepper The stepper motor
	AxisData(const EndSwitch& start, const EndSwitch& end, const Stepper& stepper) : start(start), end(end), stepper(stepper) {
	}
};