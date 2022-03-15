#pragma once

#include <map>
#include <string>
#include <vector>

class BasicIni {
public:
    explicit BasicIni(std::filesystem::path ini_loc_);
    ~BasicIni();

    void AddSection(std::string section_name);
    void Set(std::string section_name, std::string key, std::string value);

    const std::string& GetString(std::string section_name, std::string key) const;
    //~ template <typename T>
    //~ T Get(std::string section, std::section key) const;

    std::filesystem::path GetPath() const;

    void Clear();

private:
    std::map<std::string, std::map<std::string, std::string>> sections;
    const std::filesystem::path ini_loc;
};
