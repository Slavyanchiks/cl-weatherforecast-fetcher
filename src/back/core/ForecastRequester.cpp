#include "ForecastRequester.h"

std::vector<std::string> Core::ForecastRequester::daily_parameters_ = {"weather_code"};
std::vector<std::string> Core::ForecastRequester::hourly_parameters_ = {"weather_code"};
int Core::ForecastRequester::amount_of_days_on_forecast_ = 7;

namespace {

    void GenerateRequestParameters(cpr::Parameters& parameters) {
        std::string daily_params = "";

        for (int i = 0; i < Core::ForecastRequester::daily_parameters_.size(); ++i) {
            daily_params += Core::ForecastRequester::daily_parameters_[i];
            if (i != Core::ForecastRequester::daily_parameters_.size() - 1) {
                daily_params += ",";
            }
        }

        parameters.Add({"daily", daily_params});

        std::string hourly_params = "";

        for (int i = 0; i < Core::ForecastRequester::hourly_parameters_.size(); ++i) {
            hourly_params += Core::ForecastRequester::hourly_parameters_[i];
            if (i != Core::ForecastRequester::hourly_parameters_.size() - 1) {
                hourly_params += ",";
            }
        }

        parameters.Add({"hourly", hourly_params});
    }

    void CheckResponse(cpr::Response& response) {
        if (response.status_code >= 400) {
            throw RequestExceptions::BadRequest(response.text);
        }
    }

    void ParseResponse(cpr::Response& response, Core::CityElement& element) {
        nlohmann::json data = nlohmann::json::parse(response.text);

        if (data.contains("daily")) element.daily_.update(data.at("daily"));
        if (data.contains("hourly")) element.hourly_.update(data.at("hourly"));

        if (element.daily_.empty() || element.hourly_.empty()) throw RequestExceptions::BadRequest("has no forecast data");
    };

}

void Core::ForecastRequester::SetParameters(nlohmann::json data) {
    auto dailyparams_p = "/forecast_setup/daily_forecast/parameters"_json_pointer;
    auto hourlyparams_p = "/forecast_setup/hourly_forecast/parameters"_json_pointer;
    auto amount_of_days_p = "/forecast_setup/amount_of_days"_json_pointer;

    for (int i = 0; i < data.at(dailyparams_p).size(); ++i) {
        daily_parameters_.push_back(data.at(dailyparams_p).at(i).get<std::string>());
    }

    for (int i = 0; i < data.at(hourlyparams_p).size(); ++i) {
        hourly_parameters_.push_back(data.at(hourlyparams_p).at(i).get<std::string>());
    }

    amount_of_days_on_forecast_ = data.at(amount_of_days_p).get<int>();
}

bool Core::ForecastRequester::RequestForecast(std::map<std::string, CityElement> &collection) {
    cpr::Url url(url_);

    cpr::Session session;
    session.SetUrl(url);

    for (auto& [city_name, city_element] : collection) {
        cpr::Parameters params{{"latitude", std::to_string(city_element.latitude_)},
                               {"longitude", std::to_string(city_element.longitude_)},
                               {"forecast_days", std::to_string(amount_of_days_on_forecast_)}};
        GenerateRequestParameters(params);
        session.SetParameters(params);

        cpr::Response r = session.Get();

        if (!r.status_code) return false;

        CheckResponse(r);

        ParseResponse(r, city_element);
    }

    return true;
}

void Core::ForecastRequester::IncreaseAmountOfDays() {
    if (amount_of_days_on_forecast_ < 16) ++amount_of_days_on_forecast_;
}
