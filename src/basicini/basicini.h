#pragma once

#include <map>
#include <string>
#include <vector>

class BasicIni {
public:
    explicit BasicIni(std::filesystem::path ini_loc_);
    ~BasicIni();

    void Set(std::string section, std::string key, std::string value);

    std::string GetString(std::string section, std::string key) const;
    //~ template <typename T>
    //~ T Get(std::string section, std::section key) const;

private:
    std::map<std::string, std::map<std::string, std::string>> sections;
    const std::filesystem::path ini_loc;
};
