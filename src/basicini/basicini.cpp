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
int BasicIni::Get(const std::string& section_name, const std::string& key,
                  const int& default_value) const {
    const std::string& value = GetValue(section_name, key).value_or("");
    try {
        return std::stoi(value);
    } catch (const std::invalid_argument&) {
        return default_value;
    }
};
template <>
float BasicIni::Get(const std::string& section_name, const std::string& key,
                    const float& default_value) const {
    const std::string& value = GetValue(section_name, key).value_or("");
    try {
        return std::stof(value);
    } catch (const std::invalid_argument&) {
        return default_value;
    }
};
template <>
bool BasicIni::Get(const std::string& section_name, const std::string& key,
                   const bool& default_value) const {
    std::string value = GetValue(section_name, key).value_or("");
    if (value.empty()) {
        return default_value;
    }
    std::transform(value.begin(), value.end(), value.begin(),
                   [](char c) -> char { return static_cast<char>(std::tolower(c)); });
    return value.compare("1") == 0 || value.compare("yes") == 0 || value.compare("true") == 0;
};
template <>
std::string BasicIni::Get(const std::string& section_name, const std::string& key,
                          const std::string& default_value) const {
    return GetValue(section_name, key).value_or(default_value);
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
