cmake_minimum_required(VERSION 3.2)

project(slimNES LANGUAGES CXX)

add_executable(slimNES
    cpu.cpp
    main.cpp
)

target_include_directories(slimNES PUBLIC include)
