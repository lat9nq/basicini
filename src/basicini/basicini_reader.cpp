#include <array>
#include <cctype>
#include <filesystem>
#include <string>

#include <fcntl.h>
#include <unistd.h>

#include "basicini/basicini.h"
#include "basicini/basicini_reader.h"

const std::string comment_chars = {';', '#'};

BasicIniReader::BasicIniReader(BasicIni& data_) : data{data_} {}

BasicIniReader::~BasicIniReader() = default;

bool BasicIniReader::IsValid() const {
    return valid;
}

void BasicIniReader::ReadFile() {
    const int fd = open(data.GetPath().string().c_str(), 0, O_RDONLY);
    if (fd == -1) {
        return;
    }

    data.Clear();

    std::string file_data{};
    std::size_t read_len;
    char buffer[255];
    while (read_len = read(fd, &buffer, 255)) {
        if (read_len < 255) {
            buffer[read_len] = '\0';
        }
        file_data.append(buffer);
    }

    close(fd);

    std::string line{};
    int line_number = 0;
    for (std::size_t i = 0; i < file_data.size(); i++) {
        if (file_data[i] == '\0') {
            break;
        }
        switch (file_data[i]) {
        case '\n':
        case '\r':
            line_number++;
            ParseLine(line);
            line.clear();
            break;
        default:
            line.push_back(file_data[i]);
            break;
        }
        if (!valid) {
            break;
        }
    }
}

void BasicIniReader::ParseLine(const std::string& line) {
    if (line.empty()) {
        return;
    }

    // Don't do anything if the current line is a comment
    if (comment_chars.find(line[0]) != std::string::npos) {
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

    const std::string::size_type assignment = line.find('=');
    if (assignment == std::string::npos) {
        valid = false;
        return;
    }

    // Line should be a variable=value pair

    std::string variable_name{};
    std::string variable_value{};

    for (std::size_t i = 0; i < line.find('='); i++) {
        if (!isgraph(line[i])) {
            break;
        }
        variable_name.push_back(line[i]);
    }
    for (std::size_t i = line.find('=') + 1; i < line.size(); i++) {
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
