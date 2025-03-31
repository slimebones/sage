#include "raylib/raylib.h"
#include "common.h"
#include <vector>

namespace sgcore {

class Buffer {
public:
	// How buffer can be identified: it can be anything from file path to URI.
	std::string* identifier = NULL;
	// Type of the buffer: the first plugin that supports type will be enabled
	// for the buffer.
	std::string* type = NULL;
	std::vector<byte>* body = NULL;
};

class Context {

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

	// When related buffer is opened.
	virtual void on_buffer_opened(Context* c) {}

	// When related buffer is closed.
	virtual void on_buffer_closed(Context* c) {}

	// When related buffer change mode.
	virtual void on_mode_changed(Context* c) {}

	// When related buffer is focused.
	virtual void on_focused(Context* c) {}

	// When related buffer is unfocused.
	virtual void on_unfocused(Context* c) {}

	virtual int disable() {}
	virtual int deinit() {}
};

int init();
int loop();

}