/* led.h */
#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led
{
private:
    /* data */
    uint8_t led_state = 1;
    uint8_t led_pin = LED_BUILTIN;
    void write_status(void);

public:
    Led(/* args */){};
    ~Led(){};
    void init(const uint8_t &ledpin);
    void update(const char *arg);
    const char *on_str = "ON";
    const size_t on_len = strlen(on_str);
    const char *off_str = "OFF";
    const size_t off_len = strlen(off_str);
};
extern Led led;

#endif /* !LED_H */