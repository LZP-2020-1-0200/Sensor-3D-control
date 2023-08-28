#include "eventClock.h"
#include "endSwitch.h"
#include "stepperController.h"
#include <avr/interrupt.h>

EventClock::EventClock(/* args */)
{
    // Izveido taimeri
    cli();
    TCCR3A = 0;

    const uint16_t OneKHz = TIMER_VALUE; // 16000000/8/1000-1
    OCR3A = OneKHz;               // skait. slieksnis

    TCCR3B = (1 << WGM32) | // CTC mode
             (1 << CS31);   // prescaler 1/8

    TIMSK3 |= 1 << OCIE3A; // pārtr. maska
    sei();
}

EventClock::~EventClock()
{

}
EventClock& EventClock::getInstance(void){
	static EventClock INSTANCE;
	return INSTANCE;
}

void EventClock::tick(void){
    switchUpdate();
    StepperController::xMotor.tick();
    StepperController::yMotor.tick();
    StepperController::zMotor.tick();
}

//leave clock local to file
static EventClock& clock = EventClock::getInstance();

// taimeris
ISR(TIMER3_COMPA_vect)
{
    clock.tick();
}