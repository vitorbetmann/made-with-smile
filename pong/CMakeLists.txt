cmake_minimum_required(VERSION 4.2)
project(pong C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define paths to your local raylib installation
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

# Add Smile as a subdirectory
add_subdirectory(smile)

# Include Smile headers
target_include_directories(pong PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/smile/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)

# Link against the Smile and the raylib static libraries
target_link_libraries(pong PRIVATE
        smile
        raylib
)
