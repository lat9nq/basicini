#pragma once

#include <filesystem>

class BasicIni {
public:
    explicit BasicIni(std::filesystem::path ini_path);
    ~BasicIni();
};
