#pragma once

#include <string>
#include <filesystem>

extern "C" {
bool read(std::filesystem::path path, std::u32string &files);
}