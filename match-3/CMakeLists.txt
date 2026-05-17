cmake_minimum_required(VERSION 4.2)
project(match-3 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(raylib STATIC IMPORTED GLOBAL)
set_target_properties(raylib PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libraylib.a
)

add_executable(match-3
        main.c

        src/Constants.c

        src/dicts/SoundDict.c
        src/dicts/TextureDict.c
)

add_subdirectory(libs/smile)

target_include_directories(match-3 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/smile/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dicts
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)

target_link_libraries(match-3 PRIVATE
        smile
        raylib
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
)