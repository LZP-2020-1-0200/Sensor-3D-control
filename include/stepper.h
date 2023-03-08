/* File stepper.h */
#ifndef STEPPER_H
#define STEPPER_H
#include <Arduino.h>

enum stepper_direction_t
{
    STEPPER_DOWN = -1,
    STEPPER_PAUSE = 0,
    STEPPER_UP = 1
};

#define STEPPER_LINE1 15
#define STEPPER_LINE2 13
#define STEPPER_LINE3 12
#define STEPPER_LINE4 14

#define MIN_STEP_DELAY_USEC 1000
#define MAX_STEP_DELAY_USEC 10000000

class Stepper
{
private:
    /* data */
    int position;
    stepper_direction_t direction;
    uint32_t prev_usec;
    uint32_t step_delay_usec;

public:
    Stepper(/* args */){};
    ~Stepper(){};
    void init(void);

    int exec(const uint32_t &);
    int get_position(void) const { return position; }
    void set_direction(stepper_direction_t &dir) { direction = dir; }
//    void set_direction(const char *dstr);
    stepper_direction_t get_direction(void) const { return direction; }

    uint32_t get_step_delay_usec(void) const { return step_delay_usec; }
    void delay(const char *a);
};

extern Stepper stepper;

#endif /* !STEPPER_H */