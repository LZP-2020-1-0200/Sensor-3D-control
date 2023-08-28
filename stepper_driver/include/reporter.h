
#ifndef REPORTER_H
#define REPORTER_H
#pragma once
#include <Arduino.h>
#define ERROR_MESSAGE_MAX_LENGTH 300
extern bool errorUnreported;

void reportError(const char* msg);

extern char errorMsg[ERROR_MESSAGE_MAX_LENGTH];

#endif
