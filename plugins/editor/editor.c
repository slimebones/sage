#include <stdio.h>

__declspec(dllexport) char* key() {
	char *key = malloc(256);
	strcpy(key, "editor");
	return key;
}