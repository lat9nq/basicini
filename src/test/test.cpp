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
    std::printf("Renderer.resolution_setup = %d\n",
                ini.Get<int>("Renderer", "resolution_setup", 2));
    ini.Set("Renderer", "debug", !ini.Get<bool>("Renderer", "debug", false) ? "true" : "false");
    std::printf("Renderer.debug = %s\n",
                ini.Get<bool>("Renderer", "debug", false) ? "true" : "false");
    std::printf("ControlsP0.vibration_enabled = %s\n",
                ini.Get<bool>("ControlsP0", "vibration_enabled", true) ? "true" : "false");
    std::printf("WebService.web_api_url = %s\n",
                ini.Get<std::string>("WebService", "web_api_url", {}).c_str());
    std::printf("WebService.web_api_url = %d\n", ini.Get<int>("WebService", "web_api_url", 0));
    std::printf("Not.valid = %d\n", ini.Get<int>("Not", "valid", 1234));
    BasicIni::WriteFile(ini);
    return 0;
}
