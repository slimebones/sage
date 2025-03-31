#pragma once
#include <iostream>

namespace bone {
void log(const std::string& message);
void log_error(const std::string& message);
void init();
}