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

mINI::INIStructure raw_keybindings;
std::map<std::string, std::vector<int>> KEYBINDINGS;

std::string KEYBINDINGS_TARGETS[] = {
	"en_normal/go_insert_start",
	"en_normal/go_insert_end",
	"en_normal/go_insert_start_line",
	"en_normal/go_insert_end_line",
	"en_normal/go_visual",
	"en_normal/go_command",
	"en_normal/caret_left",
	"en_normal/caret_right",
	"en_normal/caret_up",
	"en_normal/caret_down",
	"en_normal/caret_line_start",
	"en_normal/caret_line_end",
	"en_normal/caret_buffer_start",
	"en_normal/caret_buffer_end",
	"en_normal/newline_after",
	"en_normal/newline_before",

	"en_visual/caret_left",
	"en_visual/caret_right",
	"en_visual/caret_up",
	"en_visual/caret_down",
	"en_visual/caret_line_start",
	"en_visual/caret_line_end",
	"en_visual/caret_buffer_start",
	"en_visual/caret_buffer_end",

	"en_insert/go_normal",
	"en_insert/next_suggestion",
	"en_insert/prev_suggestion",
	"en_insert/accept_suggestion",

	"en_command/execute",

	"en_writables/tilde",
	"en_writables/k1",
	"en_writables/k2",
	"en_writables/k3",
	"en_writables/k4",
	"en_writables/k5",
	"en_writables/k6",
	"en_writables/k7",
	"en_writables/k8",
	"en_writables/k9",
	"en_writables/k0",
	"en_writables/hyphen",
	"en_writables/equal",
	"en_writables/q",
	"en_writables/w",
	"en_writables/e",
	"en_writables/r",
	"en_writables/t",
	"en_writables/y",
	"en_writables/u",
	"en_writables/i",
	"en_writables/o",
	"en_writables/p",
	"en_writables/bracket_right",
	"en_writables/bracket_left",
	"en_writables/backslash",
	"en_writables/a",
	"en_writables/s",
	"en_writables/d",
	"en_writables/f",
	"en_writables/g",
	"en_writables/h",
	"en_writables/j",
	"en_writables/k",
	"en_writables/l",
	"en_writables/semicolon",
	"en_writables/z",
	"en_writables/x",
	"en_writables/c",
	"en_writables/v",
	"en_writables/b",
	"en_writables/n",
	"en_writables/m",
	"en_writables/comma",
	"en_writables/dot",
	"en_writables/slash",
	"en_writables/space",
	"en_writables/apostrophe",
};

std::map<const char*, int> BRACKET_KEYS = {
	{"enter", KEY_ENTER},
	{"tab", KEY_TAB},
	{"lshift", KEY_LEFT_SHIFT},
};

int init() {
	mINI::INIFile ini_file(bone::userdir("keybindings.cfg"));
	ini_file.read(raw_keybindings);

	// Initialize keybindings
	for (const auto& target : KEYBINDINGS_TARGETS) {
		auto parts = bone::split_string(target, '/');
		if (parts.size() != 2) {
			bone::log_error("Invalid keybinding target");
			return ERROR;
		}
		auto raw_keybinding = raw_keybindings[parts[0]][parts[1]];
		std::vector<int> processed_keys;

		bool bracket_opened = false;
		std::vector<char> bracket_chars;
		for (char c : raw_keybinding) {
			if (c == '<') {
				if (bracket_opened) {
					bone::log_error("Twice opening of command bracket in keybindings.cfg, skipping");
					processed_keys.clear();
					break;
				}
				bracket_opened = true;
			}
			if (c == '>') {
				if (!bracket_opened) {
					bone::log_error("Closing of bracket without opening, in keybindings.cfg, skipping");
					processed_keys.clear();
					break;
				}
				char* bracket_string = bracket_chars.data();
				if (bracket_string == "enter") {
					processed_keys.push_back(KEY_ENTER);
				} else {
					bone::log_error(bone::format("During keybindings processing, unrecognized bracket command: '%s'", bracket_string));
				}
				bracket_opened = false;
			}
			if (bracket_opened) {
				bracket_chars.push_back(c);
			} else {
				processed_keys.push_back((int)c)
			}
		}

		// This should copy the vector to the map
		KEYBINDINGS[target] = processed_keys;
	}

	// Setup home buffer, it's always under index 0
	Buffer* home_buffer = new Buffer();
	BUFFERS[0] = home_buffer;

	return OK;
}

float relative_height(float value) {
	return (float)GetScreenHeight()+value;
}

float relative_width(float value) {
	return (float)GetScreenWidth()+value;
}

#define INFOBAR_SIZE 50
#define INFOBAR_FONT_SIZE 24

void print_rectangle(Rectangle rect) {
	printf("{%f, %f, %f, %f}\n", rect.x, rect.y, rect.width, rect.height);
}

int loop() {
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "Sage");
	GuiLoadStyleDark();

	Font font = LoadFont("src/inconsolata/variable.ttf");

	Image icon = LoadImage("src/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		DrawLine(-100, relative_height(-INFOBAR_SIZE), relative_width(100), relative_height(-INFOBAR_SIZE), WHITE);

		float text_x = 10;
		float text_y = relative_height(-INFOBAR_SIZE) + INFOBAR_FONT_SIZE / 1.75;
		DrawTextEx(font, get_mode_string(), {text_x, text_y}, INFOBAR_FONT_SIZE, 0, WHITE);

		EndDrawing();
	}

	UnloadFont(font);
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