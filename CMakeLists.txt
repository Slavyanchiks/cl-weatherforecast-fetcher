cmake_minimum_required(VERSION 3.26)

project(labwork7)

set(CMAKE_CXX_STANDARD 17)

# Fetch CPR

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
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
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_PROGRESS TRUE  GIT_SHALLOW TRUE
        GIT_TAG v3.11.2)

FetchContent_MakeAvailable(json)

# linking subdirectories

add_subdirectory(bin)