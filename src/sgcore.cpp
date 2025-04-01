#include "sgcore.h"

namespace sgcore {

std::array<Buffer*, 256> BUFFERS;
// Array of all initialized plugins. Their position is static, so they can be
// referenced by index at any time during runtime.
std::vector<Plugin*> PLUGINS;
std::map<std::string, Command_Function> COMMANDS;

int Buffer::set_mode(Buffer_Mode mode_) {
	mode = mode_;
	if (plugin_id >= 0) {
		PLUGINS[plugin_id]->on_mode_changed(mode_);
	}
	return OK;
}

Buffer_Mode Buffer::get_mode() {
	return mode;
}

mINI::INIFile file("myfile.ini");

int init() {
	bone::log(bone::userdir("src/bone/bone.cpp").string());
	return OK;
}

int loop() {
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

}