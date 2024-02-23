#include "ChordsRequester.h"

std::string Core::ChordsRequester::api_key_;

namespace {

    void CheckResponse(cpr::Response& response, const std::string& city_name) {
        if (response.status_code == 200 && response.text == "[]") {
            throw RequestExceptions::IncorrectCityName(city_name);
        } else if (response.status_code >= 400) {
            throw RequestExceptions::BadRequest(response.error.message);
        }
    }

    void ParseResponse(cpr::Response& response, Core::CityElement& elem) {
        nlohmann::json data = nlohmann::json::parse(response.text).at(0);

        if (data.contains("latitude") && data.contains("longitude")) {
            elem.latitude_ = data.at("latitude").get<float>();
            elem.longitude_ = data.at("longitude").get<float>();
        } else {
            throw RequestExceptions::BadRequest(response.text);
        }
    }

}

void Core::ChordsRequester::SetApiKey(nlohmann::json data) {
    auto api_key_p = "/ninja_api_key"_json_pointer;

    api_key_ = data.at(api_key_p).get<std::string>();
}

bool Core::ChordsRequester::RequestChords(std::map<std::string, CityElement> &collection) {
    cpr::Url url(url_);
    cpr::Header header{{"X-Api-Key", api_key_}};

    cpr::Session session;
    session.SetUrl(url);
    session.SetHeader(header);

    for (auto& [city_name, city_element] : collection) {
        cpr::Parameters params{{"name", city_name}};
        session.SetParameters(params);

        cpr::Response r = session.Get();

        if (!r.status_code) return false;

        CheckResponse(r, city_name);
        ParseResponse(r, city_element);
    }

    return true;
}
