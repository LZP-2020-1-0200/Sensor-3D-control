/**
 * @file disabledState.h
 * @brief Contains the DisabledState class
 * @details This file contains the DisabledState class.
 * @see DisabledState
 * @see State
*/
#include "state.h"
#include "axisData.h"

namespace stepperState {
	/**
	 * @class DisabledState
	 * @brief A class that represents the disabled state
	 * @details This class represents the disabled state.
	 * Disables the axis motor and unlocks the magnets.
	*/
	class DisabledState : public State
	{
	private:
		/// @brief The axis data reference
		AxisData& axisData;
	public:
		/// @brief Constructs a new DisabledState object
		/// @param axisData The axis data reference
		DisabledState(AxisData& axisData);
		~DisabledState();

		void tick() override;
		void reset() override;
		void exit() override;
	};
}
