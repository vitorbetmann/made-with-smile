cmake_minimum_required(VERSION 4.2)
project(breakout C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(breakout
        main.c

        src/Settings.c

        src/dicts/TextureDict.c
        src/dicts/SoundDict.c

        src/scenes/Start.c
        src/scenes/PaddleSelect.c
        src/scenes/Serve.c
        src/scenes/Play.c
        src/scenes/GameOver.c
        src/scenes/Victory.c
        src/scenes/EnterHighScore.c
        src/scenes/HighScore.c
)

add_subdirectory(libs/smile)

target_include_directories(breakout PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/smile/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dicts
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)

target_link_libraries(breakout PRIVATE
        smile
        raylib
)