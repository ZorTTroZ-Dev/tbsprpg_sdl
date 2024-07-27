cmake_minimum_required(VERSION 3.22)
project(tbsprpg_sdl C)

set(CMAKE_C_STANDARD 17)

add_library(mem_manager OBJECT
        utilities/mem_manager/mem_pool.h
        utilities/mem_manager.h
        utilities/mem_manager/mem_manager.c
        utilities/mem_manager/mem_pool.c
)

add_executable(tbsprpg_sdl main.c main.c)
target_link_libraries(tbsprpg_sdl mem_manager)
add_subdirectory(google_tests)