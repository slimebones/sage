#include "sgcore.h"

int main() {
    int e = bone::init("sage");
    if (e != 0) {
        return e;
    }

    e = sgcore::init();
    if (e != 0) {
        return e;
    }

    e = sgcore::loop();
    return e;
}
