/* File stepper.h */
#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>


#define STEPPER_LINE1 15
#define STEPPER_LINE2 13
#define STEPPER_LINE3 12
#define STEPPER_LINE4 14

#define MIN_STEP_DELAY_USEC 1000
#define MAX_STEP_DELAY_USEC 10000000
#define STEPPER_COUNT 3

class Stepper{
private:
    int position=0;
    uint8_t offset=0;
public:
    struct motorData
    {
        //* pull-up port register for writing
        volatile uint8_t* port;
        //* data direction register for setting write mode
        volatile uint8_t* dataDirRegister;
        //* pin numbers for the pull-up port
        int pins[4];
        motorData( volatile uint8_t*,  volatile uint8_t*, int, int, int, int);
    };


private:
    motorData motor;
    const uint8_t motor_pins;
    const uint8_t motor_mask;
    
public:
    Stepper(motorData);
    
    //* clears all motor bits to unlock all magnets
    void unlock(void);

    //* reengages the magnets
    void lock(void);

    //* steps forward
    void forward(void);

    //* steps backward
    void backward(void);

    //* retrieves position
    int getPosition(void) const;

    //* resets position to 0
    void resetPosition(void);

    //* resets the stepper
    void reset(void);

    static Stepper xStepper;
    static Stepper yStepper;
    static Stepper zStepper;
};


#endif /* !STEPPER_H */