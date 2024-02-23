#pragma once

#include <string>
#include <filesystem>
#include "nlohmann/json.hpp"

#include <fstream>

#include "../utils/Exceptions.h"

class ConfigParser {
private:
    std::filesystem::path config_path_ = "../../config/";
    std::string config_filename_;
public:
    void SetConfigPath(const std::string& path);
    void SetConfigFilename(const std::string& config_name);

    bool CheckConfig();

    void ValidateConfigValues();

    nlohmann::json ParseConfig();

    explicit ConfigParser(const std::string& config_name);
    ConfigParser();
};

