#include "endSwitch.h"
#include "axisData.h"
#include "stepperState/idleState.h"
#include "stepperState/disabledState.h"
#include "stepperState/targetState.h"
#include "stepperState/homingState.h"
#pragma once

namespace stepperState {
	/**
	 * @brief This class is the state machine for the stepper
	 * @details This class is the state machine for the stepper
	 * It contains all the states and handles the transitions
	 * between them.
	*/
	class StepperStateMachine : public StateMachine
	{
	private:
		
		/// @brief The default state that the state machine starts in and returns to
		State* defaultState = &disabledState;
	public:
		/**
		 * @brief A struct that represents the mode of the stepper motor
		 * @details This struct represents the mode of the stepper motor.
		 * It is used to control the stepper motors.
		 * Each mode has a different behavior.
		 * Some behave as a state machine,
		 * iterating through a sequence of states.
		*/
		enum class mode{
			target,   ///< move to target position
			homing,   ///< move to end switch
			idle,     ///< do nothing
			disabled  ///< disable stepper
		};

		StepperStateMachine(AxisData& axisData);
		~StepperStateMachine();

		/// @brief The axis data reference
		AxisData& axisData;

		/// @brief The idle state instance
		stepperState::IdleState idleState;

		/// @brief The disabled state instance
		stepperState::DisabledState disabledState;

		/// @brief The target state instance
		stepperState::TargetState targetState;

		/// @brief The homing state instance
		stepperState::HomingState homingState;
		
		/// @brief The current state. This isn't accessible by states.
		//AxisData::mode currentMode = AxisData::mode::disabled;

		/// @brief Ticks the state machine
		void tick();

		/// @brief Set the default state to idle or disabled
		/// @see getDefaultMode
		void stepperLockByDefault(bool lock);

		void target(int targetPosition);
		void home();
		void disable();
		void idle();
		
		/// @brief Fetches the current mode of the state machine
		/// @return the current mode of the state machine
		mode getMode() const;

		/// @brief Fetches the default mode of the state machine
		/// @return the default mode of the state machine
		/// @see stepperLockByDefault
		mode getDefaultMode() const;



		/// @brief Fetches the state Instance for the given mode
		/// @param mode the mode to fetch the state for
		/// @return The implicit cast of the corresponding state instance
		//State& getState(AxisData::mode mode);
	};

}
