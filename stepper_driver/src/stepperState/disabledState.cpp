
#include "stepperState/disabledState.h"
using namespace stepperState;
DisabledState::DisabledState(AxisData& axisData) : axisData(axisData){
}

DisabledState::~DisabledState() {
}

void DisabledState::reset() {
	axisData.direction = AxisData::directionE::DISABLED;
}

void DisabledState::tick() {
	//Serial.print("disabled tick\r\n");
}

void DisabledState::exit() {
	
}