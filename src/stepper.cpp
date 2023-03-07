#include "stepper.h"
#include <avr/interrupt.h>

Stepper stepper;

void Stepper::init(void)
{
    cli();
    DDRB |= (1 << DDB4);

    TCCR3A = 0;
    // TCCR3B = 0;

    OCR3A = 15625;                      // skait. slieksnis
    TCCR3B = (1 << WGM32) |             // CTC mode
             (1 << CS30) | (1 << CS32); // pres-1024
    TIMSK3 |= 1 << OCIE3A;              // pārtr. maska

    sei();
}

ISR(TIMER3_COMPA_vect)
{
    PORTB ^= 1 << PORTB4; // mirgo PC7
}
