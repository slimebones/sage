#include "bone.h"
// #include "raylib.h"
#include "plugin.h"
#include "windows.h"

typedef char* (*KeyFunc)();
int main(void) {
	HMODULE dll = LoadLibrary("plugins/editor/editor.dll");
	if (dll == NULL) {
		printf("Could not load the DLL\n");
		return 1;
	}

	KeyFunc key = (KeyFunc)GetProcAddress(dll, "key");
	if (key == NULL) {
		printf("Could not locate the function\n");
		FreeLibrary(dll);
		return 1;
	}

	char* k = key();
	logm("Received '%s'", k);

	FreeLibrary(dll);
	return 0;

	// const int width = 800;
	// const int height = 450;

	// InitWindow(width, height, "Sage");
	// Image icon = LoadImage("res/icon.png");
	// SetWindowIcon(icon);

	// SetTargetFPS(15);

	// while (!WindowShouldClose()) {
	// 	BeginDrawing();
	// 	ClearBackground(BLACK);
	// 	DrawText("Hello, world!", 200, 200, 20, WHITE);
	// 	EndDrawing();
	// }
	// CloseWindow();
	// UnloadImage(icon);
	// return 0;
}
