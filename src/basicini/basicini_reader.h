#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "basicini/basicini.h"

class BasicIniReader {
public:
    explicit BasicIniReader(BasicIni& data_);
    ~BasicIniReader();

    bool IsValid() const;
    void ReadFile();

private:
    void LexLine(const std::string& line);

    bool valid{true}; ///< whether the INI is valid

    BasicIni& data;
    std::string current_section;
};
