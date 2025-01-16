#include "bone.h"
#include <stdarg.h>
#include "internal.h"
#include <windows.h>
#include <dbghelp.h>

#pragma comment(lib, "dbghelp.lib")

void bone_init() {
	_app_init();
}

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

void assert(bool condition) {
	void* stack[256];
	SYMBOL_INFO* symbol;
	HANDLE process = GetCurrentProcess();

	// Initialize the symbol handler.
	SymInitialize(process, NULL, TRUE);

	// Capture the stack trace.
	unsigned short frames = CaptureStackBackTrace(0, 100, stack, NULL);

	// Allocate memory for symbol information.
	symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char));
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	symbol->MaxNameLen = 255;

	if (!condition)
	{
		SymFromAddr(process, (DWORD64)(stack[0]), 0, symbol);
		printf("\033[31mASSERT\033[0m: %s (0x%llx)\n", symbol->Name, symbol->Address);
		exit(1);
	}

	free(symbol);
	SymCleanup(process);
}
