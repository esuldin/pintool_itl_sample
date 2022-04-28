#pragma once

#include <string>

#include "pin.H"

namespace pintool
{
namespace path
{

std::string filename(const std::string& path);
std::string filename(const IMG& img);

} // namespace path
} // namespace pintool