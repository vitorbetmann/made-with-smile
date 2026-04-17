cmake_minimum_required(VERSION 4.2)
project(pong C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(pong 
        main.c

        src/Ball.c
        src/Paddle.c
        src/Settings.c
        
        src/scenes/Start.c
        src/scenes/Serve.c
        src/scenes/Play.c
        src/scenes/GameOver.c
)

add_subdirectory(smile)

target_include_directories(pong PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/smile/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)

target_link_libraries(pong PRIVATE
        smile
        raylib
)
