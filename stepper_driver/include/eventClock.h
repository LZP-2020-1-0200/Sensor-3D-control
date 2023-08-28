#include <Arduino.h>

class EventClock
{
private:
	EventClock(/* args */);
public:
	const uint16_t TIMER_VALUE = 1999;
	~EventClock();
	EventClock(EventClock const&) = delete; 
	EventClock& operator=(EventClock const&) = delete;

	//* retrieves the clock instance
	static EventClock& getInstance(void);

	//* updates all classes, tied to internal timer
	void tick(void);
};

