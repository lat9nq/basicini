#include <filesystem>
#include <string>

#include "basicini/basicini.h"

BasicIni::BasicIni(std::filesystem::path ini_loc_) : ini_loc{ini_loc_} {}
BasicIni::~BasicIni() = default;

void BasicIni::Set(std::string section, std::string key, std::string value) {}

std::string BasicIni::GetString(std::string section, std::string key) const {
    return {};
}
