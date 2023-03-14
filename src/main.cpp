#include <Arduino.h>
#include "scipi2.h"
#include "stepper.h"

#define DEFAULT_BAUD 9600

Stepper s {&PORTB, &DDRB, DDB4, DDB5, DDB6, DDB7};
Stepper s2{&PORTD, &DDRD, DDD1, DDD4, DDD7, DDD0};
Stepper s3{&PORTF, &DDRF, DDF7, DDF6, DDF5, DDF4};

scipi::Command motorLock{
  [](int argc, char** argv){
    if(argc==2){
      if(strcasecmp(argv[1], "ON")==0){
        s.lock(true);
        s2.lock(true);
        s3.lock(true);
      }else if(strcasecmp(argv[1], "OFF")==0){
        s.lock(false);
        s2.lock(false);
        s3.lock(false);
      }
    }else if(argc==3){
      if(strcasecmp(argv[1], "A")==0){
        if(strcasecmp(argv[2], "ON")==0){
          s.lock(true);
        }else if(strcasecmp(argv[2], "OFF")==0){
          s.lock(false);
        }
      }else if(strcasecmp(argv[1], "B")==0){
        if(strcasecmp(argv[2], "ON")==0){
          s2.lock(true);
        }else if(strcasecmp(argv[2], "OFF")==0){
          s2.lock(false);
        }
      }else if(strcasecmp(argv[1], "C")==0){
        if(strcasecmp(argv[2], "ON")==0){
          s3.lock(true);
        }else if(strcasecmp(argv[2], "OFF")==0){
          s3.lock(false);
        }
      }
    }
  },
  nullptr
};

scipi::Command::ChildCMD testCMDS[]={{"lock", &motorLock}};
scipi::Command motorCMD{
  [](int argc, char** argv){
    if(argc==2){
      s.targetPos=atoi(argv[1]);
      s2.targetPos=atoi(argv[1]);
      s3.targetPos=atoi(argv[1]);
    }else if(argc==3){
      if(strcasecmp(argv[1], "A")==0){
        s.targetPos=atoi(argv[2]);
      }else if(strcasecmp(argv[1], "B")==0){
        s2.targetPos=atoi(argv[2]);
      }else if(strcasecmp(argv[1], "C")==0){
        s3.targetPos=atoi(argv[2]);
      }
    }
  },
  [](){
    char buff[32];
    itoa(s.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(s2.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(s3.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write("\n");
  },
  testCMDS, 1
};

scipi::Command::ChildCMD baseCMDS[]={{"motor", &motorCMD}};
scipi::Command base{
  nullptr, nullptr,baseCMDS, 1};
scipi::scipi2 inputHandler = scipi::scipi2(Serial1, base);



void setup()
{
  Serial1.begin(DEFAULT_BAUD);
  Serial1.setTimeout(100);
  Stepper::init();
  Stepper::motors[0]=&s;
  Stepper::motors[1]=&s2;
  Stepper::motors[2]=&s3;
  //s.set_direction(STEPPER_UP);
  s.delay("2");
  s2.delay("2");
  s3.delay("2");
}

void loop()
{
  inputHandler.update();
  /*if (Serial1.available())
  {
    scpi.addChar(Serial1.read());
    return;
  }*/
}