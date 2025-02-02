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

    std::time_t first_frame = std::time(nullptr);

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
