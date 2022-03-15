#include <filesystem>
#include <string>

#include "basicini/basicini.h"

BasicIni::BasicIni(std::filesystem::path ini_loc_) : ini_loc{ini_loc_} {}
BasicIni::~BasicIni() = default;

void BasicIni::AddSection(std::string section_name) {
    sections.insert({section_name, {}});
}

void BasicIni::Set(std::string section_name, std::string key, std::string value) {
    std::map<std::string, std::string>& section = sections[section_name];
    section.insert({key, value});
}

const std::string& BasicIni::GetString(std::string section_name, std::string key) const {
    return sections.at(section_name).at(key);
}

std::filesystem::path BasicIni::GetPath() const {
    return ini_loc;
}

void BasicIni::Clear() {
    sections.clear();
}
