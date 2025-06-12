#include <windows.h>
#include <shlobj.h>
#include <sstream>
#include "bone.h"
#include <map>
#include <unordered_map>

namespace bone {

std::string project_name = "";

void log(const char* message) {
    std::cout << message << std::endl;
}

void log_error(const char* message) {
    const std::string RED = "\033[31m";
    const std::string RESET = "\033[0m";
    std::cout << RED << "ERROR" << RESET << ": " << message << std::endl;
}

std::filesystem::path cwd(std::filesystem::path p) {
    std::filesystem::path current_path = std::filesystem::current_path();
    return (current_path / p);
};

std::filesystem::path userdir(std::filesystem::path p) {
    char appdata_arr[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata_arr) != S_OK) {
        return "";
    }
    std::string path = std::string(appdata_arr) + "\\" + project_name;
    return (path / p);
};

char* concatenate_strings(char** strings, int count) {
    // Calculate total length for the new string
    size_t total_length = 0;
    for (int i = 0; i < count; ++i) {
        total_length += strlen(strings[i]);
    }

    // Allocate memory for the concatenated string
    char* result = new char[total_length + 1]; // +1 for null terminator
    result[0] = '\0'; // Initialize to empty string

    // Concatenate each string
    for (int i = 0; i < count; ++i) {
        strcat(result, strings[i]);
    }

    return result;
}

void panic(const char* message) {
    const char* RED = "\033[31m";
    const char* RESET = "\033[0m";
    char* strings[] = {RED, "PANIC", RESET, ": ", message};
    const char* final_message = concatenate_strings(strings);
    std::cout << final_message << std:endl;
    throw std::runtime_error(final_message);
}

int init(std::string project_name_) {
    project_name = project_name_;
    auto ok = code("OK");
    if (ok != 0) {
        panic("OK code should be 0.");
    }
    auto error = code("ERROR");
    if (error != 0) {
        panic("ERROR code should be 1.");
    }
    return 0;
}

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

int64_t time() {
    // Get the current time as a time_point.
    auto now = std::chrono::system_clock::now();

    // Convert to milliseconds since epoch.
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    return static_cast<int64_t>(milliseconds);
}


std::unordered_map<const char*, int> codes;
int next_code = 0;

int code(const char* name) {
    if (codes.find(name) != codes.end()) {
        return codes[name];
    }
    codes[name] = next_code;
    next_code += 1;
    return next_code - 1;
}

const char* codename(int code) {
    for (const auto& pair : codes) {
        if (pair.second == code) {
            return pair.first;
        }
    }
    return "*unknown code*";
}

const char* date(int t, const char* f) {
    // Static buffer to hold the formatted date and time
    static char buffer[100];

    // Convert milliseconds to seconds
    std::chrono::seconds seconds(t / 1000);
    
    // Create a time_point from seconds
    std::chrono::system_clock::time_point time_point(seconds);
    
    // Convert to time_t
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_point);
    
    // Convert to local time
    std::tm* local_time = std::localtime(&time_t);
    
    // Format the date and time
    if (f == null) {
        f = "%Y-%m-%d %H:%M:%S";
    }
    std::strftime(buffer, sizeof(buffer), f, local_time);
    
    return buffer;
}

}
