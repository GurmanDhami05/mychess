cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Chess)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(chess
    app/main.cpp

    engine/src/board.cpp
    engine/src/game_state.cpp
    engine/src/check.cpp
    engine/src/checkmate.cpp
    engine/src/game.cpp
    engine/src/legal_moves.cpp
    engine/src/promotion.cpp
    engine/src/rules.cpp
    engine/src/chess_engine.cpp

    ui/src/renderer.cpp
    ui/src/sdl.cpp
    ui/src/textures.cpp
    ui/src/piece_mapper.cpp

)
target_include_directories(chess PRIVATE
    engine/include
    ui/include
)

target_link_libraries(chess
    SDL2::SDL2
    SDL2_image::SDL2_image
)
