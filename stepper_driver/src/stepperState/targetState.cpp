
#include "stepperState/targetState.h"
namespace stepperState
{
	TargetState::TargetState(AxisData& axisData) : 
		movementData(axisData){
		
	}

	TargetState::~TargetState() {
	}

	void TargetState::reset() {
		//Serial.print("target enter\r\n");
		state = 0;
	}

	void TargetState::tick() {
		const int pos = movementData.axisData.stepper.getPosition();
		switch (state)
		{
		case 0:
			movementData.axisData.direction = AxisData::directionE::UP;
			// TODO move out *5/4 to a function
			if (pos >= movementData.targetPosition+((movementData.axisData.wiggle*5)/4)) {
				state=1;
			} else if(movementData.axisData.end.getState()) {
				// TODO: needs error reporting
				done();
			}
			break;
		case 1:
			movementData.axisData.direction = AxisData::directionE::DOWN;
			if (pos <= movementData.targetPosition) {
				done();
			} else if(movementData.axisData.start.getState()) {
				// TODO: needs error reporting
				done();
			}
			break;
		default:
			state = 0;
			break;
		}
	}

	void TargetState::exit() {
		movementData.axisData.direction = AxisData::directionE::PAUSE;
		
	}


} // namespace stepperState
