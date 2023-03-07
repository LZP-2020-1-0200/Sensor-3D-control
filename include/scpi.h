/* scpi.h */
#ifndef SCPI_H
#define SCPI_H

#define MAX_CMD_LEN 80
#define TX_EOL "\n"

class SCPI
{
private:
    char cmdLine[MAX_CMD_LEN + 1] = {0}; // buffer
    int charPos = 0;                     // current char position

    void parse(char *cmd, const int len);

public:
    SCPI(/* args */) {}
    ~SCPI() {}
    void addChar(char);
};
extern SCPI scpi;

class Command
{
private:
    /* data */
public:
    Command(const char *, void (*)(const char *));
    Command(void (*)(const char *)); // display "command not found" error message

    ~Command(){};
    const char *cmd;
    const int cmd_len;
    void (*func)(const char *);
};

#endif /* !SCPI_H */