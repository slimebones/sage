#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__declspec(dllexport) char* key() {
	char* key = (char*)malloc(256 * sizeof(char));
	strcpy(key, "editor");
	return key;
}

int main() {}