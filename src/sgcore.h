#pragma once
#include <map>
#include <functional>
#include <vector>
#include <array>
#include "raylib/raylib.h"
#include "ini.h"
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
    void* plugin = NULL;

    int set_mode(Buffer_Mode mode_);
    Buffer_Mode get_mode();

private:
    Buffer_Mode mode = Buffer_Mode::NORMAL;
};

class Plugin {
public:
    virtual int load() {}
    virtual int enable() {}
    // When related buffer is opened.
    virtual void open(Buffer* buffer) {}
    // When related buffer is closed.
    virtual void close(Buffer* buffer) {}
    virtual int disable() {}
    virtual int unload() {}

    // Returns supported by plugin buffer types.
    //
    // For each buffer, the first plugin that supports the buffer's type will receive events for the buffer, and will be able to modify buffer's state.
    virtual std::array<std::string&, 64>* get_types() {}
    virtual std::string& get_key() {}
    virtual std::string& get_name() {}
    virtual std::string& get_description() {}

    // Drawing is only possible during active phase.
    virtual void draw(Buffer* buffer) {}
    virtual void active_update(Buffer* buffer) {}
    virtual void passive_update(Buffer* buffer) {}

    // When for active for the plugin buffer the mode is changed.
    virtual void mode(Buffer* buffer) {}

    // When a command is issued for the plugin: it is either in format
    // `plugin_key.command_name` or `.command_name` for a related buffer.
    // The buffer passed is always the current active buffer - may not be
    // associated with the plugin.
    virtual void command(Buffer* buffer, const std::string& cmd, std::vector<std::string> args) {}
};

int init();
int loop();

char* get_mode_string();

int call_command(const char* command);

void command_exit(std::vector<const char*> args);

int engine_time();
void print_vector_int(std::vector<int> v);
}
