cmake_minimum_required(VERSION 3.20)

project(engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(engine
    src/main.cpp
    src/window.h
    #src/sdl_spike.cpp
)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.14
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

target_link_libraries(engine PRIVATE SDL3::SDL3)

target_compile_definitions(engine PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:engine> $<TARGET_FILE_DIR:engine>
    COMMAND_EXPAND_LISTS
)