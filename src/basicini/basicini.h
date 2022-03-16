#pragma once

#include <filesystem>
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
    void SetPath(const std::filesystem::path& new_path);

    const std::optional<std::string> GetValue(const std::string& section_name,
                                              const std::string& key) const;
    template <typename T>
    void Get(const std::string& section_name, const std::string& key, T& dest,
             const T& default_value) const;

    const std::filesystem::path& GetPath() const;

    static void WriteFile(const BasicIni& ini);

private:
    std::map<std::string, std::map<std::string, std::string>> sections;
    std::filesystem::path ini_loc;
};
