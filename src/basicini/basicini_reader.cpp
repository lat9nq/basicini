#include <cstdio>
#include <filesystem>
#include <string>

#include "basicini/basicini.h"

BasicIniReader::BasicIniReader(std::filesystem::path ini_loc_) : ini_loc{ini_loc_} {
    std::printf("%s\n", ini_loc.string().c_str());
}

BasicIniReader::~BasicIniReader() = default;
