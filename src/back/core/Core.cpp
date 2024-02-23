#include "Core.h"

Core::Settings Core::Core::settings_;

std::map<std::string, Core::CityElement> &Core::Core::GetCollection() {
    return cities_;
}

void Core::Core::ConfigureSettings(nlohmann::json data) {
    auto enablereload_p = "/reload_setup/enable_intentional_reload"_json_pointer;
    auto defaultreloadtime_p = "/reload_setup/default_reload_time"_json_pointer;
    auto amountofdays_p = "/forecast_setup/daily_forecast/amount_of_days"_json_pointer;

    auto citiesnames_p = "/cities"_json_pointer;

    settings_.EnableIntentionalReload = data.at(enablereload_p).get<bool>();
    settings_.DefaultReloadTime = data.at(defaultreloadtime_p).get<int>();
    settings_.AmountOfDays = data.at(amountofdays_p).get<int>();

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

