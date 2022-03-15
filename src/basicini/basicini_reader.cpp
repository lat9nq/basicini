#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <string>
#include "basicini/basicini.h"
#include "basicini/basicini_reader.h"

const std::string comment_chars = {';', '#'};

BasicIniReader::BasicIniReader(BasicIni& data_) : data{data_} {}

BasicIniReader::~BasicIniReader() = default;

bool BasicIniReader::IsValid() const {
    return valid;
}

void BasicIniReader::ReadFile() {
    std::fstream ini_file{data.GetPath()};
    if (!ini_file.is_open()) {
        return;
    }

    data.Clear();

    std::string line{};
    while (std::getline(ini_file, line)) {
        LexLine(line);
    }
    ini_file.close();
}

void BasicIniReader::LexLine(const std::string& line) {
    if (line.empty()) {
        return;
    }

    // Don't do anything if the current line is a comment
    if (comment_chars.find(line[0]) != std::string::npos) {
        return;
    }

    // Current line is invalid
    if (!isgraph(line[0])) {
        valid = false;
        return;
    }

    if (line[0] == '[') {
        // Current line is a section
        std::string section_name{};

        for (std::size_t i = 1; i < line.size(); i++) {
            if (line[i] == ']') {
                break;
            }
            section_name.push_back(line[i]);
        }

        data.AddSection(section_name);
        current_section = section_name;

        return;
    }

    // Check line has assignment character and starts at the beginning of the line
    const std::string::size_type assignment = line.find('=');
    if (assignment == std::string::npos) {
        valid = false;
        return;
    }

    // Line should be a variable=value pair

    std::string variable_name{};
    std::string variable_value{};

    for (std::size_t i = 0; i < assignment; i++) {
        if (!std::isgraph(line[i])) {
            break;
        }
        variable_name.push_back(line[i]);
    }
    for (std::size_t i = assignment + 1; i < line.size(); i++) {
        variable_value.push_back(line[i]);
    }

    // Strip trailing spaces in value
    if (!variable_value.empty()) {
        variable_value.erase(0, variable_value.find_first_not_of(' ', 0));
        variable_value.erase(variable_value.find_last_not_of(' ', variable_value.size()) + 1,
                             variable_value.size());
    }

    data.Set(current_section, variable_name, variable_value);
}
