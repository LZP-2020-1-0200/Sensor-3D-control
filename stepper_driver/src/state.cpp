#include "state.h"

State::State() {
}

State::~State() {
}
void State::done() {
	_done = true;
}
bool State::isDone() const {
	return _done;
}

void State::enter() {
	_done = false;
	reset();
}