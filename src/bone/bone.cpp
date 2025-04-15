#include <windows.h>
#include <shlobj.h>
#include <sstream>
#include "bone.h"

namespace bone {

std::string project_name = "";

void log(const std::string& message) {
	std::cout << message << std::endl;
}

void log_error(const std::string& message) {
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

int init(std::string project_name_) {
	project_name = project_name_;
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

}