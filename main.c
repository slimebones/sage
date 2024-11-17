#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "utils.h"
#include "buffer.h"

Font font;
Buffer* selectedBuffer = nil;

void update() {
    for (int i = 0; i < MAX_BUFFERS; i++) {
        Buffer* buffer = Buffers[i];
        printf("%d\n", buffer->Mode);
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

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Sage");
    SetTargetFPS(60);
    // Stop execution while no input/window events happen.
    EnableEventWaiting();

    for (int i = 0; i < MAX_BUFFERS; i++) {
        Buffer* buffer = &(Buffer){Insert};
        Buffers[i] = buffer;
        printf("%d\n", buffer->Mode);
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
