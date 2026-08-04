cmake_minimum_required(VERSION 3.20)

project(Chess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GTest REQUIRED)

#
# Engine Library
#

add_library(chess_engine

    engine/src/board.cpp
    engine/src/game_state.cpp
    engine/src/check.cpp
    engine/src/checkmate.cpp
    engine/src/legal_moves.cpp
    engine/src/promotion.cpp
    engine/src/rules.cpp
    engine/src/chess_engine.cpp
    engine/src/piece.cpp
    engine/src/perft.cpp
    engine/src/fen.cpp
)

target_include_directories(chess_engine
    PUBLIC
        engine/include
)

#
# Main Executable
#

add_executable(chess

    app/main.cpp

    ui/src/renderer.cpp
    ui/src/sdl.cpp
    ui/src/textures.cpp
    ui/src/piece_mapper.cpp
    ui/src/game.cpp
)

target_include_directories(chess
    PRIVATE
        ui/include
)

target_link_libraries(chess
    PRIVATE
        chess_engine
        SDL2::SDL2
        SDL2_image::SDL2_image
)

#
# Tests
#

enable_testing()

add_executable(chess_tests

    tests/test_fen.cpp
    tests/test_board.cpp
    tests/test_rules.cpp
    tests/test_engine.cpp
)

target_link_libraries(chess_tests
    PRIVATE
        chess_engine
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(chess_tests)
