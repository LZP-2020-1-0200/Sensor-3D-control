#include "stepper.h"
#include "endSwitch.h"

class StepperController
{
public:
    enum class direction_t
    {
        STEPPER_DOWN = -1,
        STEPPER_PAUSE = 0,
        STEPPER_UP = 1,
        STEPPER_DISABLED
    };

    enum class mode{
        target,
        homing,
        idle,
        disabled
    };
private:
    // which way is it currently going
    direction_t direction=direction_t::STEPPER_PAUSE;

    mode currentMode=mode::target;
    mode defaultMode=mode::disabled;

    // uint32_t prev_usec;
    // uint32_t step_delay_usec;
    volatile uint16_t direction_change_timer=0;
    volatile uint16_t millisecond_counter = 0;
    volatile uint16_t step_delay_milliseconds = 5;
    
    /*
    // pullupPort pointer
    volatile uint8_t *pullupPort;
    
    // register for pullupPort modes (read/write modes)
    volatile uint8_t *dataDirRegister;
    
    // bit numbers for the correct pins
    const int stepperPins[4];

    */
    Stepper& motor;
    endSwitch& start;
    endSwitch& end;
    
public:
    
    // How long to wait if the stepper has to swap directions
    unsigned int direction_change_delay=0;
    
    StepperController(Stepper&, endSwitch&, endSwitch&);
    ~StepperController();
    static StepperController* motors[STEPPER_COUNT];

    int get_position(void) const;

    direction_t get_direction(void) const { return direction; }
    
    void tick();
    // uint32_t get_step_delay_usec(void) const { return step_delay_usec; }
    bool setDelay(const char *a);

    // Set the target position for the stepper to go to
    // Enables the stepper if it is disabled
    void setTarget(int);

    /** 
     * Move the stepper downward to find the end switch and recalibrate
     * internal position
     *
     * Enables the stepper if it is disabled
     */
    void home(void);

    // Unlocks the stepper for power saving
    void Disable(void);

    // Locks the stepper
    void Enable(void);

    bool isEnabled(void) const;
    
    // Make a complete reset of the stepper and switches
    void reset(void);

    // Get current mode of the stepper
    mode getMode(void) const { return currentMode; }

    // Get default mode for the stepper
    mode getDefaultMode(void) const { return defaultMode; }

    // Set default mode for the stepper
    inline void setDefaultMode(mode m) { defaultMode = m; }

    // Get start switch state
    bool getStartSwitch(void) const { return start.getState(); }

    // Get end switch state
    bool getEndSwitch(void) const { return end.getState(); }

private:
    // Target position that the stepper should go to
    enum Tstate{
        T_START,
        T_OVERSHOOT,
        T_APPROACH
    };
    Tstate targetState=T_START;
    int targetPos = 0;
    bool targetedMove();

    int homingState = 0;
    unsigned int homingOvershootCounter = 0;
    int fWiggle = 0;
    int bWiggle = 0;
    int wiggle = 0;
    bool homingMove();
    
    void updateStepper();
    void updateTimers();
    direction_t deltaToDirection(int delta);

public:
    static StepperController xMotor;
    static StepperController yMotor;
    static StepperController zMotor;
};
