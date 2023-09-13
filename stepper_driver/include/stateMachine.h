#include "state.h"
#pragma once

class StateMachine
{
	private:
		
		// The current state of the state machine
		State* currentState;
	public:
		void setState(State* newState);
		State* getState() const;
		virtual void tick() = 0;
};
