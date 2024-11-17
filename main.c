#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "utils.h"
#include "codes.h"
#include "buffer.h"
#include "input.h"
#include "ini.h"

Font font;
Buffer* selectedBuffer = nil;

void update() {
    UpdateInput();
    for (int i = 0; i < MAX_BUFFERS; i++) {
        Buffer* buffer = Buffers[i];
        UpdateBuffer(buffer);
    }
}

void draw() {
    // ClearBackground(BLACK);
    // Vector2 position;
    // position.x = 0;
    // position.y = 0;
    // DrawTextEx(
    //     font,
    //     "check this font out dude\nnewline",
    //     position,
    //     font.baseSize*0.75,
    //     1,
    //     WHITE
    // );
}

typedef struct {
    const char* space;
    const char* q;
} IniConfig;

static int iniHandler(void* ini, const char* section, const char* name, const char* value) {
    printf("%s %s %s\n", section, name, value);
    return 0;
}

Code parseAppIni() {
    IniConfig iniConfig;
    int r = ini_parse("app.ini", iniHandler, &iniConfig);
    if (r != 0) {
        printf("[E] Can't load `app.ini`. (Code %d)\n", -1);
        return Error;
    }
    printf("Ini Config: %s %s\n", iniConfig.space, iniConfig.q);
    return Ok;
}

Code main() {
    int r = parseAppIni();
    if (r < 0) {
        return r;
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Sage");
    SetTargetFPS(60);
    // Stop execution while no input/window events happen.
    EnableEventWaiting();

    // Initialize all buffers in normal mode.
    for (int i = 0; i < MAX_BUFFERS; i++) {
        Buffer* buffer = &(Buffer){Normal};
        Buffers[i] = buffer;
    }

    font = LoadFont("static/inconsolata/variable.ttf");
    while (!WindowShouldClose()) {
        update();

        BeginDrawing();
            draw();
        EndDrawing();
    }
    CloseWindow();
    return Ok;
}
