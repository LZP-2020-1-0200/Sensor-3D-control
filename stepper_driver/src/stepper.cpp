#include "stepper.h"

// constrain to this file
static const uint8_t sequence[] = //{(1 << DDB4), (1 << DDB5), (1 << DDB6), (1 << DDB7)};
{
    0b1100,
    0b0100,
    0b0110,
    0b0010,
    0b0011,
    0b0001,
    0b1001
};

Stepper::motorData::motorData(
    volatile uint8_t* port,
    volatile uint8_t* dataDirRegister,
    int pin1, int pin2, int pin3, int pin4)
    : port(port),
      dataDirRegister(dataDirRegister),
      pins{pin1, pin2, pin3, pin4} {
    
};

Stepper::Stepper(motorData motor)
    : motor(motor),
      motor_pins(
        (1<<motor.pins[0]) |
        (1<<motor.pins[1]) |
        (1<<motor.pins[2]) |
        (1<<motor.pins[3])
        ), motor_mask(~motor_pins) {
    cli();
    //set motor pins as outputs
    *(motor.dataDirRegister) |= motor_pins;
    sei();
};

void Stepper::unlock(void){
    *(motor.port) &= motor_mask;
}

void Stepper::lock(void){
    volatile uint8_t stepper_bits = *(motor.port) & motor_mask;// clear all motor bits
    uint8_t seqN = (position + offset) & 7;
    for(int i=0;i<4;i++){
        stepper_bits|= (0b1&(sequence[seqN]>>i))<<motor.pins[i];
    }
    *(motor.port) = stepper_bits;
}

void Stepper::forward(void) {
    position++;
    lock();
}

void Stepper::backward(void){
    position--;
    lock();
}

int Stepper::getPosition(void) const {
    return position;
}

void Stepper::resetPosition(void){
    offset = (position + offset) & 7;
    position = 0;
}

void Stepper::reset(void){
    resetPosition();
    unlock();
    offset = 0;
    position = 0;
}


#define STEPPER_SETUP(port, pin1, pin2, pin3, pin4) \
    &PORT ## port,\
    &DDR ## port,\
    DD ## port ## pin1,\
    DD ## port ## pin2,\
    DD ## port ## pin3,\
    DD ## port ## pin4

#define STEPPER_SETUP_R(port, pin1, pin2, pin3, pin4) STEPPER_SETUP(port, pin4, pin3, pin2, pin1)

Stepper Stepper::yStepper{motorData{STEPPER_SETUP_R(D,0,4,1,7)}};

Stepper Stepper::xStepper{motorData{STEPPER_SETUP(B,4,6,5,7)}};

Stepper Stepper::zStepper{motorData{STEPPER_SETUP(F,4,6,5,7)}};
