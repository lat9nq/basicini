#include <cstdio>
#include <filesystem>
#include <string>

#include "basicini/basicini.h"

BasicIni::BasicIni(std::filesystem::path ini_path) {
    std::printf("%s\n", ini_path.string().c_str());
}

BasicIni::~BasicIni() = default;
