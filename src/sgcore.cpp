#include "sgcore.h"

int sgcore::init() {
	return OK;
}

int sgcore::loop() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(800, 450, "raylib [core] example - basic window");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);
		// DrawTextEx("Congrats! You created your first window!", 190, 200, 20, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return OK;
}