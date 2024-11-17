#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "utils.h"
#include "buffer.h"
#include "input.h"

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

void main() {
#ifdef _WIN32
    println(1111);
#endif

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
}
