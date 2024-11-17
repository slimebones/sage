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
    LangLayouts* langLayouts;
} IniConfig;

static int iniHandler(void* user, const char* section, const char* name, const char* value) {
    IniConfig* config = (IniConfig*)user;
    if (strcmp(section, ""))
    config->langLayouts->en->writables;
    return 0;
}

u64 charHash(const void* item, u64 seed0, u64 seed1) {
    const char* target = item;
    return hashmap_sip(target, strlen(target), seed0, seed1);
}

int charCompare(const void* a, const void* b, void* udata) {
    return strcmp(a, b);
}

Code parseAppIni() {
    IniConfig* config = malloc(sizeof(struct IniConfig));

    // Allocate config fields.
    config->langLayouts = malloc(sizeof(struct LangLayouts));
    config->langLayouts->en = malloc(sizeof(struct LangLayouts));
    config->langLayouts->en->writables = malloc(sizeof(struct LayoutWritables));
    config->langLayouts->en->normal = hashmap_new(
        sizeof(char*), 0, 0, 0, charHash, charCompare, nil, nil
    );
    config->langLayouts->en->insert = hashmap_new(
        sizeof(char*), 0, 0, 0, charHash, charCompare, nil, nil
    );
    config->langLayouts->en->visual = hashmap_new(
        sizeof(char*), 0, 0, 0, charHash, charCompare, nil, nil
    );
    config->langLayouts->en->command = hashmap_new(
        sizeof(char*), 0, 0, 0, charHash, charCompare, nil, nil
    );

    int r = ini_parse(APPINI_PATH, iniHandler, config);
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
