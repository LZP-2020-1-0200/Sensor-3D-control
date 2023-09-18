
#include "reporter.h"


static bool isSevere(ErrorSeverity base, ErrorSeverity severity) {
	return (int)severity >= (int)base;
}

static ErrorSeverity minErrorSeverityToReport = ErrorSeverity::INFO;

void report(const __FlashStringHelper* msg, ErrorSeverity severity) {
	if (isSevere(minErrorSeverityToReport, severity)) {
		Serial.println(msg);
	}
}
void report(const char* msg, ErrorSeverity severity) {
	if (isSevere(minErrorSeverityToReport, severity)) {
		Serial.println(msg);
	}
}