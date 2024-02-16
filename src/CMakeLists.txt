project(weather)

add_library(${PROJECT_NAME} parser.h parser.cpp)

# Fetch CPR

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8
)

FetchContent_MakeAvailable(cpr)

# Fetch nlohmann/json for json files

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(json)

# Fetching FTXUI - interface

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)

if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(${PROJECT_NAME}
        PUBLIC cpr::cpr
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC nlohmann_json::nlohmann_json
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC ftxui::screen
        PUBLIC ftxui::component
        PUBLIC ftxui::dom
)