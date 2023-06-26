
#include "reporter.h"

bool errorUnreported = false;

char errorMsg[ERROR_MESSAGE_MAX_LENGTH];

void reportError(const char* msg) {
	strncpy(errorMsg, msg, ERROR_MESSAGE_MAX_LENGTH-1);
	errorMsg[ERROR_MESSAGE_MAX_LENGTH-1]='\0';
	errorUnreported=true;
}
