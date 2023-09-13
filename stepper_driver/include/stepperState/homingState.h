
#include "stateMachine.h"
#include "state.h"
#include "axisData.h"
namespace stepperState
{
	/**
	 * @brief State for homing the stepper motor
	 * @details This state is used to home the stepper motor.
	 * It is entered when the homing command is received.
	 * The motor will wiggle to ensure it is in a valid position,
	 * then it will move until the homing switch is triggered.
	 * Once the switch is triggered, the motor will move off the switch
	 * and then move back to the switch at a slower speed.
	*/
	class HomingState : public State
	{
		public:
			/// @brief Generates a new homing state instance
			/// @param axisData The axis data reference
			HomingState(AxisData& axisData);
			~HomingState();
			void tick() override;
			void reset() override;
			void exit() override;
		private:
			AxisData& axisData;
			int stage = 0;
			int referencePosition = 0;
			int wiggle = 0;
	};
} // namespace stepperState