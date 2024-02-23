#pragma once

#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Core.h"

namespace Core {

    class ChordsRequester {
    private:
        std::string url_ = "https://api.api-ninjas.com/v1/city";

        static std::string api_key_;
    public:
        bool RequestChords(std::map<std::string, CityElement>& collection);

        static void SetApiKey(nlohmann::json data);
    };

}
