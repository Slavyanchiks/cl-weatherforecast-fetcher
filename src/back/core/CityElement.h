#pragma once

#include <nlohmann/json.hpp>

namespace Core {

    struct CityElement {
        float latitude_;
        float longitude_;

        int days_on_forecast_;

        nlohmann::json daily_;
        nlohmann::json hourly_;

        CityElement(int days_on_forecast) {
            daily_ = nlohmann::basic_json();
            hourly_ = nlohmann::basic_json();

            days_on_forecast_ = days_on_forecast;

            latitude_ = 0;
            longitude_ = 0;
        }

        CityElement() : CityElement(7) {}
    };

} // Core ns
