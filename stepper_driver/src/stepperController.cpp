#include "stepperController.h"
#include "stepper.h"
#include "endSwitch.h"
#include "reporter.h"

StepperController* StepperController::motors[STEPPER_COUNT];

StepperController::StepperController(Stepper& motor, endSwitch& startSwitch, endSwitch& endSwitch)
    : motor(motor), start(startSwitch), end(endSwitch) { };

StepperController::~StepperController(){

}

int StepperController::get_position(void) const {
    return motor.getPosition();
}

void StepperController::updateTimers(){
    if(direction_change_timer > 0) direction_change_timer--;
    if(millisecond_counter>step_delay_milliseconds){
        millisecond_counter = 0;
        updateStepper();
    }
    millisecond_counter++;
}

StepperController::direction_t StepperController::deltaToDirection(int delta){
    if (delta == 0) return StepperController::direction_t::STEPPER_PAUSE;
    if (delta > 0) return StepperController::direction_t::STEPPER_UP;
    return StepperController::direction_t::STEPPER_DOWN;
}



void StepperController::home(void) {
    homingState = 0;
    homingOvershootCounter = 0;
    fWiggle = 0;
    bWiggle = 0;
    wiggle = 0;
    currentMode = mode::homing;
}

void StepperController::setTarget (int x) {
    targetPos = x;
    currentMode = mode::target;
    targetState = T_START;
}

void StepperController::tick(){
    start.update();
    end.update();
    updateTimers();
    //updateStepper();
    if(currentMode == mode::target) {
        if(targetedMove()){
            currentMode = defaultMode;
            Serial.print("reached.\r\n");
        }
    } else if(currentMode == mode::homing) {
        if(homingMove()) {
            currentMode = defaultMode;
            Serial.print("homed.\r\n");
        }
    } else if(currentMode == mode::idle) {
        direction = direction_t::STEPPER_PAUSE;
    } else if(currentMode == mode::disabled) {
        direction = direction_t::STEPPER_DISABLED;
    }
}

// this is essentially a state machine with the advantage
// of transitions happening on the same iteration
bool StepperController::homingMove(){
    Serial.print(homingState, DEC);
    Serial.print("\n");
    switch (homingState)
    {
        // move off of limit switch
        case 0:
        if (start.getState()) {
            direction = direction_t::STEPPER_UP;
            return false;
        }
        homingOvershootCounter = 0;
        homingState++;

        // overshoot
        case 1:
        if(homingOvershootCounter<1000*step_delay_milliseconds){
            homingOvershootCounter++;
            direction = direction_t::STEPPER_UP;
            return false;
        }
        homingState++;

        // approach switch
        case 2:
        if (!start.getState()) {
            direction = direction_t::STEPPER_DOWN;
            return false;
        }
        homingOvershootCounter = 0;
        homingState++;

        //small overshoot
        case 3:
        if(homingOvershootCounter<50*step_delay_milliseconds){
            homingOvershootCounter++;
            direction = direction_t::STEPPER_DOWN;
            return false;
        }
        homingState++;

        // overshoot a bit because the switch may release because
        // of the screw releasing pressure on the switch

        // count up wiggle steps
        case 4:
        if (start.getState()) {
            direction = direction_t::STEPPER_UP;
            fWiggle++;
            return false;
        }
        homingOvershootCounter = 0;
        homingState++;

        // overshoot
        case 5:
        if(homingOvershootCounter<50*step_delay_milliseconds){
            homingOvershootCounter++;
            direction = direction_t::STEPPER_UP;
            return false;
        }
        homingState++;


        // return to switch to set (0,0) and count down wiggle steps
        case 6:
        if (!start.getState()) {
            direction = direction_t::STEPPER_DOWN;
            bWiggle++;
            return false;
        }
        wiggle = (bWiggle>fWiggle) ? bWiggle : fWiggle;
        wiggle = wiggle/step_delay_milliseconds;
        motor.resetPosition();
        direction = direction_t::STEPPER_PAUSE;
        homingState++;
        Serial.print("bWiggle: ");
        Serial.print(bWiggle/step_delay_milliseconds, DEC);
        Serial.print("\r\n");
        Serial.print("fWiggle: ");
        Serial.print(fWiggle/step_delay_milliseconds, DEC);
        
    }
    return true;
}

// updates the steppers
bool StepperController::targetedMove(){
    switch (targetState)
    {
        case T_START:
        Serial.print("start\r\n");
        if (motor.getPosition() > targetPos) {
            targetState = T_APPROACH;
            targetedMove();
            return false;
        }
        targetState = T_OVERSHOOT;
        case T_OVERSHOOT:
        Serial.write("overshoot\r\n");
        if (targetPos > motor.getPosition() - (wiggle*4)/3) {
            if (end.getState()) {
                reportError("End switch reached before target");
                return true;
            }
            direction = direction_t::STEPPER_UP;
            return false;
        }
        targetState = T_APPROACH;
        case T_APPROACH:
        Serial.write("approach\r\n");
        if (targetPos < motor.getPosition()) {
            if (start.getState()) {
                reportError("End switch reached before target");
                direction = direction_t::STEPPER_PAUSE;
                return true;
                
            }
            direction = direction_t::STEPPER_DOWN;
            return false;
        }
    }
    direction = direction_t::STEPPER_PAUSE;
    return true;
}

void StepperController::updateStepper(){
    //if (isDelayed()) return;

    if(direction==StepperController::direction_t::STEPPER_PAUSE) {
        motor.lock();
    } else if (direction == direction_t::STEPPER_UP) {
        motor.forward();
    } else if (direction == direction_t::STEPPER_DOWN) {
        motor.backward();
    } else if (direction == direction_t::STEPPER_DISABLED) {
        motor.unlock();
    }
}

// Sets step delay for steppers
bool StepperController::setDelay(const char *a)
{
    const int MAX_DIGIT_COUNT = 8;
    // check if all chars are digits
    for(size_t i = 0; a[i] != '\0' && i <= MAX_DIGIT_COUNT; i++) {
        if(!('0' <= a[i] && a[i] >= '9')){
            return false;
        }
        // max number limitation
        if(i == MAX_DIGIT_COUNT) return false;
    }
    step_delay_milliseconds = (uint16_t)atoi(a);
    return true;
}

void StepperController::Enable() {
    currentMode = mode::idle;
    direction = direction_t::STEPPER_PAUSE;
    motor.lock();
}

void StepperController::Disable() {
    currentMode = mode::disabled;
    direction = direction_t::STEPPER_DISABLED;
    motor.unlock();
}

bool StepperController::isEnabled(void) const {
    return currentMode != mode::disabled;
}

void StepperController::reset(void) {
    currentMode = mode::disabled;
    direction_change_delay = 0;
    direction = direction_t::STEPPER_DISABLED;
    motor.reset();
    targetState = T_START;
    homingState = 0;
    homingOvershootCounter = 0;
    wiggle = 0;
    fWiggle = 0;
    bWiggle = 0;
    targetPos = 0;
    step_delay_milliseconds = 0;
    motor.unlock();
    end.reset();
    start.reset();
}

StepperController StepperController::xMotor(
    Stepper::xStepper,
    endSwitch::Xlow,
    endSwitch::Xhigh
);
StepperController StepperController::yMotor(
    Stepper::yStepper,
    endSwitch::Ylow,
    endSwitch::Yhigh
);
StepperController StepperController::zMotor(
    Stepper::zStepper,
    endSwitch::Zlow,
    endSwitch::Zhigh
);