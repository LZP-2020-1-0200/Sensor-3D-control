#include "scpi2.h"

namespace scpi
{
    
const char* RECIEVED_RESPONSE = "R\r\n";
const char* ERROR_RESPONSE = "E\r\n";

scpi2::~scpi2()
{
}

void scpi2::update(){
    while (serial.available())
    {
        char c = serial.read();
        if(c=='\n' || c=='\r' || c==';'){
            input[inBufIndex]='\0';
            if(inBufIndex!=0)cmd.parse(serial, input);
            inBufIndex=0;
        // handle delete chars/backspaces
        }else if(c == '\b' || c == 127){
            if(inBufIndex>0) {
                inBufIndex--;
            }
            input[inBufIndex] = ' ';
        }else{
            input[inBufIndex] = c;
            inBufIndex++;
        }
        if(inBufIndex>SCIPI_BUFFER_SIZE){
            inBufIndex=0;
            serial.write("Command too long\r\n");
            //read all available data to empty buffer
            while (serial.available())
            {
                serial.read();
            }
        }
    }
}

int Command::cmdInd(char* command, int c){
    for(size_t i=0 ; i<childCMDCount ; i++){
        if(strncasecmp(subcommands[i].txt, command, c)==0){
            return i;
        }
    }
    return -1;
}

void Command::parse(HardwareSerial& serial, char* line){
    //iterate up to seperator
    for(int i=0;line[i]!='\0';i++){
        //sub cmd
        if(line[i]==':'){
            // check if parent command exists
            int ind = cmdInd(line, i);
            if(ind==-1){
                serial.write("Command \"");
                serial.write(line, i);
                serial.write("\" not found.\r\n");
                return;
            }
            //parse subcommand
            subcommands[ind].cmd->parse(serial, line+i+1);
            return;
        }
        // parameters
        else if(line[i]==' '){
            //check if command exists
            int ind = cmdInd(line, i);
            if(ind==-1){
                serial.write("Command \"");
                serial.write(line, i);
                serial.write("\" not found.\r\n");
                return;
            }
            char* argv[SCIPI_MAX_ARGC];
            int argc=1;
            line[i]='\0';
            argv[0]=line;
            i++;
            bool start=false;
            argv[argc]=line+i;
            //parse arguments
            do
            {
                if(!start){
                    if(line[i]!=' ')start=true;
                }else{
                    if(line[i]==' ' || line[i]=='\0'){
                        line[i]='\0';
                        argc++;
                        start=false;
                        if(argc==SCIPI_MAX_ARGC){
                            serial.write("Too many arguments.\r\n");
                            return;
                        }
                        argv[argc]=line+i+1;
                    }
                }
                i++;
            }while (line[i]!='\0');
            argc++;
            if(subcommands[ind].cmd->func==nullptr){
                serial.write("Call cmd not supported. Did you mean to add '?'?\r\n");
                return;
            }
            subcommands[ind].cmd->func(argc, argv);
            return;
        }
        // get command
        else if(line[i]=='?'){
            int ind = cmdInd(line, i);
            if(ind==-1){
                serial.write("Command \"");
                serial.write(line);
                serial.write("\" not found.\r\n");
                return;
            }
            subcommands[ind].cmd->get();
            return;
        }
    }
    //call cmd
    int ind = cmdInd(line, strlen(line));
    if(ind==-1){
        serial.write("Command \"");
        serial.write(line);
        serial.write("\" not found.\r\n");
        return;
    }
    subcommands[ind].cmd->func(1, &line);
    return;
}

} // namespace scpi
