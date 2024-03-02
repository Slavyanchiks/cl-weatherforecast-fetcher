#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/captured_mouse.hpp"

#include "../back/core/Core.h"

using namespace ftxui;

static inline std::map<std::string, std::string> DailyParameterTranslations = {
        {"temperature_2m_max", "Температура MAX : "},
        {"temperature_2m_min", "Температура MIN : "},
        {"apparent_temperature_max", "По ощущениям MAX : "},
        {"apparent_temperature_min", "По ощущениям MIN : "},
        {"precipitation_sum", "Осадки : "},
        {"precipitation_probability_mean", "Вероятность выпадения осадков : "},
        {"wind_speed_10m_max", "Максимальная скорость ветра : "},
        {"wind_direction_10m_dominant", "Преобладающее направление ветра : "}
};

static inline std::map<std::string, std::string> HourlyParameterTranslations = {
        {"temperature_2m", "Температура : "},
        {"apparent_temperature", "По ощущениям : "},
        {"relative_humidity_2m", "Относительная влажность : "},
        {"dew_point_2m", "Точка росы : "},
        {"wind_speed_10m", "Скорость ветра : "},
        {"wind_direction_10m", "Направление ветра : "},
        {"cloud_cover", "Облачность : "},
        {"surface_pressure", "Давление : "},
        {"precipitation", "Осадки : "},
        {"precipitation_probability", "Вероятность осадков : "}
};

class CityElementUI : public ComponentBase {
private:
    int city_changer_ = 0;
    int day_changer_ = 0;

    Element HeaderConstructor(const std::string& name);
    Element TodayWeatherConstructor(Core::CityElement& city_elem);

    Core::Core* head_;
public:
    bool OnEvent(Event event) override;
    Element Render() override;

    void SetHead(Core::Core* head_p);

    std::vector<std::string> toggle_entries_ = {"Ночь", "Утро", "День", "Вечер"};
    int toggle_selected_ = 0;

    Component tab_toggle_ = Toggle(&toggle_entries_, &toggle_selected_);

    Elements container_morning_;
    Elements container_afternoon_;
    Elements container_evening_;
    Elements container_night_;

    Component tab_container_;
    Component tab_;

    Components HourlyWeatherConstructor(std::map<std::string, Core::CityElement>& cities);
};

