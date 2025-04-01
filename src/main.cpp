#include "common.h"
#include "sgcore.h"

int main() {
	int e = bone::init("sage");
	if (e != OK) {
		return e;
	}

	e = sgcore::init();
	if (e != OK) {
		return e;
	}

	e = sgcore::loop();
	return e;
}