#include <Arduino.h>
#include "scipi2.h"
#include "stepper.h"
#include "endSwitch.h"
#include "stepperController.h"
#define DEFAULT_BAUD 9600




static StepperController& xMotor = StepperController::xMotor;
static StepperController& yMotor = StepperController::yMotor;
static StepperController& zMotor = StepperController::zMotor;

scipi::Command motorLock{
  [](int argc, char** argv){
    if(argc==2){
      if(strcasecmp(argv[1], "ON")==0){
        xMotor.pause_lock=true;
        yMotor.pause_lock=true;
        zMotor.pause_lock=true;
        Serial1.write("Motors locked\r\n");
      }else if(strcasecmp(argv[1], "OFF")==0){
        xMotor.pause_lock=false;
        yMotor.pause_lock=false;
        zMotor.pause_lock=false;
        Serial1.write("Motors unlocked\r\n");
      }else{
        Serial1.write("Invalid lock command\r\n");
      }
    }else if(argc==3){
      if(strcasecmp(argv[1], "X")==0){
        if(strcasecmp(argv[2], "ON")==0){
          xMotor.pause_lock = true;
        }else if(strcasecmp(argv[2], "OFF")==0){
          xMotor.pause_lock = false;
        }
      }else if(strcasecmp(argv[1], "Y")==0){
        if(strcasecmp(argv[2], "ON")==0){
          yMotor.pause_lock = true;
        }else if(strcasecmp(argv[2], "OFF")==0){
          yMotor.pause_lock = false;
        }
      }else if(strcasecmp(argv[1], "Z")==0){
        if(strcasecmp(argv[2], "ON")==0){
          zMotor.pause_lock = true;
        }else if(strcasecmp(argv[2], "OFF")==0){
          zMotor.pause_lock = false;
        }
      }
    }
  },
  nullptr
};

scipi::Command::ChildCMD testCMDS[]={{"lock", &motorLock}};
scipi::Command motorCMD{
  [](int argc, char** argv){
    Serial.write(argv[1]);
    if(argc==2){
      xMotor.setTarget(atoi(argv[1]));
      yMotor.setTarget(atoi(argv[1]));
      zMotor.setTarget(atoi(argv[1]));
    }else if(argc==3){
      if(strcasecmp(argv[1], "X")==0){
        xMotor.setTarget(atoi(argv[2]));
      }else if(strcasecmp(argv[1], "Y")==0){
        yMotor.setTarget(atoi(argv[2]));
      }else if(strcasecmp(argv[1], "Z")==0){
        zMotor.setTarget(atoi(argv[2]));
      }
    }
  },
  [](){
    char buff[32];
    itoa(xMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(yMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write(" ");
    itoa(zMotor.get_position(), buff, 10);
    Serial1.write(buff);
    Serial1.write("\r\n");
  },
  testCMDS, 1
};
scipi::Command homeCMD{
  [](int argc, char** argv){
    xMotor.home();
    yMotor.home();
    zMotor.home();
  },
  nullptr
};
scipi::Command::ChildCMD baseCMDS[]={
  {"motor", &motorCMD},
  {"home", &homeCMD}
};
scipi::Command base{
  nullptr, nullptr,baseCMDS, 2};
scipi::scipi2 inputHandler = scipi::scipi2(Serial1, base);

#ifndef PIO_UNIT_TESTING
void setup()
{
  Serial.begin(DEFAULT_BAUD);
  Serial.setTimeout(100);
  Serial1.begin(DEFAULT_BAUD);
  Serial1.setTimeout(100);
  StepperController::motors[0]=&xMotor;
  StepperController::motors[1]=&yMotor;
  StepperController::motors[2]=&zMotor;
  //s.set_direction(STEPPER_UP);
  xMotor.setDelay("100");
  yMotor.setDelay("100");
  zMotor.setDelay("200");
  //zMotor.setTarget(30000);
  delay(3000);
  //zMotor.setMode(StepperController::mode::homing);
}


void loop()
{
  inputHandler.update();
}
#endif