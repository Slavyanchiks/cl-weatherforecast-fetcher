#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

#include "Core.h"

namespace Core {

    class ForecastRequester {
    private:
        std::string url_ = "https://api.open-meteo.com/v1/forecast";
    public:
        static std::vector<std::string> daily_parameters_;
        static std::vector<std::string> hourly_parameters_;

        static void SetParameters(nlohmann::json data);

        bool RequestForecast(std::map<std::string, CityElement>& collection);

    };

}
