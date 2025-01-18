#include "bone.h"
#include "plugin.h"
#include "raylib.h"

int main(void) {
	// load();
	bone_init();

	const int width = 800;
	const int height = 450;

	InitWindow(width, height, "Sage");
	Image icon = LoadImage("res/icon.png");
	SetWindowIcon(icon);

	SetTargetFPS(15);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Hello, world!", 200, 200, 20, WHITE);
		EndDrawing();
	}
	CloseWindow();
	UnloadImage(icon);
	return 0;
}
