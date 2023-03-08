#include "scpi.h"
#include <Arduino.h>
#include <string.h>
#include "led.h"
#include "stepper.h"
SCPI scpi;

void SCPI::addChar(char ch)
{
    if (ch == 10 || ch == 13)
    {
        ch = 0; // replace char by zero terminator
    }
    cmdLine[charPos++] = ch; // insert symbol

    if (ch == 0)
    {
        parse(cmdLine, charPos - 1);
        charPos = 0;
    }
    if (charPos >= MAX_CMD_LEN)
    { // buffer overflow
        charPos = 0;
    }
}

Command::Command(const char *cmd_str, void (*ptr_func)(const char *)) //
    : cmd(cmd_str),
      cmd_len(strlen(cmd_str)),
      func(ptr_func)
{ // Regular constructor for command-function pairs
}

Command::Command(void (*ptr_func)(const char *)) //
    : cmd(nullptr),
      cmd_len(0),
      func(ptr_func)
{ // Special constructor for handling unknown commands
} // This error function must be the last one in the cmd_list!

void HELP_func(const char *); // implementation requires cmd_list, see below

Command cmd_list[] = {
    // command-function pairs
    Command("*IDN?", [](const char *a)
            { Serial.print("SCPI demo" TX_EOL); }),
    Command("LED", [](const char *a)
            { led.update(a); }),
    Command("STEP:DELAY", [](const char *a)
            { stepper.delay(a); }),
    Command("STEP:INIT", [](const char *a)
            { stepper.init(); }),

    Command("HELP", HELP_func), //
    Command([](const char *a) { // error function must be last!
        Serial.print("ERROR: UNKNOWN COMMAND ");
        Serial.print(a);
        Serial.print(TX_EOL);
    })};
void HELP_func(const char *args)
{
    Serial.write("Available commands:" TX_EOL);
    for (Command *cl = cmd_list; cl->cmd; cl++)
    {
        Serial.write(cl->cmd);
        Serial.write(TX_EOL);
    }
}

void SCPI::parse(char *cmd, const int len)
{
    if (len) // not an empty line
    {
        Command *cl = cmd_list;
        int cmd_num = 0;
        for (; cl->cmd; cl++)
        { // search for known commands
            if (0 == strncasecmp(cmd, cl->cmd, cl->cmd_len))
            { // known command found
                char *argument = &cmd[cl->cmd_len];
                while (*argument == ' ' || *argument == '\t')
                { // step over empty spaces between command and arguments
                    argument++;
                }
                cl->func(argument); // call the known function
                return;
            }
            cmd_num++;
        }
        cl->func(cmd);
    }
}
