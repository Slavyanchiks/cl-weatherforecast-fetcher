#include <iostream>

#include "src/back/configurator/ConfigParser.h"
#include "src/back/core/Core.h"
#include "src/back/core/ChordsRequester.h"


//int main() {

//    ConfigParser cfg;
//    Core::Core::ConfigureSettings(cfg.ParseConfig());
//    Core::ChordsRequester::SetApiKey(cfg.ParseConfig());
//    Core::ForecastRequester::SetParameters(cfg.ParseConfig());
//
//    Core::Core core;
//
//    Core::ChordsRequester chords_requester;
//    Core::ForecastRequester forecast_requester;
//
//    chords_requester.RequestChords(core.GetCollection());
//    forecast_requester.RequestForecast(core.GetCollection());
//
//    for (auto& [key, value] : core.GetCollection()) {
//        std::cout << key << std::endl;
//        std::cout << value.latitude_ << " " << value.longitude_ << " - " << value.days_on_forecast_ << "\n" << std::endl;
//        std::cout << value.hourly_.dump() << "\n" << std::endl;
//        std::cout << value.daily_.dump() << "\n" <<std::endl;
//    }

//    nlohmann::json obj1;
//    obj1["a"] = true;
//
//    nlohmann::json obj2;
//    obj2["b"] = false;
//
//    std::cout << obj1.dump() << " " << obj2.dump() << std::endl;
//
//    obj1.update(obj2);
//
//    std::cout << obj1.dump() << " " << obj2.dump() << std::endl;

//    cpr::Url url("https://api.api-ninjas.com/v1/city");
//    cpr::Parameters params{{"name", "Moscow"}};
//    cpr::Header header{{"X-Api-Key", "XEnAw2bO5S0nNvXJxP/l6A==asoHHuS5RIXfV3UA"}};
//
//    cpr::Session session;
//
//    session.SetUrl(url);
//    session.SetHeader(header);
//    session.SetParameters(params);
//
//    cpr::Response r = session.Get();
//
//    nlohmann::json json = nlohmann::json::parse(r.text);
//
//    std::cout << json[0].at("latitude") << " " << json[0].at("longitude") << "\n\n";
//
//    cpr::Url new_url("https://api.open-meteo.com/v1/forecast");
//
//    cpr::Parameters new_params{
//        {"latitude", to_string(json[0].at("latitude"))},
//        {"longitude", to_string(json[0].at("longitude"))},
//        {"hourly", "temperature_2m,apparent_temperature"}
//    };
//
//    session.SetUrl(new_url);
//    session.SetHeader(cpr::Header{});
//    session.SetParameters(new_params);
//
//    cpr::Response weather = session.Get();
//
//    std::cout << weather.status_line << "\n\n" << weather.text << std::endl;

//}