#pragma once

#include <string>
#include <filesystem>

extern "C" {
std::string read(std::filesystem::path path);
}