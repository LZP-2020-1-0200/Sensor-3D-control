/**
 * @file scpi2.h
 * @brief Contains the scpi2 class and the Command class
 * @details This file contains the scpi2 class and the Command class.
 * Both are used to implement the SCPI interface via lambda functions.
 * @see scpi2
 * @see Command
*/

#include <Arduino.h>

#define SCIPI_BUFFER_SIZE 127
#define SCIPI_MAX_ARGC 16


namespace scpi{
    
    /**
     * @class Command
     * @brief A class that represents a command
     * @details This class represents a command.
     * It is used to implement the SCPI interface via lambda functions.
    */
    class Command
    {
    public:
        /**
         * @struct ChildCMD
         * @brief A struct that represents a child command
         * @details This struct represents a child command.
         * It contains the text of the command and a pointer to the command.
        */
        struct ChildCMD
        {
            /// @brief The command name
            const char* const txt;
            /// @brief The command pointer
            Command* cmd;
            /// @brief The length of the command name
            const size_t txtLen;
            // delete copy constructor and assignment operator
            ChildCMD(const ChildCMD& ccmd) : txt(ccmd.txt), cmd(ccmd.cmd), txtLen(ccmd.txtLen) { };
            ChildCMD& operator=(const ChildCMD&) = delete;

            /// @brief Constructor for ChildCMD
            /// @param txt The command name
            /// @param cmd The command pointer
            ChildCMD(const char* const txt, Command* cmd)
                : txt(txt), cmd(cmd), txtLen(strlen(txt)){};
        };
    private:
        /// @brief The function pointer to the command
        int (* const func)(int, char**)=nullptr;
        /// @brief The function pointer to the get function
        void (* const get)()=nullptr;
        
        /// @brief Command indexer
        /// @param  command The command to search for 
        /// @param  c The length of the command
        /// @return The index of the command in the subcommands array or -1 if not found
        int cmdInd(char*, int);

        /// @brief The subcommands array
        const ChildCMD* const subcommands;
        /// @brief The length of the subcommands array
        const size_t childCMDCount;
    public:
        /**
         * @brief Constructor for Command
         * @param func The function pointer to the command, can be nullptr
         * @param get The function pointer to the get function, can be nullptr
         * @param subCMD The subcommands array
         * @param childCMDCount The length of the subcommands array
        */
        Command(int (* const func)(int, char**), void (* const get)(), const ChildCMD* const subCMD, int childCMDCount)
            : func(func), get(get),
              subcommands(subCMD), childCMDCount(childCMDCount){}
        
        /**
         * @brief Templated constructor for Command
         * @param func The function pointer to the command, can be nullptr
         * @param get The function pointer to the get function, can be nullptr
         * @param subCMD The subcommands array
        */
        template<size_t N>
        Command(int (* const func)(int, char**), void (* const get)(), const ChildCMD(&subCMD)[N] )
            : func(func), get(get),
              subcommands(subCMD), childCMDCount(N){}
        
        /**
         * @brief Constructor for Command
         * @param func The function pointer to the command, can be nullptr
         * @param get The function pointer to the get function, can be nullptr
         * @note This constructor can be used when there are no child commands
        */
        Command(int (* const func)(int, char**), void (* const get)())
            : func(func), get(get),
              subcommands(nullptr), childCMDCount(0){}

        /**
         * @brief Constructor for Command
         * @param func The function pointer to the command, can be nullptr
         * @note This constructor can be used when there are no child commands
         * and no get function
        */
        Command(int (* const func)(int, char**))
            : func(func), get(nullptr),
              subcommands(nullptr), childCMDCount(0){}
        ~Command(){};
        // delete copy constructor and assignment operator
        Command(const Command& cmd) = delete;
        Command& operator=(const Command&) = delete;

        /// @brief Dumps the command with child commands to the serial port recursively
        /// @note This function is used for debugging
        void dump(void) const;

        /// @brief Parses the command and calls the function
        /// @param serial The serial reference to print to
        /// @param line The command to parse
        void parse(HardwareSerial& serial, char* line);

    };

    /**
     * @class scpi2
     * @brief A class that represents the SCPI interface
     * @details This class represents the SCPI interface.
     * It is used to implement the SCPI interface via lambda functions.
     * @see Command
     * @see ChildCMD
    */
    class scpi2
    {
    private:
        /// @brief The serial reference to read/write from/to
        HardwareSerial& serial;
        /// @brief The input buffer
        char input[SCIPI_BUFFER_SIZE+1];
        /// @brief The index of the input buffer
        int inBufIndex=0;
        /// @brief The root command
        /// @note This is the root command, all other commands are child commands of this command
        /// This should not have func and get
        /// @see Command
        Command& cmd;
        
    public:
        /// @brief Constructor for scpi2
        /// @param serial Reference to the serial port
        /// @param cmd The root command reference
        scpi2(HardwareSerial& serial, Command& cmd): serial(serial), cmd(cmd){};
        ~scpi2();

        /**
         * @brief Updates the SCPI interface
         * @details This method should be called quite often as it is the main method
         * of the SCPI interface.
         * It reads the serial port and parses the commands.
         * @note This method is blocking, it will block until the serial port is empty.
        */
        void update();
    };
}
