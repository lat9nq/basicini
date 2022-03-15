#include <filesystem>
#include "basicini/basicini_reader.h"

int main() {
    const std::filesystem::path test_path = "./test.ini";
    BasicIni ini(test_path);
    return 0;
}
