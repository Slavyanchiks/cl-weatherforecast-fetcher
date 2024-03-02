#include "CityElementUI.h"

namespace {
    std::string GetDate(Core::CityElement& element, int day_changer) {
        std::string full_date = element.daily_.at("time").at(24*day_changer).get<std::string>();

        return std::string(full_date.substr(0, 10));
    }

    std::string GetPreciseFloat(float f) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << f;
        return ss.str();
    }
}

Element CityElementUI::HeaderConstructor(const std::string &name) {
    return hbox(text(name)) | borderRounded;
}

Element CityElementUI::TodayWeatherConstructor(Core::CityElement &city_elem) {
    Elements displayed_params;

    for (const auto& param : Core::ForecastRequester::daily_parameters_) {
        if (param != "weather_code") {
            std::string final_str = DailyParameterTranslations[param] + GetPreciseFloat(city_elem.daily_.at(param).at(0).get<float>());
            displayed_params.push_back(text(final_str) | size(WIDTH, EQUAL, 30));
        }
    }

    return window(text(city_elem.daily_.at("time").at(0).get<std::string>()),vflow(displayed_params))
                  | size(HEIGHT, GREATER_THAN, 4) | size(HEIGHT, LESS_THAN, 6);
}

Components CityElementUI::HourlyWeatherConstructor(std::map<std::string, Core::CityElement>& cities) {
    int start_iter = 24 * day_changer_;

    container_night_.clear();
    container_morning_.clear();
    container_afternoon_.clear();
    container_evening_.clear();

    for (const auto& param : Core::ForecastRequester::hourly_parameters_) {
        if (param != "weather_code") {
            std::string final_str = HourlyParameterTranslations[param] + GetPreciseFloat(
                    cities[Core::Core::settings_.CitiesNames[city_changer_]].hourly_.at(param).at(
                            start_iter + 8).get<float>());
            container_morning_.emplace_back(text(final_str) | size(WIDTH, GREATER_THAN, 20));
        }
    }
    for (const auto& param : Core::ForecastRequester::hourly_parameters_) {
        if (param != "weather_code") {
            std::string final_str = HourlyParameterTranslations[param] + GetPreciseFloat(
                    cities[Core::Core::settings_.CitiesNames[city_changer_]].hourly_.at(param).at(
                            start_iter + 14).get<float>());
            container_afternoon_.emplace_back(text(final_str) | size(WIDTH, GREATER_THAN, 20));
        }
    }
    for (const auto& param : Core::ForecastRequester::hourly_parameters_) {
        if (param != "weather_code") {
            std::string final_str = HourlyParameterTranslations[param] + GetPreciseFloat(
                    cities[Core::Core::settings_.CitiesNames[city_changer_]].hourly_.at(param).at(
                            start_iter + 20).get<float>());
            container_evening_.emplace_back(text(final_str) | size(WIDTH, GREATER_THAN, 20));
        }
    }
    for (const auto& param : Core::ForecastRequester::hourly_parameters_) {
        if (param != "weather_code") {
            std::string final_str = HourlyParameterTranslations[param] + GetPreciseFloat(
                    cities[Core::Core::settings_.CitiesNames[city_changer_]].hourly_.at(param).at(
                            start_iter + 2).get<float>());
            container_night_.emplace_back(text(final_str) | size(WIDTH, GREATER_THAN, 20));
        }
    }

    return {Renderer([&] { return vbox(container_night_); }),
            Renderer([&] { return vbox(container_morning_); }),
            Renderer([&] { return vbox(container_afternoon_); }),
            Renderer([&] { return vbox(container_evening_); })};
}

bool CityElementUI::OnEvent(ftxui::Event event) {
    if (event.is_character()) {
        if (event.character() == "n") {
            city_changer_ = (city_changer_ + 1) % Core::Core::settings_.CitiesNames.size();
        } else if (event.character() == "p") {
            city_changer_ = (city_changer_ - 1) % Core::Core::settings_.CitiesNames.size();
        } else if (event.character() == "+") {
            day_changer_ = (day_changer_ + 1) % 16;
        } else if (event.character() == "-") {
            day_changer_ = (day_changer_ - 1) % 16;
        }
    } else if (event == Event::Escape) {
        event.screen_->Exit();
    }

    return ComponentBase::OnEvent(event);
}

Element CityElementUI::Render() {
    tab_container_ = Container::Tab({HourlyWeatherConstructor(head_->GetCollection())}, &toggle_selected_);

    tab_ = Container::Vertical({tab_toggle_, tab_container_});

    return vbox(HeaderConstructor(Core::Core::settings_.CitiesNames[city_changer_]),
                TodayWeatherConstructor(head_->GetCollection()[Core::Core::settings_.CitiesNames[city_changer_]]),
                tab_toggle_->Render(),
                separator(),
                tab_container_->Render() | borderRounded | size(HEIGHT, GREATER_THAN, 17)) ;
}

void CityElementUI::SetHead(Core::Core *head_p) {
    head_ = head_p;
}