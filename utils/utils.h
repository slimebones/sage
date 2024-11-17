#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// We manually define platform here. Don't know why, but on my windows mingw
// setup _WIN32 does not work.
#define PLATFORM_WIN32 1

#define nil NULL
// We store time in int, not uint, to allow for negative deltas.
#define Time int64_t

// Negative codes - errors, 0 code - OK, positive codes - ok messages.
#define Code int16_t

#define u16 uint16_t
#define u64 uint64_t
#define u32 uint32_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

typedef void (*Function)();

Time TimeNow();

char* GetCwd();
char* GetHomeDir();
