#include <algorithm>
#include <filesystem>
#include <fstream>
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
    section.insert_or_assign(key, value);
}

void BasicIni::SetPath(const std::filesystem::path& new_path) {
    ini_loc = new_path;
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
                   [](char c) -> char { return static_cast<char>(std::tolower(c)); });
    dest = value.compare("1") == 0 || value.compare("yes") == 0 || value.compare("true") == 0;
};
template <>
void BasicIni::Get(const std::string& section_name, const std::string& key,
                   std::string& dest) const {
    dest = GetValue(section_name, key).value_or("");
}

void BasicIni::Clear() {
    sections.clear();
}

void BasicIni::WriteFile(const BasicIni& data) {
    std::fstream ini_file{data.ini_loc, std::ios::out | std::ios::trunc};
    if (!ini_file.is_open()) {
        return;
    }

    for (auto section = data.sections.begin(); section != data.sections.end(); ++section) {
        ini_file << '[' << section->first << "]\n";
        for (auto item = section->second.begin(); item != section->second.end(); ++item) {
            ini_file << item->first << " =" << (item->second.empty() ? "" : " ") << item->second
                     << '\n';
        }
        ini_file << '\n';
    }
    ini_file.close();
}
