#pragma once

#include <string>
#include <vector>

namespace Core {

    struct Settings {
        bool EnableIntentionalReload;
        int DefaultReloadTime;

        std::vector<std::string> CitiesNames;

        int AmountOfDays;
    };

}