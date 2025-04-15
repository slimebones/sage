#include "sgcore.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"
#undef RAYGUI_IMPLEMENTATION

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

float relative_height(float value) {
	return (float)GetScreenHeight()+value;
}

float relative_width(float value) {
	return (float)GetScreenWidth()+value;
}

int loop() {
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	// SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(800, 450, "Sage");
	GuiLoadStyle("raygui/styles/dark/style_dark.rgs");

	Image icon = LoadImage("src/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	bool show_message_box = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		GuiPanel({relative_height(-100), relative_width(-100), 100, 100}, "Test");

		EndDrawing();
	}

	CloseWindow();

	return OK;
}

int call_command(const std::string& command) {
	return OK;
}
}