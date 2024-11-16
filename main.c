#include "raylib.h"

Font font;

void draw() {
    ClearBackground(BLACK);
    Vector2 position;
    position.x = 0;
    position.y = 0;
    DrawTextEx(
        font,
        "check this font out dude\nnewline",
        position,
        font.baseSize*0.75,
        1,
        WHITE);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Sage");
    SetTargetFPS(60);
    // Stop execution while no input/window events happen.
    EnableEventWaiting();

    font = LoadFont("static/inconsolata/variable.ttf");
    while (!WindowShouldClose()) {
        BeginDrawing();
            draw();
        EndDrawing();
    }
    CloseWindow();
}
