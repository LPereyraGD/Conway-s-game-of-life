cmake_minimum_required(VERSION 3.14)
project(GameOfLife64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings are important for "defensible" high-quality code
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(src)

# Core Logic Library
add_library(life_core
    src/Cell.h
    src/LifeTypes.h
    src/LifeEngine.h
    src/GameWorld.h
    src/GameWorld.cpp
    src/LifeReader.h
    src/LifeReader.cpp
    src/LifeWriter.h
    src/LifeWriter.cpp
)

# Main Executable
add_executable(game_of_life src/main.cpp)
target_link_libraries(game_of_life life_core)

# Simple Unit Tests
enable_testing()
add_executable(unit_tests tests/unit_tests.cpp)
target_link_libraries(unit_tests life_core)
add_test(NAME CoreTests COMMAND unit_tests)
