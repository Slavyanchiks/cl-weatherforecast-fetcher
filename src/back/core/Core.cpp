#include "Core.h"

Core::Settings Core::Core::settings_;

std::map<std::string, Core::CityElement> &Core::Core::GetCollection() {
    return cities_;
}

void Core::Core::ConfigureSettings(nlohmann::json data) {
    auto defaultreloadtime_p = "/reload_setup/default_reload_time"_json_pointer;

    auto citiesnames_p = "/cities"_json_pointer;

    settings_.DefaultReloadTime = data.at(defaultreloadtime_p).get<int>();

    for (int i = 0; i < data.at(citiesnames_p).size(); ++i) {
        settings_.CitiesNames.push_back(data.at(citiesnames_p).at(i).get<std::string>());
    }
}

void Core::Core::GenerateCollection() {
    cities_.clear();

    if (settings_.CitiesNames.empty()) throw ConfigExceptions::NeedsConfiguration();

    for (const auto& name : settings_.CitiesNames) {
        cities_.emplace(name, CityElement());
    }
}

Core::Core::Core() {
    GenerateCollection();
}

// WeatherApp operative functions implementation

void WeatherApp::ConfigureApp() {
    ConfigParser cfg;

    Core::Core::ConfigureSettings(cfg.ParseConfig());
    Core::ChordsRequester::SetApiKey(cfg.ParseConfig());
    Core::ForecastRequester::SetParameters(cfg.ParseConfig());
}

void WeatherApp::GetChords(std::map<std::string, Core::CityElement>& cities) {
    Core::ChordsRequester requester;
    requester.RequestChords(cities);
}

bool WeatherApp::ReloadForecast(std::map<std::string, Core::CityElement> &cities) {
    Core::ForecastRequester requester;
    return requester.RequestForecast(cities);
}

void WeatherApp::TimeReload(std::time_t &first_frame, Core::Core &core) {

    if (std::time(nullptr) - first_frame > Core::Core::settings_.DefaultReloadTime) {
        first_frame = std::time(nullptr);
        WeatherApp::ReloadForecast(core.GetCollection());
    }
}
