#include "raylib.h"

int main() {
    InitWindow(800, 450, "Sage");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Alexander Ryzhov", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
}
