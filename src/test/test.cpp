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
    std::printf("Renderer.resolution_setup = %d\n", [&]() {
        int value;
        ini.Get("Renderer", "resolution_setup", value, 2);
        return value;
    }());
    ini.Set("Renderer", "debug",
            [&]() {
                bool value;
                ini.Get("Renderer", "debug", value, false);
                return !value;
            }()
                ? "true"
                : "false");
    std::printf("Renderer.debug = %s\n",
                [&]() {
                    bool value;
                    ini.Get("Renderer", "debug", value, false);
                    return value;
                }()
                    ? "true"
                    : "false");
    std::printf("ControlsP0.vibration_enabled = %s\n",
                [&]() {
                    bool value;
                    ini.Get("ControlsP0", "vibration_enabled", value, true);
                    return value;
                }()
                    ? "true"
                    : "false");
    std::printf("WebService.web_api_url = %s\n",
                [&]() {
                    std::string value;
                    ini.Get("WebService", "web_api_url", value, {});
                    return value;
                }()
                    .c_str());
    std::printf("WebService.web_api_url = %d\n", [&]() {
        int value;
        ini.Get("WebService", "web_api_url", value, 0);
        return value;
    }());
    std::printf("Not.valid = %d\n", [&]() {
        int value;
        ini.Get("Not", "valid", value, 1234);
        return value;
    }());
    BasicIni::WriteFile(ini);
    return 0;
}
