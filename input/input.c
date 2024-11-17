#include "input.h"
#define DELAY = 80;

Time lastInputTime = 0;

void UpdateInput() {
    // We collect only one pressed key per frame.
    int key = GetKeyPressed();
    if (key == 0) {
        return;
    }
    lastInputTime = TimeNow();
    printf("%llu\n", lastInputTime);
}
