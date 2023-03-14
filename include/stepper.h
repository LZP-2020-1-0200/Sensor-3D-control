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
#define STEPPER_COUNT 3
class Stepper
{
private:
    /* data */
    int position=0;
    stepper_direction_t direction=STEPPER_PAUSE;
    uint32_t prev_usec;
    uint32_t step_delay_usec;
    volatile uint16_t direction_change_timer=0;
    volatile uint16_t millisecond_counter = 0;
    volatile uint16_t delay_milliseconds = 5;
    volatile uint8_t *port;
    volatile uint8_t *portRegister;
    const int stepperPins[4];
    const uint8_t stepper1_pins = (1 << DDB4) | (1 << DDB5) | (1 << DDB6) | (1 << DDB7);
    const uint8_t stepper1_mask = ~stepper1_pins;
public:
    int targetPos=0;
    int direction_change_steps=0;
    Stepper(volatile uint8_t* port, volatile uint8_t* portRegister, int pinA, int pinB, int pinC, int pinD)
        : port(port), portRegister(portRegister), stepperPins({pinA,pinB,pinC, pinD}),
        stepper1_pins((1<<pinA)|(1<<pinB)|(1<<pinC)|(1<<pinD)), stepper1_mask(~stepper1_pins){

        cli();
        *portRegister |= stepper1_pins;//add stepper pins as outputs
        sei();
    };
    ~Stepper(){};
    static void init(void);
    static Stepper* motors[STEPPER_COUNT];

    int exec(const uint32_t &);
    int get_position(void) const { return position; }
    void set_direction(stepper_direction_t dir);
//    void set_direction(const char *dstr);
    stepper_direction_t get_direction(void) const { return direction; }
    void inline move();
    uint32_t get_step_delay_usec(void) const { return step_delay_usec; }
    void delay(const char *a);
    void lock(bool x);
};


#endif /* !STEPPER_H */