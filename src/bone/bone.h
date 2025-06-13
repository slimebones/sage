// The Bone utility set.
// This is C++ version - available only for Windows.

#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#define byte unsigned char
#define null nullptr

namespace bone {
void log(const char* message);
void log_error(const char* message);
void panic(const char* message);
int init(const char* project_name_);

std::filesystem::path cwd(std::filesystem::path p);
std::filesystem::path userdir(std::filesystem::path p);

std::vector<const char*> split_string(const char* s, char delimiter);
const char* format(const char* f, ...);

// Get current time in milliseconds.
int64_t time(); 
const char* date(int64_t t, const char* f);
int code(const char* name);
const char* codename(int code);
const char* concatenate_strings(char** strings, int count);

}
