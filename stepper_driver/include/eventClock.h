#include <Arduino.h>

/**
 * @class EventClock
 * @brief A class that represents the internal clock
 * @details This class represents the internal clock. 
 * It is used to update all classes that are tied to the internal timer.
 * It attaches to the timer interrupt and updates all classes when the interrupt is triggered.
 * It is a singleton class.
*/
class EventClock
{
private:
	EventClock(/* args */);
public:
	const uint16_t TIMER_VALUE = 1999;
	~EventClock();
	EventClock(EventClock const&) = delete; 
	EventClock& operator=(EventClock const&) = delete;

	/// @brief retrieves the clock instance
	static EventClock& getInstance(void);

	/// @brief updates all classes, tied to internal timer
	void tick(void);
};

