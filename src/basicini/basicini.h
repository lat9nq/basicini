#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

class BasicIni {
public:
    explicit BasicIni(std::filesystem::path ini_loc_);
    ~BasicIni();

    void AddSection(const std::string& section_name);
    void Set(const std::string& section_name, const std::string& key, const std::string& value);
    void Clear();

    template <typename T>
    void Get(const std::string& section_name, const std::string& key, T& dest) const;

    const std::filesystem::path& GetPath() const;

private:
    const std::optional<std::string> GetValue(const std::string& section_name,
                                              const std::string& key) const;

    std::map<std::string, std::map<std::string, std::string>> sections;
    const std::filesystem::path ini_loc;
};
