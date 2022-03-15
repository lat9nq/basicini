#include <cstdio>
#include <filesystem>
#include "basicini/basicini.h"
#include "basicini/basicini_reader.h"

int main() {
    const std::filesystem::path test_path = "./test.ini";
    BasicIni ini{test_path};
    BasicIniReader reader{ini};
    reader.ReadFile();
    std::printf("valid? %s\n", reader.IsValid() ? "yes" : "no");
    return 0;
}
