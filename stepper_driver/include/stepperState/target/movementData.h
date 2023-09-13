#include "../axisData.h"
#pragma once
/**
 * @namespace stepperState::target
 * @brief The target state namespace
 * @details This namespace contains all of the target state classes
 * and the MovementData struct.
 * @see stepperState::target::MovementData
 * @see stepperState::target::Above
 * @see stepperState::target::CloseIn
 * @see stepperState::TargetState
*/
namespace stepperState::target
{
	/**
	 * @brief Holds data for the target state
	*/
	struct MovementData
	{
		
		/// @brief The target position
		int targetPosition = 0;

		/// @brief All of the possible states
		enum class state {
			above,
			closeIn,
			done
		}

		/// @brief The next state to transition to
		nextMode = state::above;

		/// @brief The axis data reference
		AxisData& axisData;

		/**
		 * @brief Construct a new Movement Data object
		 * 
		 * @param axisData The axis data reference
		 */
		MovementData(AxisData& axisData) : axisData(axisData) {
		}
	};

} // namespace stepperState::target
