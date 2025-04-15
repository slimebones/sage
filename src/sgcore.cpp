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

mINI::INIStructure keybindings;

int init() {
	mINI::INIFile ini_file(bone::userdir("keybindings.cfg"));
	ini_file.read(keybindings);

	return OK;
}

int loop() {
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	// SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(800, 450, "Sage");

	Image icon = LoadImage("src/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

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