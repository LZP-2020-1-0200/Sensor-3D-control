
#include "stepperState/stepperStateMachine.h"
using namespace stepperState;
StepperStateMachine::StepperStateMachine(AxisData& axisData) : 
    axisData(axisData),
    idleState(axisData),
    disabledState(axisData),
    targetState(axisData),
    homingState(axisData) {
        setState(&disabledState);
}

StepperStateMachine::~StepperStateMachine()
{
}

/*State& StepperStateMachine::getState(AxisData::mode mode) {
    switch (mode)
    {
    case AxisData::mode::idle:
        return idleState;
        break;
    case AxisData::mode::disabled:
        return disabledState;
        break;
    case AxisData::mode::target:
        return targetState;
        break;
    default:
        // Should never happen, quietly return idle state
        return idleState;
        break;
    }
    // Should never happen, quietly return idle state
    return idleState;
}*/

void StepperStateMachine::tick() {
    
    State* currentState = getState();
    if(currentState->isDone()){
        // target -> default
        if(currentState == &targetState){
            setState(defaultState);
        } else
        // homing -> default
        if(currentState == &homingState) {
            setState(defaultState);
        }
    }
    getState()->tick();
}

void StepperStateMachine::stepperLockByDefault(bool lock) {
    if(lock) {
        defaultState = &idleState;
    } else {
        defaultState = &disabledState;
    }
}
void StepperStateMachine::target(int targetPosition) {
    targetState.movementData.targetPosition = targetPosition;
    setState(&targetState);
}

void StepperStateMachine::home() {
    setState(&homingState);
}

void StepperStateMachine::disable() {
    setState(&disabledState);
}

void StepperStateMachine::idle() {
    setState(&idleState);
}

StepperStateMachine::mode StepperStateMachine::getMode() const {
    if(getState() == &idleState) {
        return mode::idle;
    } else if(getState() == &disabledState) {
        return mode::disabled;
    } else if(getState() == &targetState) {
        return mode::target;
    } else if(getState() == &homingState) {
        return mode::homing;
    } else {
        // Should never happen, quietly return disabled
        // TODO: error reporting
        return mode::disabled;
    }
}

StepperStateMachine::mode StepperStateMachine::getDefaultMode() const {
    if(defaultState == &idleState) {
        return mode::idle;
    } else if(defaultState == &disabledState) {
        return mode::disabled;
    } else if(defaultState == &targetState) {
        return mode::target;
    } else if(defaultState == &homingState) {
        return mode::homing;
    } else {
        // Should never happen, quietly return disabled
        return mode::disabled;
    }
}