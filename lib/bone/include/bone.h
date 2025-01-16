#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void bone_init();
// Called `logm` to avoid collisions with builtin.
void logm(const char* message, ...);
void log_error(const char* message, ...);
void assert(bool condition);
#define null NULL