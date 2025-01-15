#include "bone.h"
#include "windows.h"

typedef void*(*Allocator)(size_t size);
typedef char* (*KeyFunc)(Allocator allocator);

// We use approach of passing allocator functions to DLL, otherwise we get
// access violation errors while trying to use their own malloc. Don't
// know why this happens, but allocator-passing approach seems to work.
void* memory_allocator(size_t size) {
	return malloc(size);
}

bool load() {
	HMODULE dll = LoadLibrary("plugins/editor/editor.dll");
	if (dll == NULL) {
		printf("Could not load the DLL\n");
		return false;
	}

	KeyFunc key = (KeyFunc)GetProcAddress(dll, "key");
	if (key == NULL) {
		printf("Could not locate the function\n");
		FreeLibrary(dll);
		return false;
	}

	char* k = key(memory_allocator);
	logm("Received '%s'", k);

	FreeLibrary(dll);
	return true;
}
