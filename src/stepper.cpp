#include "stepper.h"
#include <avr/interrupt.h>

Stepper stepper;

const uint8_t stepper1_pins = (1 << DDB4) | (1 << DDB5) | (1 << DDB6) | (1 << DDB7);
const uint8_t stepper1_mask = ~stepper1_pins;

void Stepper::init(void)
{
    cli();

    DDRB |= stepper1_pins;

    TCCR3A = 0;

    const uint16_t OneKHz = 1999; // 16000000/8/1000-1
    OCR3A = OneKHz;               // skait. slieksnis

    TCCR3B = (1 << WGM32) | // CTC mode
             (1 << CS31);   // prescaler 1/8

    TIMSK3 |= 1 << OCIE3A; // pārtr. maska
    sei();
}

static volatile uint16_t millisecond_counter = 0;
static volatile uint16_t delay_milliseconds = 5;

const uint8_t sequence[] = {(1 << DDB4), (1 << DDB5), (1 << DDB6), (1 << DDB7)};

volatile int xpos = 0;
volatile int direction = 1;

ISR(TIMER3_COMPA_vect)
{
    if (++millisecond_counter >= delay_milliseconds)
    {
        volatile uint8_t stepper_1_bits = 0;//PORTB & stepper1_mask;
        xpos += direction;
        stepper_1_bits |= sequence[xpos & 0x03];

        PORTB = stepper_1_bits; // mirgo
        millisecond_counter = 0;
    }
}

void Stepper::delay(const char *a)
{
    delay_milliseconds = (uint16_t)atoi(a);
}