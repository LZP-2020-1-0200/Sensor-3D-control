
#include "stepperState/idleState.h"
using namespace stepperState;
IdleState::IdleState(AxisData& axisData) : axisData(axisData){
}

IdleState::~IdleState() {
}

void IdleState::reset() {
	axisData.direction = AxisData::directionE::PAUSE;
}


void IdleState::tick() {
	//Serial.print("idle tick\r\n");
}

void IdleState::exit() {
	
}