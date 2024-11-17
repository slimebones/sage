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

static int iniHandler(
    void* user, const char* section, const char* name, const char* value
) {
    IniConfig* config = (IniConfig*)user;
    if (strcmp(section, "layout.en.normal")) {
        hashmap_set(config->langLayouts->en->normal, &name);
    }
    if (strcmp(section, "layout.en.visual")) {
        hashmap_set(config->langLayouts->en->visual, &name);
    }
    if (strcmp(section, "layout.en.insert")) {
        hashmap_set(config->langLayouts->en->insert, &name);
    }
    if (strcmp(section, "layout.en.command")) {
        hashmap_set(config->langLayouts->en->command, &name);
    }
    if (strcmp(section, "layout.en.writables")) {
        hashmap_set(config->langLayouts->en->command, &name);
    }
    return 0;
}

Code parseAppIni() {
    IniConfig* config = malloc(sizeof(struct IniConfig));

    // Allocate config fields.
    config->langLayouts = malloc(sizeof(struct LangLayouts));
    config->langLayouts->en = malloc(sizeof(struct LangLayouts));
    config->langLayouts->en->writables = malloc(sizeof(struct LayoutWritables));
    config->langLayouts->en->normal = malloc(
        BINDINGS_SIZE * sizeof(Binding*)
    );
    config->langLayouts->en->insert = malloc(
        BINDINGS_SIZE * sizeof(Binding*)
    );
    config->langLayouts->en->visual = malloc(
        BINDINGS_SIZE * sizeof(Binding*)
    );
    config->langLayouts->en->command = malloc(
        BINDINGS_SIZE * sizeof(Binding*)
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
