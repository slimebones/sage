#pragma once
#include <iostream>
#define byte unsigned char

namespace bone {
void log(const std::string& message);
void log_error(const std::string& message);
void init();
}