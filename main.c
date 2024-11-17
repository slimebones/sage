#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "utils.h"
#include "common.h"
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

typedef struct IniConfig {
    const char* space;
    const char* q;
} IniConfig;

static int iniHandler(void* user, const char* section, const char* name, const char* value) {
    IniConfig* config = (IniConfig*)user;
    printf("%s %s %s\n", section, name, value);
    return 0;
}

Code parseAppIni() {
    IniConfig iniConfig;
    int r = ini_parse(APPINI_PATH, iniHandler, &iniConfig);
    if (r < 0) {
        printf("[E] Can't load `%s`. (Code %d)\n", APPINI_PATH, -1);
        return Error;
    }
    return Ok;
}

void initPaths() {
    REPO_DIR = malloc(512);
    strcpy(REPO_DIR, GetHomeDir());
    strcat(REPO_DIR, "/.sage");

    VAR_DIR = malloc(512);
    strcpy(VAR_DIR, REPO_DIR);
    strcat(VAR_DIR, "/var");

    APPINI_PATH = malloc(512);
    strcpy(APPINI_PATH, REPO_DIR);
    strcat(APPINI_PATH, "/app.ini");
}

Code main() {
    initPaths();
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
