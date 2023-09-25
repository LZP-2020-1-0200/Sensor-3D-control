


#include "scpi2.h"
#include "stepperController.h"

extern StepperController& xMotor;
extern StepperController& yMotor;
extern StepperController& zMotor;

extern scpi::Command motorCMD;
extern scpi::Command homeCMD;
extern scpi::Command rawCMD;
extern scpi::Command rstCMD;
extern scpi::Command idnCMD;



static void getHelp(void) {
	Serial.println(F("Sending manual"));
	Serial1.print(F(
		"\n\n\n"
		"Available Commands: \n\n"
		"-\t*RST\n"
		"Resets the controller.\n\n"
		"-\t*IDN?\n"
		"Returns the device ID.\n\n"
		"-\tMOTOR?\n"
		"Returns the current position of all motors.\n\n"
		"-\tMOTOR [X|Y|Z] {coordinate}\n"
		"Moves the motor to the specified coordinate. \n\n"
		"-\tMOTOR {coordinate}\n"
		"Moves all motors to the specified coordinate. \n\n"
		"-\tMOTOR:END:{X|Y|Z}?\n"
		"Returns the end switch status of the specified motor.\n\n"
		"-\tMOTOR:STATE?\n"
		"Returns the state of all motors.\n\n"
		"-\tMOTOR:STATE:DEFAULT[?]\n"
		"Gets/sets the default state of all motors.\n\n"
		"-\tMOTOR:LOCK {X|Y|Z} {ON|OFF}\n"
		"Locks or unlocks the specified motor.\n\n"
		"-\tRAW [X|Y|Z] {coordinate}\n"
		"Moves all motors to the specified coordinate. (moves without compensating for movement)\n\n"
		"-\tHOME\n"
		"Homes all motors.\n\r"
		));
}

static int getHelpFunc(int argc, char** argv) {
	getHelp();
	return 0;
}

scpi::Command helpCMD(
	getHelpFunc,
	getHelp
);

const scpi::Command::ChildCMD baseChildCMDs[] {
	{"MOTOR", &motorCMD},
	{"HOME", &homeCMD},
	{"*RST", &rstCMD},
	{"*IDN", &idnCMD},
	{"RAW", &rawCMD},
	{"HELP", &helpCMD}
};

scpi::Command baseCMD(
	nullptr,
	nullptr,
	baseChildCMDs
);