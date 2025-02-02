#pragma once

#include <string>
#include <vector>

namespace Core {

    struct Settings {
        int DefaultReloadTime;

        std::vector<std::string> CitiesNames;
    };

}