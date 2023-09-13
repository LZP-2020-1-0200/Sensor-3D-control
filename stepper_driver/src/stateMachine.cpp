
#include "stateMachine.h"

void StateMachine::setState(State* newState) {
	currentState->exit();
	currentState = newState;
	currentState->enter();
}

State* StateMachine::getState() const {
	return currentState;
}