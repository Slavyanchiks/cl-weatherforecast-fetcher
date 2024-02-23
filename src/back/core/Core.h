#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <iostream>

#include <map>

#include "CityElement.h"
#include "Settings.h"
#include "../utils/Exceptions.h"

#include "ChordsRequester.h"
#include "ForecastRequester.h"

namespace Core {

    class Core {
    private:
        std::map<std::string, CityElement> cities_;
    public:
        std::map<std::string, CityElement>& GetCollection();

        static Settings settings_;

        static void ConfigureSettings(nlohmann::json data);

        void GenerateCollection();

        Core();
    };

}

namespace WeatherApp {

}
