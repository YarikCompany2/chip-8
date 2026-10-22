cmake_minimum_required(VERSION 3.12)

project(
    CEmulator
    DESCRIPTION "Emulator of the CHIP-8 that is written in C"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendors)

add_executable(${PROJECT_NAME}
    include/chip8.h
    include/defines.h
    include/platform.h

    src/platform.c
    src/chip8.c
    src/main.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR OFF
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2::SDL2
)
