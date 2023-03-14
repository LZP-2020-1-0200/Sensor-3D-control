#include "stepper.h"
#include <avr/interrupt.h>

Stepper* Stepper::motors[STEPPER_COUNT];

const uint8_t stepper1_pins = (1 << DDB4) | (1 << DDB5) | (1 << DDB6) | (1 << DDB7);
const uint8_t stepper1_mask = ~stepper1_pins;

void Stepper::init(void)
{
    cli();
    TCCR3A = 0;

    const uint16_t OneKHz = 1999; // 16000000/8/1000-1
    OCR3A = OneKHz;               // skait. slieksnis

    TCCR3B = (1 << WGM32) | // CTC mode
             (1 << CS31);   // prescaler 1/8

    TIMSK3 |= 1 << OCIE3A; // pārtr. maska
    sei();
}


const uint8_t sequence[] = //{(1 << DDB4), (1 << DDB5), (1 << DDB6), (1 << DDB7)};
{
    0b1100,
    0b0110,
    0b0011,
    0b1001
};


ISR(TIMER3_COMPA_vect)
{
    for(int i=0;i<STEPPER_COUNT;i++){
        Stepper::motors[i]->move();
    }
}
void Stepper::set_direction(stepper_direction_t dir) { 
    if(direction!=0 && dir!=0)direction_change_timer=direction_change_steps;
    direction = dir; 
}
void inline Stepper::move(){
    if(direction_change_timer>0){
        direction_change_timer--;
        return;
    }
    int delta=targetPos-position;
    direction=(delta>0?STEPPER_UP:(delta<0?STEPPER_DOWN:STEPPER_PAUSE));
    if(direction==0)return;
    if (++millisecond_counter >= delay_milliseconds)
    {
        uint8_t seqN=position&3;
        volatile uint8_t stepper_1_bits = *port & stepper1_mask;// clear all motor bits
        position += direction;// update position
        for(int i=0;i<4;i++){
            stepper_1_bits|= (0b1&(sequence[seqN]>>i))<<stepperPins[i];
        }
        
        (*port) = stepper_1_bits; // turn on pins
        millisecond_counter = 0;
    }
}

void Stepper::delay(const char *a)
{
    delay_milliseconds = (uint16_t)atoi(a);
}
void Stepper::lock(bool x){
    volatile uint8_t stepper_1_bits = *port & stepper1_mask;// clear all motor bits
    if(x){
        uint8_t seqN=position&3;
        for(int i=0;i<4;i++){
            stepper_1_bits|= (0b1&(sequence[seqN]>>i))<<stepperPins[i];
        }
    }
    (*port) = stepper_1_bits; // turn on pins
}