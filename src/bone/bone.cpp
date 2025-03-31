#include "bone.h"

void bone::log(const std::string& message) {
	std::cout << message << std::endl;
}

void bone::log_error(const std::string& message) {
    const std::string RED = "\033[31m";
    const std::string RESET = "\033[0m";
    std::cout << RED << "ERROR" << RESET << ": " << message << std::endl;
}

void bone::init() {
}
