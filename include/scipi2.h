#include <Arduino.h>

#define SCIPI_BUFFER_SIZE 127
#define SCIPI_MAX_ARGC 16
namespace scipi{

    class Command
    {
    private:
        void (*func)(int, char**)=nullptr;
        void (*get)()=nullptr;
        
        int cmdInd(char*, int);
    public:
        struct ChildCMD
        {
            const char* txt;
            Command* cmd;
        };
        const ChildCMD* subcommands;
        int childCMDCount;
        Command(void (*func)(int, char**),void (*get)(), const ChildCMD* subCMD, int childCMDCount)
            : func(func), get(get),
              subcommands(subCMD), childCMDCount(childCMDCount){}
        Command(void (*func)(int, char**),void (*get)())
            : func(func), get(get),
              subcommands(nullptr), childCMDCount(0){}
        ~Command(){};

        void parse(HardwareSerial&, char*);

    };

    class scipi2
    {
    private:
        HardwareSerial& serial;
        char input[SCIPI_BUFFER_SIZE+1];
        int inBufIndex=0;
        Command cmd;
        
    public:
        scipi2(HardwareSerial& serial, Command cmd): serial(serial), cmd(cmd){};
        ~scipi2();

        void update();
    };

    
    

}


