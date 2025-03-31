#include "raylib/raylib.h"
#include "common.h"
#include <vector>

namespace sgcore {

std::array<Buffer*, 256> BUFFERS;

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
	// Active plugin of the buffer.
	Plugin* plugin = NULL;

	int set_mode(Buffer_Mode mode_) {
		mode = mode_;
		if (plugin != NULL) {
			plugin->on_mode_changed(mode);
		}
		return OK;
	}

	Buffer_Mode get_mode() {
		return mode;
	}

private:
	Buffer_Mode mode = Buffer_Mode::NORMAL;
};

class Plugin {
public:
	virtual int init() {}
	virtual int enable() {}

	// Returns supported by plugin buffer types.
	//
	// For each buffer, the first plugin that supports the buffer's type will
	// receive events for the buffer, and will be able to modify buffer's state.
	virtual std::array<std::string&, 64>* get_types() {}
	virtual std::string& get_key() {}
	virtual std::string& get_name() {}
	virtual std::string& get_description() {}

	// For methods "on_*" we pass only target parameters, not any kind of context.
	// Additional context can be requested by a plugin with special functions.

	// When related buffer is opened.
	virtual void on_buffer_opened(Buffer* buffer) {}

	// When related buffer is closed.
	virtual void on_buffer_closed(Buffer* buffer) {}

	// When related buffer change mode.
	virtual void on_mode_changed(Buffer_Mode mode) {}

	// When related buffer is focused.
	virtual void on_focused(Buffer* buffer) {}

	// When related buffer is unfocused.
	virtual void on_unfocused(Buffer* buffer) {}

	// When a command is issued for the plugin: it is either in format `plugin_key.command_name`
	// or `.command_name` for related buffer.
	//
	// Note that `buffer` argument might not be a related buffer in case of `plugin_key.command_name` invocation.
	virtual int on_command_entered(Buffer* buffer, const std::string& command) {}

	virtual int disable() {}
	virtual int deinit() {}
};

int init();
int loop();

int call_command(const std::string& command) {
}

}