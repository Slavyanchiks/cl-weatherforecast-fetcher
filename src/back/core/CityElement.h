#pragma once

#include <nlohmann/json.hpp>

namespace Core {

    struct CityElement {
        float latitude_;
        float longitude_;

        nlohmann::json daily_;
        nlohmann::json hourly_;

        CityElement() {
            daily_ = nlohmann::basic_json();
            hourly_ = nlohmann::basic_json();

            latitude_ = 0;
            longitude_ = 0;
        }
    };

} // Core ns
