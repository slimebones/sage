#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void*(*Allocator)(size_t size);

__declspec(dllexport) char* key(Allocator allocator) {
	char* key = (char*)allocator(256 * sizeof(char));
	strcpy(key, "editor");
	return key;
}

int main() {}