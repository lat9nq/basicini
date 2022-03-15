#pragma once

#include <filesystem>

class BasicIniReader {
public:
    explicit BasicIniReader(std::filesystem::path ini_loc_);
    ~BasicIniReader();

    bool IsValid();

private:
    void ReadFile();

    std::filesystem::path ini_loc; ///< location of the file
    bool valid{false};             ///< whether the INI is valid
};
