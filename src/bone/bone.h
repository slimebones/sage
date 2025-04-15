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

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string format(const char* f, ...) {
    // Create a variable argument list
    va_list args;
    va_start(args, f);

    // Create a string stream
    std::ostringstream oss;

    // Use vsnprintf to format the string into a buffer
    const int bufferSize = 1024; // Adjust size as needed
    char buffer[bufferSize];
    vsnprintf(buffer, bufferSize, f, args);

    // Append the formatted string to the string stream
    oss << buffer;

    // Clean up
    va_end(args);

    // Return the formatted string
    return oss.str();
}
}