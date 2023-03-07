#include "led.h"
#include "scpi.h"
#include <string.h>
Led led;
void Led::init(const uint8_t &ledpin)
{
    led_pin = ledpin;
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, led_state ^ active_low);
}
void Led::write_status(void)
{
    Serial.write(led_state ? off_str : on_str);
    Serial.write(TX_EOL);
}

void Led::update(const char *arg)
{
    const size_t arg_len = strlen(arg);
    if (arg_len)
    {
        if (0 == strncasecmp(arg, on_str, on_len))
        {
            led_state = 0;
            digitalWrite(led_pin, led_state ^ active_low);
        }
        else if (0 == strncasecmp(arg, off_str, off_len))
        {
            led_state = 1;
            digitalWrite(led_pin, led_state ^ active_low);
        }
        else
            Serial.write("ERROR: invalid LED argument" TX_EOL);
    }
    else
    {
        write_status();
    }
}