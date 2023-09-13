/**
 * @file stepper.h
 * @brief Contains the Stepper class
 * @details This file contains the Stepper class.
*/
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

/**
 * @class Stepper
 * @brief A class that represents a stepper motor
 * @details This class represents a stepper motor. It is used to control the stepper motors.
 * It hooks directly into the internal microcontroller registers to control the stepper motors.
 * @warning Can only use the stepper if all pins are on the same register
 * @see Stepper::motorData
*/
class Stepper{
private:
    int position=0;
    uint8_t offset=0;
public:
    struct motorData
    {
        /// @brief pull-up port register for writing
        volatile uint8_t* port;
        /// @brief data direction register for setting write mode
        volatile uint8_t* dataDirRegister;
        /// @brief pin numbers for the pull-up port
        int pins[4];
        motorData( volatile uint8_t*,  volatile uint8_t*, int, int, int, int);
    };


private:
    /// @brief The motor data
    motorData motor;
    /// @brief The motor pins
    const uint8_t motor_pins;
    /// @brief The motor mask
    const uint8_t motor_mask;
    
public:
    Stepper(motorData);
    
    /// @brief clears all motor bits to unlock all magnets
    void unlock(void);

    /// @brief reengages the magnets to lock the motor
    void lock(void);

    /// @brief steps forward one step
    void forward(void);

    /// @brief steps backward one step
    void backward(void);

    /// @brief retrieves the position
    /// @return the internal position coordinate
    int getPosition(void) const;

    /// @brief resets the internal position counter to 0
    void resetPosition(void);

    /// @brief performs a reset on the stepper
    void reset(void);

    /// @brief Static reference to the X stepper
    static Stepper xStepper;
    /// @brief Static reference to the Y stepper
    static Stepper yStepper;
    /// @brief Static reference to the Z stepper
    static Stepper zStepper;
};


#endif /* !STEPPER_H */