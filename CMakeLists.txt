cmake_minimum_required(VERSION 3.22)
project(tbsprpg_sdl C)

set(CMAKE_C_STANDARD 17)

add_library(utilities OBJECT
        utilities/mem_manager/mem_pool.h
        utilities/mem_manager.h
        utilities/mem_manager/mem_manager.c
        utilities/mem_manager/mem_pool.c
        utilities/ini_config.h
        utilities/ini_config/ini_config.c
        utilities/defines.h
        utilities/hashmap.h
        utilities/types/hashmap.c
        utilities/logger.h
        utilities/logger/logger.c
        utilities/strutils.h
        utilities/strutils/strutils.c
)

add_executable(tbsprpg_sdl
        main.c
        utilities/defines.h
        utilities/logger.h
)

target_link_libraries(tbsprpg_sdl
        utilities
)

add_subdirectory(google_tests)

configure_file(config.ini config.ini COPYONLY)