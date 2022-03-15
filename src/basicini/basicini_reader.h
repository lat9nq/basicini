#pragma once

#include <filesystem>
#include <memory>

#include "basicini/basicini.h"

class BasicIniReader {
public:
    explicit BasicIniReader(BasicIni& data_);
    ~BasicIniReader();

    bool IsValid() const;

private:
    void ReadFile();

    bool valid{false}; ///< whether the INI is valid

    BasicIni& data;
};
