/**
 * @file stepperController.h
 * @brief Contains the StepperController class
 * @details This file contains the StepperController class.
 * @see StepperController
*/
#include "stepper.h"
#include "endSwitch.h"
#include "stepperState/stepperStateMachine.h"

/**
 * @class StepperController
 * @brief A class that represents a stepper motor and its end switches,
 * making it a complete axis.
 * @details This class represents a stepper motor and its end switches,
 * making it a complete axis. It is used to control the stepper motors.
 * Contains the logic for organized movement of the stepper motors.
 * Has a state machine that controls the stepper motors.
 * @see State
 * @see Stepper
 * @see EndSwitch
*/
class StepperController
{
public:
    /**
     * @brief A struct that represents the direction of the stepper motor
     * @details This struct represents the direction of the stepper motor.
     * It is used to control the stepper motors.
     * @see Stepper
     * @see StepperController
    */
    enum class direction_t
    {
        STEPPER_DOWN = -1, ///< The stepper motor is moving down
        STEPPER_PAUSE = 0, ///< The stepper motor is paused (magnets locked)
        STEPPER_UP = 1,    ///< The stepper motor is moving up
        STEPPER_DISABLED   ///< The stepper motor is disabled (magnets unlocked)
    };

    
private:
    /// @brief which way is the stepper currently going
    //direction_t direction=direction_t::STEPPER_DISABLED;

    /// @brief current mode of the stepper
    //mode currentMode=mode::disabled;

    /// @brief default mode of the stepper
    //mode defaultMode=mode::disabled;

    // uint32_t prev_usec;
    // uint32_t step_delay_usec;

    /// @brief The time in milliseconds to wait if the stepper has to swap directions
    /// @deprecated Not used anymore
    volatile uint16_t direction_change_timer=0;

    /// @brief The counter for the milliseconds passed since the last step
    volatile uint16_t millisecond_counter = 0;

    /// @brief The time in milliseconds between each step
    volatile uint16_t step_delay_milliseconds = 5;
    
    /*
    // pullupPort pointer
    volatile uint8_t *pullupPort;
    
    // register for pullupPort modes (read/write modes)
    volatile uint8_t *dataDirRegister;
    
    // bit numbers for the correct pins
    const int stepperPins[4];

    */

    /// @brief The stepper motor reference
    Stepper& motor;

    /// @brief The start end switch reference
    EndSwitch& start;

    /// @brief The end end switch reference
    EndSwitch& end;

    AxisData axisData;

    stepperState::StepperStateMachine stateMachine;
    
public:
    
    /// @brief How long to wait if the stepper has to swap directions
    /// @deprecated Not used anymore
    unsigned int direction_change_delay=0;
    
    /**
     * @brief The constructor for StepperController
     * @details This constructor initializes the StepperController.
     * @param stepper The stepper motor
     * @param start The start end switch
     * @param end The end end switch
    */
    StepperController(Stepper& stepper, EndSwitch& start, EndSwitch& end);
    ~StepperController();

    /**
     * @brief An array of all the StepperController objects.
     * @details This array contains all the StepperController objects.
     * It is used to iterate through all the StepperController objects.
     * Used by EventClock to call the tick method on all StepperController objects.
     * @see EventClock
    */ 
    static StepperController* motors[STEPPER_COUNT];

    /// @brief Fetches the latest position of the stepper
    /// @return an integer representing the position of the stepper
    int get_position(void) const;

    /**
     * @brief Gets the direction of the stepper
     * @return the direction of the stepper
    */
    AxisData::directionE get_direction(void) const { return axisData.direction; }
    
    /**
     * @brief Updates the stepper controller logic
    */
    void tick();
    // uint32_t get_step_delay_usec(void) const { return step_delay_usec; }

    /**
     * @brief Sets the time in milliseconds between each step
     * @param a The time in milliseconds between each step as a c-string
    */
    bool setDelay(const char *a);

    // Set the target position for the stepper to go to
    // Enables the stepper if it is disabled
    /**
     * @brief Sets the target position for the stepper to go to
     * @param target The target position for the stepper to go to
    */
    void setTarget(int target);

    /** 
     * @brief Move the stepper downward to find the end switch and recalibrate
     * internal position
     *
     * Enables the stepper if it is disabled
     */
    void home(void);

    /// @brief Unlocks the stepper for power saving
    void Disable(void);

    /// @brief Locks the stepper
    void Enable(void);

    /// @brief Check stepper status
    /// @return bool representing whether the stepper is enabled
    bool isEnabled(void) const;
    
    /// @brief Perform a complete reset of the stepper and switches
    void reset(void);

    /// @brief Get current mode of the stepper
    stepperState::StepperStateMachine::mode getMode(void) const { return stateMachine.getMode(); }

    /// @brief Get default mode for the stepper
    stepperState::StepperStateMachine::mode getDefaultMode(void) const { return stateMachine.getDefaultMode(); }

    /// @brief Set default mode for the stepper
    inline void setDefaultMode(stepperState::StepperStateMachine::mode m) {
        stateMachine.stepperLockByDefault(m==stepperState::StepperStateMachine::mode::idle);
    }

    /// @brief Get start switch state
    bool getStartSwitch(void) const { return start.getState(); }

    /// @brief Get end switch state
    bool getEndSwitch(void) const { return end.getState(); }

private:
    /// @brief Target position that the stepper should go to
    /// @deprecated Replaced by seperate state machines for each mode
    enum Tstate{
        T_START,
        T_OVERSHOOT,
        T_APPROACH
    };
    /// @deprecated Replaced by seperate state machines for each mode
    Tstate targetState=T_START;
    /// @deprecated Replaced by seperate state machines for each mode
    int targetPos = 0;

    /// @brief Ticks the targeted move state machine
    /// @return Weather the state machine is done
    /// @deprecated Replaced by seperate state machines for each mode
    bool targetedMove();

    /// @brief Homing state machine state
    /// @deprecated Replaced by seperate state machines for each mode
    int homingState = 0;
    /// @brief Homing state machine counter
    /// @deprecated Replaced by seperate state machines for each mode
    unsigned int homingOvershootCounter = 0;

    /// @brief Forward wiggle counter
    /// @deprecated Replaced by seperate state machines for each mode
    int fWiggle = 0;
    /// @brief Backward wiggle counter
    /// @deprecated Replaced by seperate state machines for each mode
    int bWiggle = 0;
    /// @brief Wiggle counter
    /// @deprecated Replaced by seperate state machines for each mode
    int wiggle = 0;

    /// @brief Ticks the homing state machine
    /// @return Weather the state machine is done
    /// @deprecated Replaced by seperate state machines for each mode
    bool homingMove();
    
    /// @brief Updates the stepper motor
    void updateStepper();

    /// @brief Updates the timers, ticks the stepper motor if timers are done
    void updateTimers();

    /// @brief converts a number to a direction
    /// @param delta The number to convert to a direction
    /// @return The direction that corresponds to the delta
    direction_t deltaToDirection(int delta);

    

public:
    /// @brief Static reference to the X stepper controller
    static StepperController xMotor;
    /// @brief Static reference to the Y stepper controller
    static StepperController yMotor;
    /// @brief Static reference to the Z stepper controller
    static StepperController zMotor;
};
