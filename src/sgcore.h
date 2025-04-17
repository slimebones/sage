#pragma once
#include <map>
#include <functional>
#include <vector>
#include <array>
#include "raylib/raylib.h"
#include "ini.h"
#include "common.h"
#include "bone/bone.h"
#include "signal.h"

namespace sgcore {

enum Buffer_Mode {
	NORMAL,
	INSERT,
	VISUAL,
	COMMAND,
};

class Buffer {
public:
	// How buffer can be identified: it can be anything from file path to URI.
	std::string* path = NULL;
	// Type of the buffer: the first plugin that supports type will be enabled
	// for the buffer.
	std::string* type = NULL;
	std::vector<byte>* body = NULL;
	// Id of buffer's active plugin. Set to -1 if no active plugin.
	int plugin_id = -1;

	int set_mode(Buffer_Mode mode_);
	Buffer_Mode get_mode();

private:
	Buffer_Mode mode = Buffer_Mode::NORMAL;
};

class Plugin {
public:
	virtual int init() {}
	virtual int enable() {}
	// When related buffer is opened.
	virtual void open(Buffer* buffer) {}
	// When related buffer is closed.
	virtual void close() {}
	virtual int disable() {}
	virtual int deinit() {}

	// Returns supported by plugin buffer types.
	//
	// For each buffer, the first plugin that supports the buffer's type will
	// receive events for the buffer, and will be able to modify buffer's state.
	virtual std::array<std::string&, 64>* get_types() {}
	virtual std::string& get_key() {}
	virtual std::string& get_name() {}
	virtual std::string& get_description() {}

	// Drawing is only possible during active phase.
	virtual void draw() {}
	virtual void active_update() {}
	virtual void passive_update() {}

	// When for active for the plugin buffer the mode is changed.
	virtual void mode(Buffer_Mode mode) {}

	// When a command is issued for the plugin: it is either in format
	// `plugin_key.command_name` or `.command_name` for a related buffer.
	//
	// Note that `buffer` argument might not be a related buffer in case of
	// `plugin_key.command_name` invocation: this always will be active buffer
	// at the moment.
	virtual void command(Buffer* active_buffer, const std::string& cmd) {}
};

int init();
int loop();

class Command_Context {
public:
};

using Command_Function = std::function<int(Command_Context)>;

char* get_mode_string();

int call_command(const std::string& command);

}