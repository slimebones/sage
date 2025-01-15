#include "bone.h"
#include <stdarg.h>

void logm(const char* message, ...) {
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	printf("\n");
}

void log_error(const char *message, ...) {
	va_list args;
	va_start(args, message);
	printf("\033[31mERROR\033[0m: ");
	vprintf(message, args);
	va_end(args);
	printf("\n");
}