#include "common.h"
#include "sgcore.h"

int main() {
	bone::init();
	int e = sgcore::init();
	if (e != OK) {
		return e;
	}
	e = sgcore::loop();
	return e;
}