#include "bone.h"
#include "windows.h"

typedef char* (*KeyFunc)();

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

	char* k = key();
	logm("Received '%s'", k);

	FreeLibrary(dll);
	return true;
}
