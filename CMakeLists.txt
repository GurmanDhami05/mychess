cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Chess)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(chess
    src/main.cpp
    src/mygame/board.cpp
    src/mygame/renderer.cpp
    src/mygame/sdl.cpp
    src/mygame/textures.cpp
    src/mygame/input.cpp
    src/mygame/game.cpp
    src/mygame/rules.cpp
    src/mygame/check.cpp
    src/mygame/board_state.cpp
    src/mygame/checkmate.cpp
    src/mygame/promotion.cpp
)

target_include_directories(chess PRIVATE include)

target_link_libraries(chess
    SDL2::SDL2
    SDL2_image::SDL2_image
)
