#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// We manually define platform here. Don't know why, but on my windows mingw
// setup _WIN32 does not work.
#define PLATFORM_WIN32 1

#define nil NULL
// We store time in int, not uint, to allow for negative deltas.
#define Time int64_t

typedef void (*Function)();

Time TimeNow();
