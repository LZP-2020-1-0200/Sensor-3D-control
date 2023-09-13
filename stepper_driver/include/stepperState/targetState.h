
#include "../state.h"
#include "../stateMachine.h"
#include "./axisData.h"
#include "target/movementData.h"
#pragma once

namespace stepperState{
	/**
	 * @brief This state moves the axis to the target position
	 * @details Taking into account the wiggleroom of the stepper,
	 * it moves the axis above the target position by the overshoot amount
	 * and then moves it down to the target position.
	 * 
	 * Upon completion, it transitions to the default state.
	*/
	class TargetState : public State
	{
	private:
	public:
		/// @brief The data for this state
		target::MovementData movementData;
		
		TargetState(AxisData& axisData);
		~TargetState();

		int state = 0;
		

		void tick() override;
		void reset() override;
		void exit() override;
	};

} // namespace stepperState