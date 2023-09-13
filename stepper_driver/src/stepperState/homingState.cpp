
#include "stepperState/homingState.h"


namespace stepperState
{
	HomingState::HomingState(AxisData& axisData) : axisData(axisData)
	{

	}

	HomingState::~HomingState()
	{

	}

	void HomingState::tick()
	{
		int delta2;
		switch (stage)	
		{
		case 0:
			// Move off the switch
			axisData.direction = AxisData::directionE::UP;
			if(!axisData.start.getState() || axisData.end.getState()){
				referencePosition = axisData.stepper.getPosition();
				stage = 1;
			}else break;
		case 1:
			// Overshoot a bit
			axisData.direction = AxisData::directionE::UP;
			if(axisData.stepper.getPosition() > referencePosition + 50 || axisData.end.getState()){
				stage = 2;
				referencePosition = axisData.stepper.getPosition();
			} else break;
		case 2:
			// Move back to the switch
			axisData.direction = AxisData::directionE::DOWN;
			if(axisData.start.getState()){
				stage = 3;
				referencePosition = axisData.stepper.getPosition();
			} else break;
		case 3:
			// Overshoot a bit
			axisData.direction = AxisData::directionE::DOWN;
			if(axisData.stepper.getPosition() < referencePosition - 10){
				stage = 4;
				referencePosition = axisData.stepper.getPosition();
			} else break;
		case 4:
			// Move off the switch
			axisData.direction = AxisData::directionE::UP;
			if(!axisData.start.getState()){
				wiggle = axisData.stepper.getPosition() - referencePosition;
				referencePosition = axisData.stepper.getPosition();
				stage = 5;
			} else break;
		case 5:
			// Touch the switch again
			axisData.direction = AxisData::directionE::DOWN;
			if(axisData.start.getState()){
				delta2 = referencePosition - axisData.stepper.getPosition();
				wiggle = (wiggle > delta2) ? wiggle : delta2;
				axisData.wiggle = wiggle;
				done();
				return;
			} else break;
		default:
			break;
		}

	}

	void HomingState::reset()
	{
		stage = 0;
		wiggle = 0;
		referencePosition = axisData.stepper.getPosition();
	}

	void HomingState::exit()
	{
	}
}; // namespace stepperState