#include "src/back/configurator/ConfigParser.h"
#include "src/back/core/Core.h"
#include "src/front/CityElementUI.h"

using namespace ftxui;

int main() {
    WeatherApp::ConfigureApp();

    Core::Core core;

    auto main_component = std::make_shared<CityElementUI>();
    main_component->SetHead(&core);

    WeatherApp::GetChords(core.GetCollection());
    WeatherApp::ReloadForecast(core.GetCollection());

    auto screen = ScreenInteractive::Fullscreen();

//    Components comps = main_component->HourlyWeatherConstructor(core.GetCollection());
    std::time_t first_frame = std::time(nullptr);

//
//    auto tab_container = Container::Tab(comps, &main_component->toggle_selected_);
//    auto tab_ = Container::Vertical({main_component->tab_toggle_, tab_container});
//
//    auto tab_ren = Renderer([&] {
//        return vbox(main_component->tab_toggle_->Render(),
//                separator(),
//                tab_container->Render()) | borderRounded | size(HEIGHT, GREATER_THAN, 17);
//    });

    auto general_container = Container::Vertical({main_component});

    auto elem_ren = Renderer(general_container, [&] {
        return vbox(main_component->Render());
    });

    elem_ren |= CatchEvent([&](Event event) {
        WeatherApp::TimeReload(first_frame, core);

        main_component->tab_->OnEvent(event);
        main_component->OnEvent(event);

        return true;
    });

    screen.Loop(elem_ren);

}
