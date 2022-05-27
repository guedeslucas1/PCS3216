cmake_minimum_required(VERSION 3.10)

project(simuladorSisProg)

include_directories(inc)

add_executable(main src/main)

add_library(lib 
    src/eventManager.cpp
    src/dumper.cpp
    src/loader.cpp
)

target_link_libraries(main lib)
