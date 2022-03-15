#include <filesystem>
#include <string>

#include "basicini/basicini.h"
#include "basicini/basicini_reader.h"

BasicIniReader::BasicIniReader(BasicIni& data_) : data{data_} {}

BasicIniReader::~BasicIniReader() = default;

bool BasicIniReader::IsValid() const {
    return valid;
}

void BasicIniReader::ReadFile() {}
