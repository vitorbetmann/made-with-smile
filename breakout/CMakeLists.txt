cmake_minimum_required(VERSION 4.2)
project(breakout C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libraylib.a
)

add_executable(breakout
        main.c

        src/Paddle.c
        src/Ball.c
        src/Util.c
        src/Constants.c
        src/LevelMaker.c
        src/Brick.c

        src/dicts/SoundDict.c
        src/dicts/TextureDict.c

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
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
)