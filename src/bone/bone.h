// The Bone utility set.
// This is C++ version - available only for Windows.

#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#define byte unsigned char

namespace bone {
void log(const std::string& message);
void log_error(const std::string& message);
int init(std::string project_name_);

std::filesystem::path cwd(std::filesystem::path p);

std::filesystem::path userdir(std::filesystem::path p);

// @todo implement log pipes, e.g. for sgcore interception

std::vector<std::string> split_string(const std::string& str, char delimiter);
std::string format(const char* f, ...);
}