#include <iostream>
//#include <fstream>

#include <cpr/cpr.h>
#include <conio.h>

//#include "cmake-build-debug/_deps/json-src/single_include/nlohmann/json.hpp"

//using json = nlohmann::json;

int main() {
//    json file parsing test code
//    std::ifstream in("../config.json");
//    json j = json::parse(in);
//
//    std::cout << j["pi"] << " " << j["happy"] << '\n';

//    cpr test code
//    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
//                               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
//                               cpr::Parameters{{"anon", "true"}, {"key", "value"}});
//    std::cout << r.status_code << std::endl;
//    std::cout << r.header["content-type"] << std::endl;
//
//    std::cout << r.elapsed << " of time" << std::endl;


//    conio stuff test code
    while (true) {
        if (_getch() == VK_ESCAPE) {
            std::cout << "goood byyye";
            break;
        } else {
            system("CLS");
            std::cout << "................\n";
        }
    }
}