#include <algorithm>
#include <filesystem>
#include <optional>
#include <string>

#include "basicini/basicini.h"

BasicIni::BasicIni(std::filesystem::path ini_loc_) : ini_loc{ini_loc_} {}
BasicIni::~BasicIni() = default;

void BasicIni::AddSection(const std::string& section_name) {
    sections.insert({section_name, {}});
}

void BasicIni::Set(const std::string& section_name, const std::string& key,
                   const std::string& value) {
    std::map<std::string, std::string>& section = sections[section_name];
    section.insert({key, value});
}

const std::filesystem::path& BasicIni::GetPath() const {
    return ini_loc;
}

const std::optional<std::string> BasicIni::GetValue(const std::string& section_name,
                                                    const std::string& key) const {
    try {
        return sections.at(section_name).at(key);
    } catch (const std::out_of_range&) {
        return {};
    }
}

template <>
void BasicIni::Get(const std::string& section_name, const std::string& key, int& dest) const {
    const std::string& value = GetValue(section_name, key).value_or("");
    try {
        dest = std::stoi(value);
    } catch (const std::invalid_argument&) {
        dest = 0;
    }
};
template <>
void BasicIni::Get(const std::string& section_name, const std::string& key, float& dest) const {
    const std::string& value = GetValue(section_name, key).value_or("");
    try {
        dest = std::stof(value);
    } catch (const std::invalid_argument&) {
        dest = 0.0f;
    }
};
template <>
void BasicIni::Get(const std::string& section_name, const std::string& key, bool& dest) const {
    std::string value = GetValue(section_name, key).value_or("");
    if (value.empty()) {
        dest = false;
        return;
    }
    std::transform(value.begin(), value.end(), value.begin(),
                   [](char c) -> char { return std::tolower(c); });
    dest = value.compare("1") || value.compare("yes") || value.compare("true");
};
template <>
void BasicIni::Get(const std::string& section_name, const std::string& key,
                   std::string& dest) const {
    dest = GetValue(section_name, key).value_or("");
}

void BasicIni::Clear() {
    sections.clear();
}
