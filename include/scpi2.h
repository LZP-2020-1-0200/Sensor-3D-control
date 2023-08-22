#include <Arduino.h>

#define SCIPI_BUFFER_SIZE 127
#define SCIPI_MAX_ARGC 16


namespace scpi{
    

    class Command
    {
    public:
        struct ChildCMD
        {
            const char* txt;
            Command* cmd;
        };
    private:
        int (* const func)(int, char**)=nullptr;
        void (* const get)()=nullptr;
        
        int cmdInd(char*, int);
        const ChildCMD* subcommands;
        const size_t childCMDCount;
    public:
        Command(int (* const func)(int, char**), void (* const get)(), const ChildCMD* subCMD, int childCMDCount)
            : func(func), get(get),
              subcommands(subCMD), childCMDCount(childCMDCount){}
        template<size_t N>
        Command(int (* const func)(int, char**), void (* const get)(), const ChildCMD(&subCMD)[N] )
            : func(func), get(get),
              subcommands(subCMD), childCMDCount(N){}
        Command(int (* const func)(int, char**), void (* const get)())
            : func(func), get(get),
              subcommands(nullptr), childCMDCount(0){}
        Command(int (* const func)(int, char**))
            : func(func), get(nullptr),
              subcommands(nullptr), childCMDCount(0){}
        ~Command(){};

        void parse(HardwareSerial&, char*);

    };

    class scpi2
    {
    private:
        HardwareSerial& serial;
        char input[SCIPI_BUFFER_SIZE+1];
        int inBufIndex=0;
        Command cmd;
        
    public:
        scpi2(HardwareSerial& serial, Command cmd): serial(serial), cmd(cmd){};
        ~scpi2();

        void update();
    };

    
    

}


