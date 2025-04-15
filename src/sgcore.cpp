#include "sgcore.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "raygui/styles/dark/style_dark.h"

namespace sgcore {

std::array<Buffer*, 256> BUFFERS;
int current_buffer_index = 0;
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

Buffer* get_current_buffer() {
	return BUFFERS[current_buffer_index];
}

Buffer_Mode Buffer::get_mode() {
	return mode;
}

mINI::INIStructure keybindings;

int init() {
	mINI::INIFile ini_file(bone::userdir("keybindings.cfg"));
	ini_file.read(keybindings);

	Buffer home_buffer;
	BUFFERS[0] = &home_buffer;

	return OK;
}

float relative_height(float value) {
	return (float)GetScreenHeight()+value;
}

float relative_width(float value) {
	return (float)GetScreenWidth()+value;
}

#define INFOBAR_SIZE 50
#define INFOBAR_FONT_SIZE 18
#define INFOBAR_MOD 11.25

int loop() {
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "Sage");
	GuiLoadStyleDark();

	Image icon = LoadImage("src/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	bool show_message_box = false;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		DrawLine(-100, relative_height(-INFOBAR_SIZE), relative_width(100), relative_height(-INFOBAR_SIZE), WHITE);
		DrawText(get_mode_string(), 10, relative_height(-INFOBAR_SIZE/(INFOBAR_FONT_SIZE/INFOBAR_MOD)), INFOBAR_FONT_SIZE, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return OK;
}

char* get_mode_string() {
	Buffer_Mode mode = get_current_buffer()->get_mode();
	switch (mode) {
		case Buffer_Mode::NORMAL:
			return "Normal";
		case Buffer_Mode::INSERT:
			return "Insert";
		case Buffer_Mode::VISUAL:
			return "Visual";
		case Buffer_Mode::COMMAND:
			return "Command";
		default:
			return "UNKNOWN";
	}
}

int call_command(const std::string& command) {
	return OK;
}
}