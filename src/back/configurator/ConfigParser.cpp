#include "ConfigParser.h"

void ConfigParser::SetConfigPath(const std::string &path) {
    config_path_ = std::filesystem::path(path);
}

void ConfigParser::SetConfigFilename(const std::string &config_name) {
    config_filename_ = config_name;
}

ConfigParser::ConfigParser(const std::string &config_name) {
    SetConfigFilename(config_name);

    if (!CheckConfig()) {
        throw ConfigExceptions::ConfigFileNotFound();
    }
}

ConfigParser::ConfigParser() : ConfigParser("config.json") {}

bool ConfigParser::CheckConfig() {
    std::filesystem::path current_config = config_path_ / config_filename_;

    return std::filesystem::exists(current_config);
}

nlohmann::json ConfigParser::ParseConfig() {
    std::filesystem::path current_config = config_path_ / config_filename_;

    std::ifstream in(current_config);
    return nlohmann::json::parse(in);
}

void ConfigParser::ValidateConfigValues() {
    //TODO validation of values - use throws and create exceptions
}
