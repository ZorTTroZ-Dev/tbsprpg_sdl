cmake_minimum_required(VERSION 3.22)
project(tbsprpg_sdl C)

set(CMAKE_C_STANDARD 17)

add_library(mem_manager OBJECT
        utilities/mem_manager/mem_pool.h
        utilities/mem_manager.h
        utilities/mem_manager/mem_manager.c
        utilities/mem_manager/mem_pool.c
        utilities/defines.h
)

add_library(ini_config OBJECT
        utilities/ini_config.h
        utilities/ini_config/ini_config.c
        utilities/defines.h
        utilities/hashmap.h
        utilities/types/hashmap.c
)

add_executable(tbsprpg_sdl
        main.c
        utilities/defines.h
)

target_link_libraries(tbsprpg_sdl
        mem_manager
        ini_config
)

add_subdirectory(google_tests)