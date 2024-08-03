cmake_minimum_required(VERSION 3.14)

# 'google_test' is the subproject name
project(google_tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tbsprpg_sdl_tests
        utilities/mem_manager/mem_pool_tests.cpp
        ../utilities/strutils.h
        ../utilities/strutils/strutils.c
        ../utilities/mem_manager.h
        ../utilities/mem_manager/mem_pool.c
)
target_link_libraries(
        tbsprpg_sdl_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tbsprpg_sdl_tests)

