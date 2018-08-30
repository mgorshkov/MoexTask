cmake_minimum_required(VERSION 3.2)
project(MoexTask VERSION 0.0.1)

add_executable(MoexTask
    Main.cpp
    StatisticsServer.cpp
    StatisticsServer.h
    TsvParser.cpp
    TsvParser.h)

add_executable(MoexTaskClient Client.cpp)
add_library(MoexTaskLib Lib.cpp)

set_target_properties(MoexTask MoexTaskClient PROPERTIES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "-std=c++1z")

target_link_libraries(MoexTask
    MoexTaskLib
)

target_link_libraries(MoexTaskClient
    MoexTaskLib
)
