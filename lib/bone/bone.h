#include <stdio.h>
#include <stdbool.h>

// Called `logm` to avoid collisions with builtin.
void logm(const char* message, ...);
void log_error(const char* message, ...);