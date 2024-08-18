cmake_minimum_required(VERSION 3.22)
project(tbsprpg_sdl C)

set(CMAKE_C_STANDARD 17)

option(TBSPRPG_LINUX_AMD64 "Building for Linux AMD64" OFF)
option(TBSPRPG_WIN64 "Building for Windows 64" OFF)

if (TBSPRPG_LINUX_AMD64)
    include_directories(${CMAKE_SOURCE_DIR}/lib/linux_amd64/include/SDL2)
endif ()

if (TBSPRPG_WIN64)
    include_directories(${CMAKE_SOURCE_DIR}/lib/win64/include/SDL2)
endif ()

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
        utilities/threading.h
        utilities/threading/threading.c
)

add_executable(tbsprpg_sdl
        main.c
        utilities/defines.h
        utilities/logger.h
        game.c
        game.h
        utilities/threading.h
)

if (TBSPRPG_LINUX_AMD64)
    include_directories(${CMAKE_SOURCE_DIR}/lib/linux_amd64/include)
    target_include_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/linux_amd64/include/SDL2)
    target_link_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/linux_amd64/lib)
    target_link_libraries(tbsprpg_sdl
            utilities
            SDL2
            m
    )
endif ()

if (TBSPRPG_WIN64)
    target_include_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/win64/include/SDL2)
    target_link_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/win64/lib)
    target_link_libraries(tbsprpg_sdl
            utilities
            SDL2
            SDL2main
    )
    add_custom_command(TARGET tbsprpg_sdl POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/win64/bin/SDL2.dll"
            $<TARGET_FILE_DIR:tbsprpg_sdl>)
endif ()

add_subdirectory(google_tests)

configure_file(config.ini config.ini COPYONLY)

