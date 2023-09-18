
#ifndef REPORTER_H
#define REPORTER_H
#pragma once
#include <Arduino.h>

enum class ErrorSeverity {
	INFO,
	WARNING,
	ERROR,
	FATAL
};

void report(const __FlashStringHelper* msg, ErrorSeverity severity);
void report(const char* msg, ErrorSeverity severity);


#endif
