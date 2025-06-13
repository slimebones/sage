#include "sgcore.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui/src/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "raygui/styles/dark/style_dark.h"
#include <cstdlib>

namespace sgcore {

using Command_Function = std::function<void(std::vector<const char*>)>;
std::array<Buffer*, 256> BUFFERS;
int current_buffer_index = 0;
// Array of all initialized plugins. Their position is static, so they can be
// referenced by index at any time during runtime.
std::vector<Plugin*> PLUGINS;
std::unordered_map<const char*, Command_Function> BUILTIN_COMMANDS;
std::unordered_map<int, const char*> SHIFT_KEYCODES = {
    {KEY_A, "A"},
    {KEY_B, "B"},
    {KEY_C, "C"},
    {KEY_D, "D"},
    {KEY_E, "E"},
    {KEY_F, "F"},
    {KEY_G, "G"},
    {KEY_H, "H"},
    {KEY_I, "I"},
    {KEY_J, "J"},
    {KEY_K, "K"},
    {KEY_L, "L"},
    {KEY_M, "M"},
    {KEY_N, "N"},
    {KEY_O, "O"},
    {KEY_P, "P"},
    {KEY_Q, "Q"},
    {KEY_R, "R"},
    {KEY_S, "S"},
    {KEY_T, "T"},
    {KEY_U, "U"},
    {KEY_V, "V"},
    {KEY_W, "W"},
    {KEY_X, "X"},
    {KEY_Y, "Y"},
    {KEY_Z, "Z"},
    {KEY_SEMICOLON, ":"},
};
std::unordered_map<int, const char*> KEYCODES = {
    {KEY_ENTER, "enter"},
    {KEY_TAB, "tab"},
    {KEY_LEFT_SHIFT, "lshift"},
    {KEY_SPACE, "space"},
    {KEY_KP_0, "0"},
    {KEY_KP_1, "1"},
    {KEY_KP_2, "2"},
    {KEY_KP_3, "3"},
    {KEY_KP_4, "4"},
    {KEY_KP_5, "5"},
    {KEY_KP_6, "6"},
    {KEY_KP_7, "7"},
    {KEY_KP_8, "8"},
    {KEY_KP_9, "9"},
    {KEY_A, "a"},
    {KEY_B, "b"},
    {KEY_C, "c"},
    {KEY_D, "d"},
    {KEY_E, "e"},
    {KEY_F, "f"},
    {KEY_G, "g"},
    {KEY_H, "h"},
    {KEY_I, "i"},
    {KEY_J, "j"},
    {KEY_K, "k"},
    {KEY_L, "l"},
    {KEY_M, "m"},
    {KEY_N, "n"},
    {KEY_O, "o"},
    {KEY_P, "p"},
    {KEY_Q, "q"},
    {KEY_R, "r"},
    {KEY_S, "s"},
    {KEY_T, "t"},
    {KEY_U, "u"},
    {KEY_V, "v"},
    {KEY_W, "w"},
    {KEY_X, "x"},
    {KEY_Y, "y"},
    {KEY_Z, "z"},
    {KEY_F1, "f1"},
    {KEY_F2, "f2"},
    {KEY_F3, "f3"},
    {KEY_F4, "f4"},
    {KEY_F5, "f5"},
    {KEY_F6, "f6"},
    {KEY_F7, "f7"},
    {KEY_F8, "f8"},
    {KEY_F9, "f9"},
    {KEY_F10, "f10"},
    {KEY_F11, "f11"},
    {KEY_F12, "f12"},
    {KEY_SEMICOLON, ";"},
};

int Buffer::set_mode(Buffer_Mode mode_) {
    mode = mode_;
    if (plugin != NULL) {
        ((Plugin*)plugin)->mode(this);
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
std::map<const char*, std::vector<int>> KEYBINDINGS;
#define KEY_DELAY = 100

const char* KEYBINDINGS_TARGETS[] = {
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

template<typename K, typename V>
K map_find_by_value(const std::unordered_map<K, V>& map, const V& value, const K& default_) {
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first; // Return the key if the value matches
        }
    }
    return default_;
}

int longest_keybinding_size = 0;

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

        if (
            raw_keybinding.size() > 2
            && (
                (raw_keybinding[0] == '"' && raw_keybinding.back() == '"')
                || (raw_keybinding[0] == '`' && raw_keybinding.back() == '`')
            )
        ) {
            bool bracket_opened = false;
            // Special bindings are bindings enclosed in `` quotes, allowing to use
            // any symbols including `<>` without them being processed.
            bool special_binding = raw_keybinding[0] == '`' && raw_keybinding.back() == '`';

            std::vector<char> bracket_chars;
            for (char c : raw_keybinding.substr(1, raw_keybinding.length() - 2)) {
                if (!special_binding && c == '<') {
                    if (bracket_opened) {
                        bone::log_error("Twice opening of command bracket in keybindings.cfg, skipping");
                        processed_keys.clear();
                        break;
                    }
                    bracket_opened = true;
                    continue;
                }
                if (!special_binding && c == '>') {
                    if (!bracket_opened) {
                        bone::log_error("Closing of bracket without opening, in keybindings.cfg, skipping");
                        processed_keys.clear();
                        break;
                    }
                    const char* bracket_string = bracket_chars.data();
                    auto keyvalue = map_find_by_value(KEYCODES, bracket_string, 0);
                    bracket_opened = false;
                    if (keyvalue != 0) {
                        processed_keys.push_back(keyvalue);
                    } else {
                        bone::log_error(bone::format("During keybindings processing, unrecognized bracket command: '%s'", bracket_string));
                        bracket_chars.clear();
                        break;
                    }
                    bracket_chars.clear();
                    continue;
                }

                if (bracket_opened) {
                    bracket_chars.push_back(c);
                } else {
                    const char* s(1, c);
                    auto keyvalue = map_find_by_value(KEYCODES, s, 0);
                    // Now try search shift combinations
                    if (keyvalue == 0) {
                        keyvalue = map_find_by_value(SHIFT_KEYCODES, s, 0);
                        if (keyvalue != 0) {
                            processed_keys.push_back(KEY_LEFT_SHIFT);
                        }
                    }
                    if (keyvalue != 0) {
                        processed_keys.push_back(keyvalue);
                    }
                }
            }
        }

        if (processed_keys.size() > longest_keybinding_size) {
            longest_keybinding_size = processed_keys.size();
        }
        // This should copy the vector to the map
        KEYBINDINGS[target] = processed_keys;
    }

    // Setup home buffer, it's always under index 0
    Buffer* home_buffer = new Buffer();
    BUFFERS[0] = home_buffer;

    // Initialize builtin commands
    BUILTIN_COMMANDS["exit"] = cmd_exit;

    return OK;
}

void load_plugin(Plugin* plugin) {
    plugin->load();
    plugin->enable();
    PLUGINS.push_back(plugin);
}

void cmd_exit(std::vector<const char*> args) {
    exit(0);
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

std::vector<int> keybuffer;

void clear_keybuffer() {
    keybuffer.clear();
}

void print_vector_int(std::vector<int> v) {
    printf("(");
    auto i = 0;
    for (auto a : v) {
        if (i == v.size()-1) {
            printf("%d", a);
        } else {
            printf("%d, ", a);
        }
        i++;
    }
    printf(")\n");
}

const char* find_matching_key(const char* group) {
    for (const auto& keybinding_pair : KEYBINDINGS) {
        auto parts = bone::split_string(keybinding_pair.first, '/');
        auto keybinding_group = parts[0];
        if (group == keybinding_group && keybinding_pair.second == keybuffer) {
            return parts[1];
        }
    }
    return "";
}

void _update(float delta) {
    // Process keybuffer
    if (keybuffer.size() > 0) {
        const char* key;
        switch (get_current_buffer()->get_mode()) {
            case Buffer_Mode::NORMAL:
                key = find_matching_key("en_normal");
                if (key == "go_insert_start") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::INSERT);
                    clear_keybuffer();
                }
                if (key == "go_insert_end") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::INSERT);
                    clear_keybuffer();
                }
                if (key == "go_insert_start_line") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::INSERT);
                    clear_keybuffer();
                }
                if (key == "go_insert_end_line") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::INSERT);
                    clear_keybuffer();
                }
                if (key == "go_command") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::COMMAND);
                    clear_keybuffer();
                }
                if (key == "go_visual") {
                    bone::log(key);
                    get_current_buffer()->set_mode(Buffer_Mode::VISUAL);
                    clear_keybuffer();
                }
                break;
            case Buffer_Mode::INSERT:
                break;
            case Buffer_Mode::VISUAL:
                break;
            case Buffer_Mode::COMMAND:
                break;
            default:
                clear_keybuffer();
                break;
        }
    }
    if (keybuffer.size() > longest_keybinding_size) {
        clear_keybuffer();
    }
}

template <typename T>
const char* vector_to_string(const std::vector<T>& vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << ",";  // Add a comma after each element except the last one
        }
    }
    return oss.str();
}

void _draw(Font font) {
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    DrawLine(-100, relative_height(-INFOBAR_SIZE), relative_width(100), relative_height(-INFOBAR_SIZE), WHITE);

    // Draw mode
    float text_x = 10;
    float text_y = relative_height(-INFOBAR_SIZE) + INFOBAR_FONT_SIZE / 1.75;
    DrawTextEx(font, get_mode_string(), {text_x, text_y}, INFOBAR_FONT_SIZE, 0, WHITE);

    // Draw keybuffer
    text_x = 300;
    text_y = relative_height(-INFOBAR_SIZE) + INFOBAR_FONT_SIZE / 1.75;
    std::vector<const char*> keybuffer_str;
    for (auto k : keybuffer) {
        auto it = KEYCODES.find(k);
        if (it != KEYCODES.end()) {
            keybuffer_str.push_back(it->second);
        } else {
            it = SHIFT_KEYCODES.find(k);
            if (it != SHIFT_KEYCODES.end()) {
                keybuffer_str.push_back(it->second);
            }
        }
    }
    DrawTextEx(font, vector_to_string(keybuffer_str).data(), {text_x, text_y}, INFOBAR_FONT_SIZE, 0, WHITE);

    EndDrawing();
}

#define TARGET_FPS 5.0f
const float UPDATE_INTERVAL = 1.0f / TARGET_FPS;

int loop() {
    printf("Current time: %d, Current date: %s", bone::time(), bone::date(bone::time(), null));

    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Sage");
    SetExitKey(0);
    GuiLoadStyleDark();

    Font font = LoadFont("src/inconsolata/variable.ttf");

    Image icon = LoadImage("src/icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    float accumulator = 0.0f;
    float prev_time = GetTime();

    while (!WindowShouldClose()) {
        float current_time = GetTime();
        float delta_time = current_time - prev_time;
        prev_time = current_time;
        accumulator += delta_time;

        // Gather pressed keys - not in general update to not lose them in-between
        // our frames.
        std::vector<int> control_keybuffer;
        while (true) {
            auto k = GetKeyPressed();
            if (k == KEY_LEFT_SHIFT || k == KEY_LEFT_CONTROL || k == KEY_LEFT_ALT) {
                continue;
            }
            if (k == 0)  {
                break;
            }
            // Pressed controls are going with each key. Order matters!
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                keybuffer.push_back(KEY_LEFT_SHIFT);
            }
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                keybuffer.push_back(KEY_LEFT_CONTROL);
            }
            if (IsKeyDown(KEY_LEFT_ALT)) {
                keybuffer.push_back(KEY_LEFT_ALT);
            }
            keybuffer.push_back(k);
        }

        // Update logic runs at a fixed interval
        while (accumulator >= UPDATE_INTERVAL) {
            accumulator -= UPDATE_INTERVAL;
            _update(delta_time);
        }

        _draw(font);
    }

    UnloadFont(font);
    CloseWindow();

    return OK;
}

// Return engine time in milliseconds. Engine time is the time passed since the window was created.
int engine_time() {
    return (int)(GetTime() * 1000);
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

int call_command(const const char*& command) {
    return OK;
}
}
