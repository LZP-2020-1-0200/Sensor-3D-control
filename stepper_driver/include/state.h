/**
 * @file State.h
 * @brief Contains the State class
 * @details This file contains the State class.
 * It is used to implement the state machine.
 * @see State
*/
#pragma once

/**
 * @class State
 * @brief A class that represents a state
 * @details This class represents a state.
 * It is used to implement a state machine.
 * It is an abstract class.
*/
class State
{
private:
	/// @brief Whether or not the state has finished
	bool _done = false;
public:
	State();
	~State();

	void enter();

	void done();
	bool isDone() const;

	/**
	 * @brief The tick method, called for ticking the state forward.
	 * @details This method is called every tick of the state machine,
	 * when the state is active.
	*/
	virtual void tick()=0;

	/**
	 * @brief The enter method, initializes the state.
	 * @details This method should be called when the state is entered.
	 * It is used to initialize the state.
	*/
	virtual void reset()=0;

	/**
	 * @brief The exit method, cleans up the state.
	 * @details This method should be called when the state is exited.
	 * It is used to clean up the state.
	*/
	virtual void exit()=0;
};

