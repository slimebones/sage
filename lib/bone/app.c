#include "ini.h"
#include "bone.h"

#define MAX_ITEMS 256

char* sections[MAX_ITEMS];
int section_index = 0;

char* keys[MAX_ITEMS];
int key_index = 0;

char* values[MAX_ITEMS];
int value_index = 0;

static int _handler(
	void* user,
	const char* section,
	const char* key,
	const char* value
) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		if (sections[i] == null) {
			// @incompleted decide about strcpy_s
			char* copied = malloc(strlen(section) + 1);
			strcpy_s(copied, sizeof(copied), section);
			sections[i] = copied;
		}
	}

	for (int i = 0; i < MAX_ITEMS; i++) {
		if (keys[i] == null) {
			char* copied = malloc(strlen(key) + 1);
			strcpy(copied, key);
			keys[i] = copied;
		}
	}

	for (int i = 0; i < MAX_ITEMS; i++) {
		if (values[i] == null) {
			char* copied = malloc(strlen(value) + 1);
			strcpy(copied, value);
			values[i] = copied;
		}
	}

	return 1;
}

void _app_init() {
	if (ini_parse("var/app.cfg", _handler, null) < 0) {
		printf("Can't load 'test.ini'.\n");
	}
}