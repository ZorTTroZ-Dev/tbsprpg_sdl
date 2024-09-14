cmake_minimum_required(VERSION 3.22)
project(tbsprpg_sdl C)

set(CMAKE_C_STANDARD 17)

option(TBSPRPG_LINUX_AMD64 "Building for Linux AMD64" OFF)
option(TBSPRPG_WIN64 "Building for Windows 64" OFF)

if (TBSPRPG_LINUX_AMD64)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif ()

if (TBSPRPG_WIN64)
    include_directories(${CMAKE_SOURCE_DIR}/lib/win64/include)
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
        utilities/geometry.h
        utilities/timing.h
        utilities/timing/timing.c
)

add_executable(tbsprpg_sdl
        main.c
        game/game.c
        game/game.h
        render/render.h
        render/render.c
        audio/audio.h
        audio/audio.c
        simulation/simulation.h
        input/input.h
        simulation/simulation.c
        input/input.c
        game/sdl/game_sdl.h
        game/sdl/game_sdl.c
        input/sdl/input_sdl.c
        input/sdl/input_sdl.h
        render/sdl/render_sdl.h
        render/sdl/render_sdl.c
        render/sdl/render_sdl_sw.h
        render/sdl/render_sdl_sw.c
)

if (TBSPRPG_LINUX_AMD64)
    target_link_libraries(tbsprpg_sdl
            utilities
            ${SDL2_LIBRARIES}
            m
            SDL2_image
    )
endif ()

if (TBSPRPG_WIN64)
    target_include_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/win64/include)
    target_link_directories(tbsprpg_sdl PRIVATE ${CMAKE_SOURCE_DIR}/lib/win64/lib/x64)
    target_link_libraries(tbsprpg_sdl
            utilities
            SDL2
            SDL2main
            SDL2_image
    )
    add_custom_command(TARGET tbsprpg_sdl POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/win64/lib/x64/SDL2.dll"
            $<TARGET_FILE_DIR:tbsprpg_sdl>)
    add_custom_command(TARGET tbsprpg_sdl POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/lib/win64/lib/x64/SDL2_image.dll"
            $<TARGET_FILE_DIR:tbsprpg_sdl>)
endif ()

add_subdirectory(google_tests)

configure_file(config.ini config.ini COPYONLY)

add_custom_command(TARGET tbsprpg_sdl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:tbsprpg_sdl>/resources")

