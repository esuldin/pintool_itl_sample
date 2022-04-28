#pragma once

#include <iostream>

#define ERROR(msg) std::cerr << "[pintool error]: " << msg << std::endl
#define TRACE(msg) std::clog << "[pintool trace]: " << msg << std::endl